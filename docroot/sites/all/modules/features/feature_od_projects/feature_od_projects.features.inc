<?php
/**
 * @file
 * feature_od_projects.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function feature_od_projects_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function feature_od_projects_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function feature_od_projects_node_info() {
  $items = array(
    'project' => array(
      'name' => t('Проект'),
      'base' => 'node_content',
      'description' => t('Тип контента Проект'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
