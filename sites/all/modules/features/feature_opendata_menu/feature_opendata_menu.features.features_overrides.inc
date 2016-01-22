<?php
/**
 * @file
 * feature_opendata_menu.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_opendata_menu_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: menu_links
  $overrides["menu_links.main-menu_about:node/1.main-menu_about:node/1"]["DELETED"] = TRUE;
  $overrides["menu_links.main-menu_add-dataset:node/add/dataset.main-menu_add-dataset:node/add/dataset"]["DELETED"] = TRUE;

 return $overrides;
}
