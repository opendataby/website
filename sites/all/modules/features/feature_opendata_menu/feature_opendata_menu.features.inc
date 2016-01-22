<?php
/**
 * @file
 * feature_opendata_menu.features.inc
 */

/**
 * Implements hook_menu_default_menu_links_alter().
 */
function feature_opendata_menu_menu_default_menu_links_alter(&$data) {
  if (isset($data['main-menu_about:node/1'])) {
    unset($data['main-menu_about:node/1']);
  }
  if (isset($data['main-menu_add-dataset:node/add/dataset'])) {
    unset($data['main-menu_add-dataset:node/add/dataset']);
  }
}
