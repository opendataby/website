<?php
/**
 * @file
 * feature_od_dataset.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_od_dataset_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: variable
  $overrides["variable.pathauto_node_dataset_pattern.pathauto_node_dataset_pattern"]["DELETED"] = TRUE;
  $overrides["variable.pathauto_node_resource_pattern.pathauto_node_resource_pattern"]["DELETED"] = TRUE;

 return $overrides;
}
