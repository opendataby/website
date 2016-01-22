<?php
/**
 * @file
 * opendata_dataset_content_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function opendata_dataset_content_types_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_field_default_field_bases_alter().
 */
function opendata_dataset_content_types_field_default_field_bases_alter(&$data) {
  if (isset($data['field_author'])) {
    unset($data['field_author']);
  }
  if (isset($data['field_frequency'])) {
    unset($data['field_frequency']);
  }
  if (isset($data['field_public_access_level'])) {
    unset($data['field_public_access_level']);
  }
  if (isset($data['field_tags'])) {
    unset($data['field_tags']);
  }
}

/**
 * Implements hook_field_group_info_alter().
 */
function opendata_dataset_content_types_field_group_info_alter(&$data) {
  if (isset($data['group_additional|node|dataset|form'])) {
    unset($data['group_additional|node|dataset|form']);
  }
  if (isset($data['group_link_api|node|resource|form'])) {
    unset($data['group_link_api|node|resource|form']);
  }
  if (isset($data['group_link_file|node|resource|form'])) {
    unset($data['group_link_file|node|resource|form']);
  }
  if (isset($data['group_primary|node|dataset|form'])) {
    unset($data['group_primary|node|dataset|form']);
  }
}

/**
 * Implements hook_field_default_field_instances_alter().
 */
function opendata_dataset_content_types_field_default_field_instances_alter(&$data) {
  if (isset($data['node-dataset-body'])) {
    unset($data['node-dataset-body']);
  }
  if (isset($data['node-dataset-field_additional_info'])) {
    unset($data['node-dataset-field_additional_info']);
  }
  if (isset($data['node-dataset-field_author'])) {
    unset($data['node-dataset-field_author']);
  }
  if (isset($data['node-dataset-field_contact_email'])) {
    unset($data['node-dataset-field_contact_email']);
  }
  if (isset($data['node-dataset-field_contact_name'])) {
    unset($data['node-dataset-field_contact_name']);
  }
  if (isset($data['node-dataset-field_data_dictionary'])) {
    unset($data['node-dataset-field_data_dictionary']);
  }
  if (isset($data['node-dataset-field_frequency'])) {
    unset($data['node-dataset-field_frequency']);
  }
  if (isset($data['node-dataset-field_granularity'])) {
    unset($data['node-dataset-field_granularity']);
  }
  if (isset($data['node-dataset-field_license'])) {
    unset($data['node-dataset-field_license']);
  }
  if (isset($data['node-dataset-field_public_access_level'])) {
    unset($data['node-dataset-field_public_access_level']);
  }
  if (isset($data['node-dataset-field_related_content'])) {
    unset($data['node-dataset-field_related_content']);
  }
  if (isset($data['node-dataset-field_resources'])) {
    unset($data['node-dataset-field_resources']);
  }
  if (isset($data['node-dataset-field_spatial'])) {
    unset($data['node-dataset-field_spatial']);
  }
  if (isset($data['node-dataset-field_spatial_geographical_cover'])) {
    unset($data['node-dataset-field_spatial_geographical_cover']);
  }
  if (isset($data['node-dataset-field_tags'])) {
    unset($data['node-dataset-field_tags']);
  }
  if (isset($data['node-dataset-field_temporal_coverage'])) {
    unset($data['node-dataset-field_temporal_coverage']);
  }
  if (isset($data['node-resource-body'])) {
    unset($data['node-resource-body']);
  }
  if (isset($data['node-resource-field_dataset_ref'])) {
    unset($data['node-resource-field_dataset_ref']);
  }
  if (isset($data['node-resource-field_format'])) {
    unset($data['node-resource-field_format']);
  }
  if (isset($data['node-resource-field_link_remote_file'])) {
    unset($data['node-resource-field_link_remote_file']);
  }
  if (isset($data['node-resource-field_upload'])) {
    unset($data['node-resource-field_upload']);
  }
}

/**
 * Implements hook_taxonomy_default_vocabularies_alter().
 */
function opendata_dataset_content_types_taxonomy_default_vocabularies_alter(&$data) {
  if (isset($data['format'])) {
    unset($data['format']);
  }
  if (isset($data['tags'])) {
    unset($data['tags']);
  }
}

/**
 * Implements hook_strongarm_alter().
 */
function opendata_dataset_content_types_strongarm_alter(&$data) {
  if (isset($data['field_bundle_settings_node__dataset'])) {
    unset($data['field_bundle_settings_node__dataset']);
  }
}
