<?php

/**
 * @file
 *
 * Support for migrating categories from a WordPress blog into Drupal.
 */

/**
 * Implementation of WordPressMigration, for categories
 */
class WordPressCategory extends WordPressMigration {
  /**
   * Set it up
   */
  public function __construct(array $arguments = array()) {
    parent::__construct($arguments);

    // The "nicename" is what we would call the machine name, the unique
    // identifier of a category.
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'wp:category_nicename' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'WordPress category machine name',
        )
      ),
      MigrateDestinationTerm::getKeySchema()
    );

    $fields = array(
      'wp:category_nicename' => 'Unique "machine name" of the category',
      'wp:category_parent' => 'Category parent (nicename?)',
      'wp:cat_name' => 'User-friendly category name',
      'wp:category_description' => 'Description of category',
    );

    // Construct the source and destination objects.
    $source_options = array(
      'reader_class' => 'MigrateXMLReader',
      'cache_counts' => TRUE,
    );
    $this->source = new MigrateSourceXML($this->wxrFile, '/rss/channel/category',
      'wp:category_nicename', $fields, $source_options, $this->arguments['namespaces']);
    $this->destination = new MigrateDestinationTerm($this->arguments['category_vocabulary']);

    // The basic mappings
    $this->addFieldMapping('name', 'wp:cat_name')
         ->xpath('wp:cat_name')
         ->callbacks('html_entity_decode');
    $this->addFieldMapping('description', 'wp:category_description')
         ->xpath('wp:category_description')
         ->callbacks('html_entity_decode');
    $this->addFieldMapping('parent', 'wp:category_parent')
         ->sourceMigration($this->machineName)
         ->xpath('wp:category_parent');

    // Unmapped destination fields
    $this->addFieldMapping('parent_name');
    $this->addFieldMapping('format');
    $this->addFieldMapping('weight');
    $this->addFieldMapping('path');
  }
}
