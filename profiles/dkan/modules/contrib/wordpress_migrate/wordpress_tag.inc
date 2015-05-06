<?php

/**
 * @file
 *
 * Support for migrating tags from a WordPress blog into Drupal.
 */

/**
 * Implementation of WordPressMigration, for tags
 */
class WordPressTag extends WordPressMigration {
  /**
   * Set it up
   */
  public function __construct(array $arguments = array()) {
    parent::__construct($arguments);

    // The slug is what we would call the machine name, the unique
    // identifier of a tag.
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'wp:tag_slug' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
          'description' => 'WordPress tag machine name',
        )
      ),
      MigrateDestinationTerm::getKeySchema()
    );

    $fields = array(
        'wp:tag_slug' => 'Unique "machine name" of the tag',
        'wp:tag_name' => 'User-friendly tag name',
        'wp:tag_description' => 'Description of tag',
    );

    // Construct the source and destination objects.
    $source_options = array(
      'reader_class' => 'MigrateXMLReader',
      'cache_counts' => TRUE,
    );
    $this->source = new MigrateSourceXML($this->wxrFile, '/rss/channel/tag',
      'wp:tag_slug', $fields, $source_options, $this->arguments['namespaces']);
    $this->destination = new MigrateDestinationTerm($arguments['tag_vocabulary']);

    // The basic mappings
    $this->addFieldMapping('name', 'wp:tag_name')
         ->xpath('wp:tag_name')
         ->callbacks('html_entity_decode');
    $this->addFieldMapping('description', 'wp:tag_description')
         ->xpath('wp:tag_description')
         ->callbacks('html_entity_decode');
    $this->addFieldMapping('parent_name')
         ->issueGroup('DNM');

    // Unmapped destination fields
    $this->addFieldMapping('parent');
    $this->addFieldMapping('format');
    $this->addFieldMapping('weight');
    $this->addFieldMapping('path');
  }
}
