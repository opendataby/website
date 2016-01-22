<?php
/**
 * @file
 * feature_opendata_context.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_opendata_context_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: context
  $overrides["context.dataset.dataset"]["DELETED"] = TRUE;
  $overrides["context.dataset_search.dataset_search"]["DELETED"] = TRUE;
  $overrides["context.sitewide.sitewide"]["DELETED"] = TRUE;

  // Exported overrides for: views_view
  $overrides["views_view.dataset.dataset"]["DELETED"] = TRUE;

 return $overrides;
}
