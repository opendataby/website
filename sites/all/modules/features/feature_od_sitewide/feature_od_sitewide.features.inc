<?php
/**
 * @file
 * feature_od_sitewide.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function feature_od_sitewide_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_filter_default_formats_alter().
 */
function feature_od_sitewide_filter_default_formats_alter(&$data) {
  if (isset($data['html'])) {
    unset($data['html']);
  }
}
