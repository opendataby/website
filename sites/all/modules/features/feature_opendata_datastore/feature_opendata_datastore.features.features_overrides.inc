<?php
/**
 * @file
 * feature_opendata_datastore.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_opendata_datastore_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: search_api_index
  $overrides["search_api_index.datasets.datasets"]["DELETED"] = TRUE;

  // Exported overrides for: search_api_server
  $overrides["search_api_server.datasets.datasets"]["DELETED"] = TRUE;

  // Exported overrides for: views_view
  $overrides["views_view.datasets.datasets"]["DELETED"] = TRUE;

 return $overrides;
}
