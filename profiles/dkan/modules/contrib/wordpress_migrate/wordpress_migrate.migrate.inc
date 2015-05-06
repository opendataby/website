<?php

/*
 * Implementation of hook_migrate_api().
 */
function wordpress_migrate_migrate_api() {
  $api = array(
    'api' => 2,
    'wizard classes' => array('WordPressMigrateWizard'),
  );
  return $api;
}

class WordPressMigrateWizard extends MigrateUIWizard {
  protected $filename;

  /**
   * Whether to perform author migration.
   *
   * @var bool
   */
  protected $authorMigration = TRUE;

  /**
   * User ID of the account to assign as author of any orphaned content.
   *
   * @var int
   */
  protected $defaultAuthorUid = 1;

  protected $blogPostType;
  protected $pageType;

  protected $contentValues = array();

  /**
   * List of namespaces referenced by the WXR file, keyed by prefix.
   *
   * @var array
   */
  protected $namespaces = array();

  /**
   * Lay out the basic steps of the wizard.
   */
  public function __construct() {
    parent::__construct();
//    $this->addStep(t('Overview'), 'overviewForm');
    $this->addStep(t('Upload blog'), 'sourceDataForm');
    $this->addStep(t('Select content to import'), 'contentSelectForm');
    $this->addStep(t('Review'), 'reviewForm');
  }

  /**
   * Identify ourselves.
   *
   * @return string
   */
  public function getSourceName() {
    return t('WordPress');
  }

  /**
   * First step - find out how to get the source data.
   */
  public function sourceDataForm(&$form_state) {
    // Make sure we have a private directory configured
    if (!variable_get('wordpress_migrate_private_path', '') &&
        !variable_get('file_private_path', '')) {
      $message = t('A private file system path must be <a href="@config">configured</a>
        to securely store your uploaded WordPress file.',
        array('@config' => url('admin/config/media/file-system', array('query' => array('destination' => current_path())))));
      $form['unconfigured'] = array(
        '#prefix' => '<div>',
        '#markup' => $message,
        '#suffix' => '</div>',
      );
      return $form;
    }
    $form['overview'] = array(
      '#prefix' => '<p>',
      '#markup' => t('This wizard supports importing into your Drupal site from ' .
        'a WordPress blog. To be able to use this wizard, you must have the ' .
        'address and credentials of the WordPress blog, or an XML file exported ' .
        'from the blog.'),
      '#suffix' => '</p>',
    );
    $form['description'] = array(
      '#prefix' => '<p>',
      '#markup' => t('You will be led through a series of steps, allowing you to ' .
        'customize what will be imported into Drupal and how it will be mapped. ' .
        'At the end of this process, a migration job will be '.
        'generated and you will be left at the Migrate dashboard, from which ' .
        'you can perform the import, monitor its progress, roll it back, etc.'),
      '#suffix' => '</p>',
    );

    if (module_exists('media') && !module_exists('migrate_extras')) {
      $form['need_extras'] = array(
        '#prefix' => '<div>',
        '#markup' => '<p>' . t('You have the <a href="@media">Media module</a> enabled - to
          take advantage of Media features, you need to also install and enable the
          <a href="@extras">Migrate Extras module</a>.' . '</p>',
          array('@media' => url('http://drupal.org/project/media'),
            '@extras' => url('http://drupal.org/project/migrate_extras'))),
        '#suffix' => '</div>',
      );
    }

    $form['source']['source_select'] = array(
      '#type' => 'radios',
      '#options' => array(0 => t('Import from a file'), 1 => t('Import from a URL')),
      '#default_value' => 0,
      '#attributes' => array('class' => array('container-inline')),
    );

    $form['#attributes'] = array('enctype' => 'multipart/form-data');
    $form['source']['wxr_file'] = array(
      '#type' => 'file',
      '#title' => t('WordPress exported file (WXR)'),
      '#description' => t('Select an exported WordPress file. Maximum file size is !size.',
        array('!size' => format_size(file_upload_max_size()))),
      '#states' => array(
        'visible' => array(
          ':input[name="source_select"]' => array('value' => 0),
        ),
      ),
    );

    $form['source']['credentials']['domain'] = array(
      '#type' => 'textfield',
      '#title' => t('Blog URL'),
      '#description' => t('Enter the URL of the blog to import (e.g. example.my-server.com). Note that some servers (in particular wordpress.com) will block remote access, preventing direct access - if you get a "Could not login" error you must manually export your blog from WordPress and import the file here.'),
      '#field_prefix' => 'http://',
      '#states' => array(
        'visible' => array(
          ':input[name="source_select"]' => array('value' => 1),
        ),
      ),
    );

    $form['source']['credentials']['username'] = array(
      '#type' => 'textfield',
      '#title' => t('Blog username'),
      '#description' => t(''),
      '#states' => array(
        'visible' => array(
          ':input[name="source_select"]' => array('value' => 1),
        ),
      ),
    );

    $form['source']['credentials']['password'] = array(
      '#type' => 'password',
      '#title' => t('Blog password'),
      '#description' => t(''),
      '#states' => array(
        'visible' => array(
          ':input[name="source_select"]' => array('value' => 1),
        ),
      ),
    );
    return $form;
  }

  /**
   * Fetch and preprocess the uploaded WXR file.
   *
   * @param array $form_state
   */
  protected function sourceDataFormValidate(&$form_state) {
    if ($_FILES['files']['error']['wxr_file'] && empty($form_state['values']['domain'])) {
      form_set_error('wxr_file', t('The file could not be uploaded, most likely
        because the file size exceeds the configured limit of !filesize',
        array('!filesize' => format_size(file_upload_max_size()))));
      return;
    }
    $directory = 'wordpress://';
    if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
      form_set_error('wxr_file',
        t('Could not prepare directory %directory - make sure your Drupal files directory exists and is writable',
          array('%directory' => $directory)));
      return;
    }

    $tmpfile = $_FILES['files']['tmp_name']['wxr_file'];
    // Note that for either path we take here, $tmpfile will be the name of
    // the uploaded/retrieved file, and $destination will be the name of the
    // desired final destination.
    if ($tmpfile) {
      // Handle uploaded file
      $filename = $_FILES['files']['name']['wxr_file'];
      $this->filename = $directory . str_replace(' ', '%20', $filename);
    }
    else {
      // Export the WordPress blog directly
      $domain = preg_replace('/http[s]?\:\/\//', '', $form_state['values']['domain']);

      // Login to the WordPress site
      $wordpress_version = 3;
      $login_url = 'http://' . $domain . '/wp-login.php';
      if (!($handle = fopen($login_url, 'r'))) {
        $wordpress_version = 2;
        $login_url = 'http://' . $domain . '/blog/wp-login.php';
        $handle = fopen($login_url, 'r');
      }
      if (!$handle) {
        form_set_error('credentials][domain', t('Could not find login page for !domain',
            array('!domain' => $domain)));
      }
      fclose($handle);

      // Use a temp file for cookies.
      $cookie_file = file_directory_temp() . '/wpimport-cookie.txt';

      $username = $form_state['values']['username'];
      $password = $form_state['values']['password'];
      $ch = curl_init();
      curl_setopt($ch, CURLOPT_URL, $login_url);
      curl_setopt($ch, CURLOPT_HEADER, 1);
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
      curl_setopt($ch, CURLOPT_USERAGENT, 'Importer');
      curl_setopt($ch, CURLOPT_COOKIESESSION, 1);
      curl_setopt($ch, CURLOPT_COOKIEJAR, $cookie_file);
      curl_setopt($ch, CURLOPT_COOKIEFILE, $cookie_file);
      curl_setopt($ch, CURLOPT_POST, 1);
      curl_setopt($ch, CURLOPT_POSTFIELDS, "log=$username&pwd=$password&testcookie=1");
      $login_result = curl_exec($ch);
      curl_close($ch);

      // Login successful? Grab the export
      if ((strpos($login_result, 'Set-Cookie: wordpress_logged_in')) ||
          (strpos($login_result, 'Set-Cookie: wordpressuser_')) ||
          (strpos($login_result, 'Set-Cookie: wordpress_test_cookie'))) {
        $filename = $domain . '.xml';
        // The "domain" may have included a subdirectory - flatten things out
        $this->filename = $directory . '/' . str_replace('/', '_', $filename);
        $tmpfile = tempnam(sys_get_temp_dir(), 'wp_');
        $export_url = 'http://' . $domain;
        if ($wordpress_version == 2) {
          $export_url .= '/blog';
        }
        $export_url .= '/wp-admin/export.php?mm_start=all&mm_end=all&author=all' .
          '&export_taxonomy[category]=0&export_taxonomy[post_tag]=0&export_post_type=all' .
          '&export_post_status=all&download=true';
        $fp = fopen($tmpfile, 'w');
        if ($fp) {
          $ch = curl_init();
          curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
          curl_setopt($ch, CURLOPT_FILE, $fp);
          curl_setopt($ch, CURLOPT_COOKIEFILE, $cookie_file);
          curl_setopt($ch, CURLOPT_URL, $export_url);
          curl_exec($ch);
          curl_close($ch);
          fclose($fp);
          unlink($cookie_file);
        }
        else {
          form_set_error('credentials][domain', t('Could not create destination file !filename',
            array('!filename' => $tmpfile)));
          return;
        }
      }
      else {
        form_set_error('credentials][domain', t('Could not login at !login_url',
          array('!login_url' => $login_url)));
        return;
      }
    }

    $this->namespaces = WordPressBlog::preprocessFile($tmpfile, $this->filename);

    // Only include the author step if we have author data (which was introduced
    // in WXR 1.1)
    $blog = wordpress_migrate_blog($this->filename);
    if ($blog->getWxrVersion() != '1.0') {
      $this->addStep(t('Authors'), 'authorForm', $this->currentStep);
    }
    else {
      $this->authorMigration = FALSE;
      global $user;
      $this->defaultAuthorUid = $user->uid;
    }
    // Truncate the groupName so map/message table names don't get too long.
    $this->groupName = substr($blog->getTitle(), 0, 63 - strlen('migrate_message_blogpostcomment'));
    $this->groupTitle = t('!title (!url)',
      array('!title' => $blog->getDisplayTitle(), '!url' => $blog->getBlogUrl()));
  }

  /**
   * Present information and options around user migration.
   */
  protected function authorForm(&$form_state) {
    $form['overview'] = array(
      '#prefix' => '<p>',
      '#markup' => t('User accounts for authors in the WordPress blog may be
        imported to Drupal. If you select <strong>Yes</strong>, any authors in
        the WordPress file who do not match existing Drupal accounts (based on
        email address) will have new Drupal accounts automatically created.
        Note that their passwords are not imported - they must be reset after
        import.<br/>
        If you select <strong>No</strong>, you must choose an existing Drupal
        account which will be the author of any WordPress content whose author
        is not imported. '),
      '#suffix' => '</p>',
    );

    $form['do_migration'] = array(
      '#type' => 'radios',
      '#title' => t('Create new users for existing WordPress content authors?'),
      '#options' => array(1 => t('Yes'), 0 => t('No')),
      '#default_value' => 1,
    );

    global $user;
    $form['default_author'] = array(
      '#type' => 'textfield',
      '#title' => t('Default content author:'),
      '#default_value' => $user->name,
      '#autocomplete_path' => 'user/autocomplete',
      '#states' => array(
        'invisible' => array(
          'input[name="do_migration"]' => array('value' => 1),
        ),
      ),
    );

    return $form;
  }

  /**
   * Prepare for registration of any user-related migrations.
   *
   * @param array $form_state
   */
  protected function authorFormValidate(&$form_state) {
    if ($form_state['values']['do_migration']) {
      $this->authorMigration = TRUE;
    }
    else {
      $this->authorMigration = FALSE;
    }
    $account = user_load_by_name($form_state['values']['default_author']);
    $this->defaultAuthorUid = $account->uid;
  }

  protected function contentSelectForm(&$form_state) {
    $form['overview'] = array(
      '#prefix' => '<p>',
      '#markup' => t('WordPress blogs contain two primary kinds of content,
        blog posts and pages. Here you may choose what types of Drupal nodes
        to create from each of those content types, or omit one or both from
        the import entirely.'),
      '#suffix' => '</p>',
    );

    // Get destination node type(s)
    $node_types = node_type_get_types();
    $options = array('' => t('Do not import'));
    foreach ($node_types as $node_type => $info) {
      $options[$node_type] = $info->name;
    }

    if (isset($options['blog'])) {
      $default = 'blog';
    }
    else {
      $default = '';
    }

    $form['blog_post_type'] = array(
      '#type' => 'select',
      '#title' => t('Import WordPress blog posts as'),
      '#default_value' => $default,
      '#options' => $options,
      '#description' => t(''),
    );

    if (isset($options['page'])) {
      $default = 'page';
    }
    else {
      $default = '';
    }

    $form['page_type'] = array(
      '#type' => 'select',
      '#title' => t('Import WordPress pages as'),
      '#default_value' => $default,
      '#options' => $options,
      '#description' => t(''),
    );
    return $form;
  }

  protected function contentSelectFormValidate(&$form_state) {
    // Start clean in case we came here via Previous.
    unset($this->contentValues['blog']);
    unset($this->contentValues['page']);
    $this->removeStep(t('Blog posts'));
    $this->removeStep(t('Pages'));

    $this->contentValues['page']['page_type'] = $form_state['values']['page_type'];
    if ($this->contentValues['page']['page_type']) {
      $this->addStep(t('Pages'), 'contentPageForm', $this->currentStep);
    }
    $this->contentValues['blog']['post_type'] = $form_state['values']['blog_post_type'];
    if ($this->contentValues['blog']['post_type']) {
      $this->addStep(t('Blog posts'), 'contentBlogPostForm', $this->currentStep);
    }
  }

  protected function contentBlogPostForm(&$form_state) {
    $form['overview'] = array(
      '#prefix' => '<p>',
      '#markup' => t('There are several options you may set for the import of
        WordPress blog posts.'),
      '#suffix' => '</p>',
    );
    return $form + $this->contentForm($form_state, $this->contentValues['blog']['post_type']);
  }

  protected function contentPageForm(&$form_state) {
    $form['overview'] = array(
      '#prefix' => '<p>',
      '#markup' => t('There are several options you may set for the import of
        WordPress pages.'),
      '#suffix' => '</p>',
    );
    return $form + $this->contentForm($form_state, $this->contentValues['page']['page_type']);
  }

  /**
   * Form for mapping source content (node) types to destination types.
   */
  protected function contentForm(&$form_state, $selected_post_type) {
    $form = array();

    $empty_field = array(
       '#type' => 'value',
       '#value' => '',
     );

    $vocabs = $this->vocabularies($selected_post_type);
    if (!empty($vocabs)) {
      $options = array('' => t('Do not import'));
      foreach ($vocabs as $machine_name => $name) {
        $options[$machine_name] = $name;
      }

      // If field_tags exists, default to it.
      $tags_default = (isset($options['field_tags']) ? 'field_tags' : '');
      $form['tag_field'] = array(
        '#type' => 'select',
        '#title' => t('Import WordPress tags to the term reference field'),
        '#default_value' => $tags_default,
        '#options' => $options,
      );

      $form['category_field'] = array(
        '#type' => 'select',
        '#title' => t('Import WordPress categories to the term reference field'),
        '#default_value' => '',
        '#options' => $options,
      );
    }
    else {
      $form['tag_field'] = $form['category_field'] = $empty_field;
    }

    if (module_exists('comment') &&
        (variable_get('comment_' . $selected_post_type, COMMENT_NODE_OPEN)
         != COMMENT_NODE_CLOSED)) {
      $form['comments'] = array(
        '#type' => 'radios',
        '#title' => t('Import comments?'),
        '#options' => array(1 => t('Yes'), 0 => t('No')),
        '#default_value' => 1,
      );
      $form['pingbacks'] = array(
        '#type' => 'radios',
        '#title' => t('Ignore pingbacks?'),
        '#options' => array(1 => t('Yes'), 0 => t('No')),
        '#default_value' => 1,
      );
    }
    else {
      $form['comments'] = array(
        '#type' => 'value',
        '#value' => 0,
      );
      $form['pingbacks'] = array(
        '#type' => 'value',
        '#value' => 0,
      );
    }

    $file_fields = array('' => t('Do not import'));
    $file_fields += $this->fileFields($selected_post_type, 'file')
      + $this->fileFields($selected_post_type, 'media');
    $file_image_fields = $file_fields +
                         $this->fileFields($selected_post_type, 'image');
    if (count($file_image_fields) > 1) {
      $form['attachment_field'] = array(
        '#type' => 'select',
        '#title' => t('Field for attachments (including images)'),
        '#default_value' => '',
        '#options' => $file_image_fields,
        '#description' => t(''),
        '#states' => array(
          'visible' => array(
            'input[name="destination_type"]' => array('value' => 'blog'),
          ),
        ),
      );
    }
    else {
      $form['attachment_field'] = $empty_field;
    }
    if (count($file_fields) > 1) {
      $form['podcast_field'] = array(
        '#type' => 'select',
        '#title' => t('Field for Blubrry PowerPress podcasts'),
        '#default_value' => '',
        '#options' => $file_fields,
        '#description' => t(''),
      );
    }
    else {
      $form['podcast_field'] = $empty_field;
    }

    $options = array();
    foreach (filter_formats() as $format_id => $format) {
      $options[$format_id] = $format->name;
    }
    $form['text_format'] = array(
      '#type' => 'select',
      '#title' => t('Default format for text fields'),
      '#default_value' => 'filtered_html',
      '#options' => $options,
      '#description' => t(''),
    );
    $form['text_format_comment'] = array(
      '#type' => 'select',
      '#title' => t('Default format for comment text fields'),
      '#default_value' => 'filtered_html',
      '#options' => $options,
      '#description' => t(''),
      '#states' => array(
        'invisible' => array(
          'input[name="comments"]' => array('value' => 0),
        ),
      ),
    );

    if (module_exists('path')) {
      $options = array(
        0 => t('Do not set path aliases'),
        1 => t('Set path aliases to their original WordPress values'),
      );
      $attributes = array();
      $default_value = 1;
      if (module_exists('pathauto')) {
        $options[2] = t('Have pathauto generate new aliases');
        if (!module_exists('migrate_extras')) {
          $form['pathauto_message'] = array(
            '#prefix' => '<p>',
            '#markup' => t('<strong>To be able to change the <em>Path alias handling</em>, ' .
              'you must have the <a href="@extras">Migrate Extras module</a> installed and enabled.</strong>',
                 array('@extras' => url('http://drupal.org/project/migrate_extras'))),
            '#suffix' => '</p>',
          );
          $attributes['disabled'] = TRUE;
          $default_value = 2;
        }
      }
      $form['path_action'] = array(
        '#type' => 'radios',
        '#title' => t('Path alias handling'),
        '#description' => t('Select how path aliases for imported nodes will be set.'),
        '#options' => $options,
        '#default_value' => $default_value,
        '#attributes' => $attributes,
      );
    }
    else {
      $form['path_action'] = $empty_field;
    }

    if (module_exists('redirect')) {
      if (class_exists('MigrateRedirectEntityHandler')) {
        $form['generate_redirects'] = array(
          '#type' => 'checkbox',
          '#title' => t('Generate redirects'),
          '#description' => t('If this box is checked, redirects will be set up from
            the former WordPress blog URLs to the new URLs on your Drupal site'),
          '#default_value' => FALSE,
        );
      }
      else {
        $form['generate_redirects'] = array(
          '#type' => 'value',
          '#value' => 0,
        );
        $form['generate_redirects_info'] = array(
          '#prefix' => '<p>',
          '#markup' => t('You have the Redirect module enabled. To be able to '
            . 'generate redirects for your imported WordPress content, you need '
            . 'to <a href="@link">patch Redirect</a>.',
            array('@link' => 'http://drupal.org/node/1116408#comment-6040494')),
          '#suffix' => '</p>',
        );
      }
    }
    else {
      $form['generate_redirects'] = $empty_field;
    }

    return $form;
  }

  /**
   * Save the selected type mappings, as an array keyed by source type and
   * containing the destination type (bundle).
   */
  protected function contentBlogPostFormValidate(&$form_state) {
    $this->contentValues['blog'] += $form_state['values'];
  }

  /**
   * Save the selected type mappings, as an array keyed by source type and
   * containing the destination type (bundle).
   */
  protected function contentPageFormValidate(&$form_state) {
    $this->contentValues['page'] += $form_state['values'];
  }

  /**
   * Show the user what they've chosen to migrate, and give them one last chance
   * to say yay or nay.
   */
  protected function reviewForm(&$form_state) {
    // In case we've been going back-and-forth with Previous, make sure we
    // start with no migrations - all migrations will be added here.
    $this->migrations = array();

    $blog = wordpress_migrate_blog($this->filename);
    $migration_classes = $blog->migrationClasses();

    $this->groupArguments = array(
      'filename' => $this->filename,
      'source_system' => $this->getSourceName(),
      'namespaces' => $this->namespaces,
    );

    $message = t('<p>Please review your migration configuration. When you submit this
      form, migration processes will be created and you will be left at the
      migration dashboard.</p>');

    $form['description'] = array(
      '#prefix' => '<div>',
      '#markup' => $message,
      '#suffix' => '</div>',
    );
    $migrations = '';
    $account = user_load($this->defaultAuthorUid);
    if ($this->authorMigration) {
      $migrations .= t('<li>WordPress authors will be imported.</li>');
    }
    else {
      $migrations .= t('<li>WordPress authors will not be imported. The default ' .
        'author for any content whose author can\'t be identified will be %default.</li>',
                       array('%default' => $account->name));
    }
    $arguments = array(
      'default_author_uid' => $this->defaultAuthorUid,
      'import_users' => $this->authorMigration,
    );
    $this->addMigration('Author', $migration_classes['WordPressAuthor'], $arguments);

    $attachment_arguments = array();

    if ($this->contentValues['blog']['post_type']) {
      $migrations .= t('<li>WordPress blog posts will be imported to %type nodes.</li>',
        array('%type' => $this->contentValues['blog']['post_type']));
      $arguments = array(
        'dependencies' => array('Author'),
        'post_type' => $this->contentValues['blog']['post_type'],
        'tag_field' => $this->contentValues['blog']['tag_field'],
        'category_field' => $this->contentValues['blog']['category_field'],
        'attachment_field' => $this->contentValues['blog']['attachment_field'],
        'podcast_field' => $this->contentValues['blog']['podcast_field'],
        'text_format' => $this->contentValues['blog']['text_format'],
        'path_action' => $this->contentValues['blog']['path_action'],
        'generate_redirects' => $this->contentValues['blog']['generate_redirects'],
      );
      if ($arguments['tag_field']) {
        $tag_vocabulary = $this->getVocabulary($arguments['tag_field']);
        $tag_arguments = array('tag_vocabulary' => $tag_vocabulary);
        $arguments['tag_migration'] = 'Tag' . $tag_vocabulary;
        $arguments['dependencies'][] = $arguments['tag_migration'];
        $this->addMigration($arguments['tag_migration'], $migration_classes['WordPressTag'],
                            $tag_arguments);
      }
      if ($arguments['category_field']) {
        $category_vocabulary = $this->getVocabulary($arguments['category_field']);
        $category_arguments = array('category_vocabulary' => $category_vocabulary);
        $arguments['category_migration'] = 'Category' . $category_vocabulary;
        $arguments['dependencies'][] = $arguments['category_migration'];
        $this->addMigration($arguments['category_migration'], $migration_classes['WordPressCategory'],
                            $category_arguments);
      }
      $this->addMigration('BlogPost', $migration_classes['WordPressBlogEntry'], $arguments);
      $attachment_arguments['dependencies'][] = 'BlogPost';
      $attachment_arguments['blog_attachment_field'] =
        $this->contentValues['blog']['attachment_field'];
      if ($this->contentValues['blog']['comments']) {
        $migrations .= t('<li>WordPress blog post comments will be imported.</li>');
        $arguments = array(
          'post_type' => $this->contentValues['blog']['post_type'],
          'source_post_type' => 'post',
          'dependencies' => array('BlogPost'),
          'text_format_comment' => $this->contentValues['blog']['text_format_comment'],
          'skip_pingbacks' => $this->contentValues['blog']['pingbacks'],
        );
        $this->addMigration('BlogPostComment', $migration_classes['WordPressComment'], $arguments);
      }
      else {
        $migrations .= t('<li>WordPress blog post comments will not be imported.</li>');
      }
    }
    else {
      $migrations .= t('<li>WordPress blog posts and their comments will not be imported.</li>');
    }
    if ($this->contentValues['page']['page_type']) {
      $migrations .= t('<li>WordPress pages will be imported to %type nodes.</li>',
        array('%type' => $this->contentValues['page']['page_type']));
      $arguments = array(
        'dependencies' => array('Author'),
        'page_type' => $this->contentValues['page']['page_type'],
        'tag_field' => $this->contentValues['page']['tag_field'],
        'category_field' => $this->contentValues['page']['category_field'],
        'attachment_field' => $this->contentValues['page']['attachment_field'],
        'podcast_field' => $this->contentValues['page']['podcast_field'],
        'text_format' => $this->contentValues['page']['text_format'],
        'path_action' => $this->contentValues['page']['path_action'],
        'generate_redirects' => $this->contentValues['page']['generate_redirects'],
      );

      $this->addMigration('Page', $migration_classes['WordPressPage'], $arguments);
      $attachment_arguments['dependencies'][] = 'Page';
      $attachment_arguments['page_attachment_field'] =
        $this->contentValues['page']['attachment_field'];

      if ($this->contentValues['page']['comments']) {
        $migrations .= t('<li>WordPress page comments will be imported.</li>');
        $arguments = array(
          'post_type' => $this->contentValues['page']['page_type'],
          'source_post_type' => 'page',
          'dependencies' => array('Page'),
          'text_format_comment' => $this->contentValues['page']['text_format_comment'],
          'skip_pingbacks' => $this->contentValues['page']['pingbacks'],
        );
        $this->addMigration('PageComment', $migration_classes['WordPressComment'], $arguments);
      }
      else {
        $migrations .= t('<li>WordPress page comments will not be imported.</li>');
      }
    }
    else {
      $migrations .= t('<li>WordPress pages and their comments will not be imported.</li>');
    }
    $this->addMigration('Attachment', $migration_classes['WordPressAttachment'],
                        $attachment_arguments);

    $form['migration_list'] = array(
      '#prefix' => '<ol>',
      '#markup' => $migrations,
      '#suffix' => '</ol>',
    );

    return $form;
  }

  /**
   * Return a list of vocabularies attached to a given node type (bundle).
   *
   * @param $node_type
   * @return array
   */
  protected function vocabularies($node_type) {
    $fields = field_info_instances('node', $node_type);
    $term_fields = array();
    foreach ($fields as $field_name => $instance_info) {
      $field_info = field_info_field($field_name);
      if ($field_info['type'] == 'taxonomy_term_reference') {
        $term_fields[$field_name] = $instance_info['label'];
      }
    }
    return $term_fields;
  }

  /**
   * Get the (first, if multiple) vocabulary assigned to the named field.
   *
   * @param $field_name
   *
   * @return string|null
   */
  protected function getVocabulary($field_name) {
    $field_info = field_info_field($field_name);
    if ($field_info['type'] == 'taxonomy_term_reference') {
      return $field_info['settings']['allowed_values'][0]['vocabulary'];
    }
    return NULL;
  }

  /**
   * Return a list of file fields attached to a given node type (bundle).
   *
   * @param $node_type
   * @param $file_type
   * @return array
   */
  protected function fileFields($node_type, $file_type) {
    $fields = field_info_instances('node', $node_type);
    $file_fields = array();
    foreach ($fields as $field_name => $instance_info) {
      $field_info = field_info_field($field_name);
      if ($field_info['type'] == $file_type) {
        $file_fields[$field_name] = $instance_info['label'];
      }
    }
    return $file_fields;
  }
}
