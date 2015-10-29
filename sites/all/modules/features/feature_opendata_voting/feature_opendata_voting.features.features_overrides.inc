<?php
/**
 * @file
 * feature_opendata_voting.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_opendata_voting_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.node-dataset-field_rating.display|teaser|weight"] = 11;
  $overrides["field_instance.node-dataset-field_rating.widget|weight"] = 8;

 return $overrides;
}
