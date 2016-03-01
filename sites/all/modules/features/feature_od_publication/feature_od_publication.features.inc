<?php
/**
 * @file
 * feature_od_publication.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function feature_od_publication_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function feature_od_publication_node_info() {
  $items = array(
    'publication' => array(
      'name' => t('Публикация'),
      'base' => 'node_content',
      'description' => t('Публикация'),
      'has_title' => '1',
      'title_label' => t('Заголовок'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
