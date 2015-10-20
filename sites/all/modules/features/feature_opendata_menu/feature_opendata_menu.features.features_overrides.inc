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
  $overrides["menu_links.main-menu_about:node/1.link_title"] = 'О нас';
  $overrides["menu_links.main-menu_about:node/1.weight"] = -43;
  $overrides["menu_links.main-menu_add-dataset:node/add/dataset.customized"] = 1;
  $overrides["menu_links.main-menu_add-dataset:node/add/dataset.hidden"] = 1;
  $overrides["menu_links.main-menu_add-dataset:node/add/dataset.link_title"] = 'Добавить набор данных';
  $overrides["menu_links.main-menu_add-dataset:node/add/dataset.weight"] = -48;

 return $overrides;
}
