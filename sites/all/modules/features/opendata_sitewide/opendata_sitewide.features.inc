<?php
/**
 * @file
 * opendata_sitewide.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function opendata_sitewide_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "quicktabs" && $api == "quicktabs") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_filter_default_formats_alter().
 */
function opendata_sitewide_filter_default_formats_alter(&$data) {
  if (isset($data['html'])) {
    unset($data['html']);
  }
}

/**
 * Implements hook_strongarm_alter().
 */
function opendata_sitewide_strongarm_alter(&$data) {
  if (isset($data['admin_theme'])) {
    unset($data['admin_theme']);
  }
  if (isset($data['bueditor_roles'])) {
    unset($data['bueditor_roles']);
  }
  if (isset($data['colorizer_cssfile'])) {
    unset($data['colorizer_cssfile']);
  }
}
