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
    $data['main-menu_about:node/1']['link_title'] = 'О нас'; /* WAS: 'About' */
    $data['main-menu_about:node/1']['weight'] = -43; /* WAS: -47 */
  }
  if (isset($data['main-menu_add-dataset:node/add/dataset'])) {
    $data['main-menu_add-dataset:node/add/dataset']['customized'] = 1; /* WAS: 0 */
    $data['main-menu_add-dataset:node/add/dataset']['hidden'] = 1; /* WAS: 0 */
    $data['main-menu_add-dataset:node/add/dataset']['link_title'] = 'Добавить набор данных'; /* WAS: 'Add Dataset' */
    $data['main-menu_add-dataset:node/add/dataset']['weight'] = -48; /* WAS: -50 */
  }
}
