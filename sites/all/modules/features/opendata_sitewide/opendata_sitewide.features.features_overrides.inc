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
  $overrides["filter.html.html"]["DELETED"] = TRUE;

  // Exported overrides for: variable
  $overrides["variable.admin_theme.admin_theme"]["DELETED"] = TRUE;
  $overrides["variable.bueditor_roles.bueditor_roles"]["DELETED"] = TRUE;
  $overrides["variable.colorizer_cssfile.colorizer_cssfile"]["DELETED"] = TRUE;

 return $overrides;
}
