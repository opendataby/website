<?php
/**
 * @file
 * dkan_dataset_content_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function dkan_dataset_content_types_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function dkan_dataset_content_types_node_info() {
  $items = array(
    'dataset' => array(
      'name' => t('Набор данных'),
      'base' => 'node_content',
      'description' => t('Набор данных - это контейнер для нескольких файлов с данными по определенной теме. В свою очередь, файлы с данными имеют уникальный адрес и описание лицензии. '),
      'has_title' => '1',
      'title_label' => t('Заголовок'),
      'help' => '',
    ),
    'resource' => array(
      'name' => t('Русурс'),
      'base' => 'node_content',
      'description' => t('Данные - это файл или ссылка на файл с данными.'),
      'has_title' => '1',
      'title_label' => t('Заголовок'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implements hook_rdf_default_mappings().
 */
function dkan_dataset_content_types_rdf_default_mappings() {
  $rdf_mappings = array();

  // Exported RDF mapping: resource
  $rdf_mappings['node']['resource'] = array(
    'rdftype' => array(
      0 => 'sioc:Item',
      1 => 'foaf:Document',
    ),
    'title' => array(
      'predicates' => array(
        0 => 'dc:title',
      ),
    ),
    'created' => array(
      'predicates' => array(
        0 => 'dc:date',
        1 => 'dc:created',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'changed' => array(
      'predicates' => array(
        0 => 'dc:modified',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'body' => array(
      'predicates' => array(
        0 => 'content:encoded',
      ),
    ),
    'uid' => array(
      'predicates' => array(
        0 => 'sioc:has_creator',
      ),
      'type' => 'rel',
    ),
    'name' => array(
      'predicates' => array(
        0 => 'foaf:name',
      ),
    ),
    'comment_count' => array(
      'predicates' => array(
        0 => 'sioc:num_replies',
      ),
      'datatype' => 'xsd:integer',
    ),
    'last_activity' => array(
      'predicates' => array(
        0 => 'sioc:last_activity_date',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
  );

  // Exported RDF mapping: dataset
  $rdf_mappings['node']['dataset'] = array(
    'rdftype' => array(
      0 => 'sioc:Item',
      1 => 'foaf:Document',
    ),
    'title' => array(
      'predicates' => array(
        0 => 'dc:title',
      ),
      'type' => 'property',
    ),
    'created' => array(
      'predicates' => array(
        0 => 'dc:date',
        1 => 'dc:created',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'changed' => array(
      'predicates' => array(
        0 => 'dc:modified',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'body' => array(
      'predicates' => array(
        0 => 'content:encoded',
      ),
      'type' => 'property',
    ),
    'uid' => array(
      'predicates' => array(
        0 => 'sioc:has_creator',
      ),
      'type' => 'rel',
    ),
    'name' => array(
      'predicates' => array(
        0 => 'foaf:name',
      ),
    ),
    'comment_count' => array(
      'predicates' => array(
        0 => 'sioc:num_replies',
      ),
      'datatype' => 'xsd:integer',
    ),
    'last_activity' => array(
      'predicates' => array(
        0 => 'sioc:last_activity_date',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'field_frequency' => array(
      'type' => 'property',
      'predicates' => array(
        0 => 'dc:Frequency',
      ),
    ),
    'field_resources' => array(
      'type' => 'property',
      'predicates' => array(
        0 => 'dcat:Distribution',
      ),
    ),
    'field_author' => array(
      'type' => 'property',
      'predicates' => array(
        0 => 'dc:creator',
      ),
    ),
    'field_data_dictionary' => array(
      'type' => 'property',
      'predicates' => array(
        0 => 'dcat:dataDictionary',
      ),
    ),
    'field_granularity' => array(
      'type' => 'property',
      'predicates' => array(
        0 => 'dcat:granularity',
      ),
    ),
    'field_license' => array(
      'type' => 'property',
      'predicates' => array(
        0 => 'dc:license',
      ),
    ),
    'field_public_access_level' => array(
      'type' => 'property',
      'predicates' => array(
        0 => 'dc:accessRights',
      ),
    ),
    'field_related_content' => array(
      'type' => 'property',
      'predicates' => array(
        0 => 'dc:relation',
      ),
    ),
    'field_spatial' => array(
      'type' => 'property',
      'predicates' => array(
        0 => 'dc:spatial',
      ),
    ),
    'field_tags' => array(
      'type' => 'property',
      'predicates' => array(
        0 => 'dcat:theme',
      ),
    ),
    'field_temporal_coverage' => array(
      'type' => 'property',
      'predicates' => array(
        0 => 'dc:temporal',
      ),
    ),
    'og_group_ref' => array(
      'type' => 'property',
      'predicates' => array(
        0 => 'dc:publisher',
      ),
    ),
  );

  return $rdf_mappings;
}
