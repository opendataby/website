<?php
/**
 * @file
 * opendata_sitewide.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function opendata_sitewide_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: filter
  $overrides["filter.html.filters|filter_html"]["DELETED"] = TRUE;

  // Exported overrides for: variable
  $overrides["variable.admin_theme.value"] = 'seven';

 return $overrides;
}
