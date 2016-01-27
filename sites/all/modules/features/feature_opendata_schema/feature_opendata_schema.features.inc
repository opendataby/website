<?php
/**
 * @file
 * feature_opendata_schema.features.inc
 */

/**
 * Implements hook_open_data_schema_apis_defaults_alter().
 */
function feature_opendata_schema_open_data_schema_apis_defaults_alter(&$data) {
  if (isset($data['ckan_current_package_list_with_resources'])) {
    unset($data['ckan_current_package_list_with_resources']);
  }
  if (isset($data['ckan_group_list'])) {
    unset($data['ckan_group_list']);
  }
  if (isset($data['ckan_group_package_show'])) {
    unset($data['ckan_group_package_show']);
  }
  if (isset($data['ckan_package_list'])) {
    unset($data['ckan_package_list']);
  }
  if (isset($data['ckan_package_show'])) {
    unset($data['ckan_package_show']);
  }
  if (isset($data['ckan_resource_show'])) {
    unset($data['ckan_resource_show']);
  }
  if (isset($data['data_json'])) {
    unset($data['data_json']);
  }
  if (isset($data['data_json_1_1'])) {
    unset($data['data_json_1_1']);
  }
}
