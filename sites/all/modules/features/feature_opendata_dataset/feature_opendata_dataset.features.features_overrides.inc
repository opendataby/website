<?php
/**
 * @file
 * feature_opendata_dataset.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_opendata_dataset_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: variable
  $overrides["variable.pathauto_node_dataset_pattern.value"] = 'dataset/[node:nid]';
  $overrides["variable.pathauto_node_resource_pattern.value"] = 'dataset/[node:field-dataset-ref:0:nid]/resource/[node:uuid]';

 return $overrides;
}
