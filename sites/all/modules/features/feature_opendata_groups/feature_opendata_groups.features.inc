<?php
/**
 * @file
 * feature_opendata_groups.features.inc
 */

/**
 * Implements hook_field_default_field_instances_alter().
 */
function feature_opendata_groups_field_default_field_instances_alter(&$data) {
  if (isset($data['node-dataset-og_group_ref'])) {
    unset($data['node-dataset-og_group_ref']);
  }
}

/**
 * Implements hook_strongarm_alter().
 */
function feature_opendata_groups_strongarm_alter(&$data) {
  if (isset($data['pathauto_node_group_pattern'])) {
    unset($data['pathauto_node_group_pattern']);
  }
}

/**
 * Implements hook_views_default_views_alter().
 */
function feature_opendata_groups_views_default_views_alter(&$data) {
  if (isset($data['dkan_group_members'])) {
    unset($data['dkan_group_members']);
  }
  if (isset($data['dkan_og_extras_group_members'])) {
    unset($data['dkan_og_extras_group_members']);
  }
  if (isset($data['group_block'])) {
    unset($data['group_block']);
  }
  if (isset($data['groups_page'])) {
    unset($data['groups_page']);
  }
  if (isset($data['groups_search'])) {
    unset($data['groups_search']);
  }
  if (isset($data['og_count'])) {
    unset($data['og_count']);
  }
}
