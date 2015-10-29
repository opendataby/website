<?php
/**
 * @file
 * feature_opendata_dataset.features.inc
 */

/**
 * Implements hook_strongarm_alter().
 */
function feature_opendata_dataset_strongarm_alter(&$data) {
  if (isset($data['pathauto_node_dataset_pattern'])) {
    $data['pathauto_node_dataset_pattern']->value = 'dataset/[node:nid]'; /* WAS: 'dataset/[node:title]' */
  }
  if (isset($data['pathauto_node_resource_pattern'])) {
    $data['pathauto_node_resource_pattern']->value = 'dataset/[node:field-dataset-ref:0:nid]/resource/[node:uuid]'; /* WAS: 'dataset/[node:field-dataset-ref:0:title]/resource/[node:uuid]' */
  }
}
