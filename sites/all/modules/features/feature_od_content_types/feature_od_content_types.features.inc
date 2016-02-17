<?php
/**
 * @file
 * feature_od_content_types.features.inc
 */

/**
 * Implements hook_field_default_field_bases_alter().
 */
function feature_od_content_types_field_default_field_bases_alter(&$data) {
  if (isset($data['field_upload'])) {
    unset($data['field_upload']);
  }
}

/**
 * Implements hook_field_default_field_instances_alter().
 */
function feature_od_content_types_field_default_field_instances_alter(&$data) {
  if (isset($data['node-resource-field_upload'])) {
    unset($data['node-resource-field_upload']);
  }
}
