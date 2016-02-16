<?php
/**
 * @file
 * feature_od_sitewide.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_od_sitewide_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: filter
  $overrides["filter.html.html"]["DELETED"] = TRUE;

 return $overrides;
}
