<?php
/**
 * @file
 * dkan_sitewide_demo_front.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function dkan_sitewide_demo_front_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "quicktabs" && $api == "quicktabs") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function dkan_sitewide_demo_front_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
