<?php

/**
 * @file
 *
 * Support for migrating authors from a WordPress blog into Drupal.
 */

/**
 * Implementation of WordPressMigration, for authors
 */
class WordPressAuthor extends WordPressMigration {
  /**
   * Set it up
   */
  public function __construct(array $arguments = array()) {
    parent::__construct($arguments);

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'wp:author_login' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'WordPress author username',
        )
      ),
      WordPressAuthorDestination::getKeySchema()
    );

    $fields = array(
      'wp:author_id' => 'Unique WordPress ID of the author',
      'wp:author_login' => 'Username (for login) of the author',
      'wp:author_email' => 'Author email address',
      'wp:author_display_name' => 'Displayed author name',
      'wp:author_first_name' => 'Author first name',
      'wp:author_last_name' => 'Author last name',
    );

    // Construct the source and destination objects.
    $source_options = array(
      'reader_class' => 'MigrateXMLReader',
      'cache_counts' => TRUE,
    );
    $this->source = new MigrateSourceXML($this->wxrFile, '/rss/channel/wp:author',
      'wp:author_login', $fields, $source_options, $this->arguments['namespaces']);
    $this->destination = new WordPressAuthorDestination($arguments);

    // The basic mappings
    $this->addFieldMapping('name', 'wp:author_login')
         ->xpath('wp:author_login')
         ->dedupe('users', 'name');
    $this->addFieldMapping('mail', 'wp:author_email')
         ->xpath('wp:author_email');
    $this->addFieldMapping('roles')
         ->defaultValue(DRUPAL_AUTHENTICATED_RID);
    $this->addFieldMapping('status')
         ->defaultValue(1);

    // Unmapped destination fields
    $this->addUnmigratedDestinations(array('pass', 'theme', 'signature',
      'signature_format', 'created', 'access', 'login', 'timezone', 'language',
      'picture', 'init', 'is_new', 'role_names', 'data'));
    if (module_exists('path')) {
      $this->addUnmigratedDestinations(array('path'));
    }

    // Unmapped source fields
    $this->addUnmigratedSources(array('wp:author_display_name',
      'wp:author_first_name', 'wp:author_last_name', 'wp:author_id'));
  }
}

class WordPressAuthorDestination extends MigrateDestinationUser {
  /**
   * Whethere we will create new user accounts from authors with email
   * addresses not already registered.
   *
   * @var bool
   */
  protected $importUsers = TRUE;

  /**
   * The user ID of the account to use for any unimported authors.
   *
   * @var int
   */
  protected $defaultAuthorUid = 1;

  public function __construct($options = array()) {
    parent::__construct($options);
    $this->importUsers = $options['import_users'];
    $this->defaultAuthorUid = $options['default_author_uid'];
  }

  /**
   * Override of MigrateDestinationUser::import().
   *
   * On initial import, if the email address already exists we want to link to
   * that account, and remember that we did so. On updates, if we see that it
   * is a linked account, we don't want to update it.
   *
   * @param stdClass $account
   * @param stdClass $row
   */
  public function import(stdClass $account, stdClass $row) {
    if (isset($row->migrate_map_destid1)) {
      // Updating the account - if it's linked, just return the ID of the linked
      // account
      $uid = db_select('wordpress_migrate_linked_authors', 'a')
             ->fields('a', array('uid'))
             ->condition('mail', $account->mail)
             ->execute()
             ->fetchField();
      if ($uid) {
        $this->numUpdated++;
        return array($uid);
      }
    }
    else {
      // Initial import - if already in the users table, add to our linked_authors
      // list and return the uid of the existing account.
      $uid = db_select('users', 'u')
             ->fields('u', array('uid'))
             ->condition('mail', $account->mail)
             ->execute()
             ->fetchField();
      if (!$uid) {
        // This user does not yet exist on the site. See if we're supposed to
        // create it.
        $create_new_users = $this->importUsers;
        if (!$create_new_users) {
          // Link this content to the default user chosen in the import settings.
          $uid = $this->defaultAuthorUid;
        }
      }
      if ($uid) {
        db_merge('wordpress_migrate_linked_authors')
          ->key(array('mail' => $account->mail))
          ->fields(array('uid' => $uid))
          ->execute();
        $this->numCreated++;
        return array($uid);
      }
    }
    // If there's no linkage, do the normal thing and create a new user.
    return parent::import($account, $row);
  }

  /**
   * Override of MigrateDestinationUser::bulkRollback().
   *
   * We want to make sure we don't delete any users who existed before we first
   * imported.
   *
   * @param $uids
   *  Array of user IDs to be deleted.
   */
  public function bulkRollback(array $uids) {
    // Make sure we only attempt each uid once - if multiple authors had the
    // same email address in WordPress, the corresponding Drupal uid will be in
    // the array twice, we'll delete the linked_authors row the first time we
    // see it, and the second pass on that uid will delete the account.
    $uids = array_unique($uids, SORT_NUMERIC);
    $delete_uids = array();
    foreach ($uids as $uid) {
      $mail = db_select('wordpress_migrate_linked_authors', 'a')
              ->fields('a', array('mail'))
              ->condition('uid', $uid)
              ->execute()
              ->fetchField();
      if ($mail) {
        db_delete('wordpress_migrate_linked_authors')
          ->condition('mail', $mail)
          ->execute();
      }
      else {
        $delete_uids[] = $uid;
      }
    }
    parent::bulkRollback($delete_uids);
  }
}
