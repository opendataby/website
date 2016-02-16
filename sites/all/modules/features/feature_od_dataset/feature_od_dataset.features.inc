<?php
/**
 * @file
 * feature_od_dataset.features.inc
 */

/**
 * Implements hook_strongarm_alter().
 */
function feature_od_dataset_strongarm_alter(&$data) {
  if (isset($data['pathauto_node_dataset_pattern'])) {
    unset($data['pathauto_node_dataset_pattern']);
  }
  if (isset($data['pathauto_node_resource_pattern'])) {
    unset($data['pathauto_node_resource_pattern']);
  }
}
