<?php

/**
 * @file
 *
 * Support for migrating comments from a WordPress blog into Drupal.
 */

/**
 * Override of MigrateXMLReader, so we can track the parent posts for
 * comments.
 */
class WordPressCommentXMLReader extends MigrateXMLReader {
  /**
   * The last post ID we've seen - saved so we can apply it to comments.
   * @var int
   */
  protected $postId;

  /**
   * Implementation of Iterator::next(). We need to preserve the ID of
   * the parent element.
   *
   * @return void
   */
  public function next() {
    migrate_instrument_start('WordPressCommentXMLReader::next');
    $this->currentElement = $this->currentId = NULL;

    // Loop over each node in the XML file, looking for elements at a path
    // matching the input query string (represented in $this->elementsToMatch).
    while ($this->reader->read()) {
      if ($this->reader->nodeType == XMLREADER::ELEMENT) {
        $this->currentPath[$this->reader->depth] = $this->reader->localName;
        // Save the last post_id, so comments can use it to find their parent
        if ($this->reader->name == 'wp:post_id') {
          $this->postId = WordPressBlog::readString($this->reader);
        }
        elseif ($this->reader->name == 'wp:post_type') {
          $this->currentPostType = WordPressBlog::readString($this->reader);
        }
        if ($this->currentPath == $this->elementsToMatch) {
          if ($this->postType != $this->currentPostType) {
            continue;
          }

          // We're positioned to the right element path - if filtering on an
          // attribute, check that as well before accepting this element.
          if (empty($this->attributeName) ||
              ($this->reader->getAttribute($this->attributeName) == $this->attributeValue)) {
            // We've found a matching element - get a SimpleXML object representing it.
            // We must associate the DOMNode with a DOMDocument to be able to import
            // it into SimpleXML.
            // Despite appearances, this is almost twice as fast as
            // simplexml_load_string($this->readOuterXML());
            $node = $this->reader->expand();
            if ($node) {
              $dom = new DOMDocument();
              $node = $dom->importNode($node, TRUE);
              $dom->appendChild($node);
              $this->currentElement = simplexml_import_dom($node);
              if ($this->reader->name == 'wp:comment') {
                $this->currentElement->post_id = $this->postId;
              }
              $idnode = $this->currentElement->xpath($this->idQuery);
              $this->currentId = (string)reset($idnode);
              break;
            }
            else {
              foreach (libxml_get_errors() as $error) {
                $error_string = MigrateItemsXML::parseLibXMLError($error);
                if ($migration = Migration::currentMigration()) {
                  $migration->saveMessage($error_string);
                }
                else {
                  Migration::displayMessage($error_string);
                }
              }
            }
          }
        }
      }
      elseif ($this->reader->nodeType == XMLREADER::END_ELEMENT) {
        // Trim currentPath as we exit each element
        unset($this->currentPath[$this->reader->depth]);
      }
    }

    migrate_instrument_stop('WordPressCommentXMLReader::next');
  }
}

class WordPressPostCommentXMLReader extends WordPressCommentXMLReader {
  public function __construct($xml_url, $element_query, $id_query) {
    parent::__construct($xml_url, $element_query, $id_query);
    $this->postType = 'post';
  }
}

class WordPressPageCommentXMLReader extends WordPressCommentXMLReader {
  public function __construct($xml_url, $element_query, $id_query) {
    parent::__construct($xml_url, $element_query, $id_query);
    $this->postType = 'page';
  }
}

/**
 * Implementation of WordPressMigration, for comments
 */
class WordPressComment extends WordPressMigration {
  /**
   * Set it up
   */
  public function __construct(array $arguments = array()) {
    parent::__construct($arguments);

    if ($arguments['source_post_type'] == 'page') {
      $reader_class = 'WordPressPageCommentXMLReader';
    }
    else {
      $reader_class = 'WordPressPostCommentXMLReader';
    }

    // comment_id is the unique ID of items in WordPress
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'wp:comment_id' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'description' => 'WordPress comment ID',
        )
      ),
      MigrateDestinationComment::getKeySchema()
    );

    $fields = array(
        'wp:post_id' => 'Unique ID of the item the comment is attached to',
        'wp:comment_id' => 'Unique ID of the comment',
        'wp:comment_author' => 'Name of comment author',
        'wp:comment_author_email' => 'Email address of comment author',
        'wp:comment_author_url' => 'URL of comment author',
        'wp:comment_author_IP' => 'IP address from which comment was posted',
        'wp:comment_date' => 'Date of comment (what timezone?)',
        'wp:comment_date_gmt' => 'Date of comment (GMT)',
        'wp:comment_content' => 'Body of comment',
        'wp:comment_approved' => '1/0/spam - spam comments will not be imported',
        'wp:comment_type' => '?',
        'wp:comment_parent' => 'comment_id (?) of parent comment',
        'wp:comment_user_id' => 'WordPress user ID of commenter (?)',
      );

    $source_options = array(
      'reader_class' => $reader_class,
      'cache_counts' => TRUE,
    );
    $this->source = new MigrateSourceXML($this->wxrFile, '/rss/channel/item/comment',
      'wp:comment_id', $fields, $source_options, $this->arguments['namespaces']);
    $this->destination = new MigrateDestinationComment('comment_node_' . $arguments['post_type']);

    // The basic mappings
    $this->addFieldMapping('nid', 'wp:post_id')
         ->xpath('wp:post_id')
         ->sourceMigration($this->arguments['dependencies']);
    $this->addFieldMapping('pid', 'wp:comment_parent')
         ->xpath('wp:comment_parent')
         ->sourceMigration($this->generateMachineName('WordPressComment'));
    $this->addFieldMapping('uid')
         ->description('Use email to match Drupal account; if no match, default to anonymous');
    $this->addFieldMapping('subject')
         ->description('No comment subjects in WP')
         ->issueGroup('DNM');
    $this->addFieldMapping('hostname', 'wp:comment_author_IP')
         ->xpath('wp:comment_author_IP');
    $this->addFieldMapping('created', 'wp:comment_date')
         ->xpath('wp:comment_date')
         ->callbacks('strtotime');
    $this->addFieldMapping('changed', 'wp:comment_date')
         ->xpath('wp:comment_date')
         ->callbacks('strtotime');
    $this->addFieldMapping(NULL, 'wp:comment_date_gmt')
         ->description('Using comment_date')
         ->issueGroup('DNM');
    $this->addFieldMapping('status', 'wp:comment_approved')
         ->xpath('wp:comment_approved')
         ->description('Do not import those with values of "spam"');
    $this->addFieldMapping('thread')
         ->issueGroup('DNM');
    $this->addFieldMapping('name', 'wp:comment_author')
         ->xpath('wp:comment_author')
         ->callbacks(array($this, 'truncateName'));
    $this->addFieldMapping('mail', 'wp:comment_author_email')
         ->xpath('wp:comment_author_email');
    $this->addFieldMapping('homepage', 'wp:comment_author_url')
         ->xpath('wp:comment_author_url');
    $this->addFieldMapping('language');
    $this->addFieldMapping(NULL, 'wp:comment_id')
         ->description('Source primary key')
         ->issueGroup('DNM');
    $this->addFieldMapping(NULL, 'wp:comment_user_id')
         ->description('Always 0?')
         ->issueGroup('DNM');
    $this->addFieldMapping(NULL, 'wp:comment_type')
         ->description('Always empty?')
         ->issueGroup('DNM');
    $this->addFieldMapping('comment_body', 'wp:comment_content')
         ->xpath('wp:comment_content');
    $this->addFieldMapping('comment_body:format')
         ->defaultValue($arguments['text_format_comment']);
    $this->addFieldMapping('comment_body:language');
  }

  /**
   * Names from Wordpress can be longer than 60 characters, truncate them.
   */
  protected function truncateName($value) {
    $value = substr($value, 0, 60);
    return $value;
  }

  /**
   * Implements Migration::prepareRow().
   * 
   * @param $row
   *
   * @return bool
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    // Reject spam
    if ($this->xpathValue($row->xml->xpath('wp:comment_approved')) == 'spam') {
      return FALSE;
    }

    // Ignore pingbacks if requested.
    if ($this->xpathValue($row->xml->xpath('wp:comment_type')) == 'pingback' &&
        $this->arguments['skip_pingbacks']) {
      return FALSE;
    }

    return TRUE;
  }

  /**
   * Prepare comment - called just before comment_save().
   *
   * @param stdClass $comment
   * @param stdClass $row
   */
  public function prepare(stdClass $comment, stdClass $row) {
    // Match creator email to Drupal account if possible; otherwise, use anonymous
    static $drupal_static_fast;
    if (!isset($drupal_static_fast)) {
      $drupal_static_fast['user_map'] = &drupal_static(__FUNCTION__);
    }
    $user_map = &$drupal_static_fast['user_map'];
    $comment_author_email = $this->xpathValue($row->xml->xpath('wp:comment_author_email'));
    if (!isset($user_map[$comment_author_email])) {
      $user_map[$comment_author_email] = db_select('users', 'u')
        ->fields('u', array('uid'))
        ->condition('mail', $row->{'wp:comment_author_email'})
        ->execute()
        ->fetchField();
      if (!$user_map[$comment_author_email]) {
        $user_map[$comment_author_email] = 0;
      }
    }
    $comment->uid = $user_map[$comment_author_email];
  }

  /**
   * Turn an array of XML objects returned by xpath() into a single string.
   *
   * @param $result
   *
   * @return string
   */
  public function xpathValue($result) {
    return (string)reset($result);
  }
}
