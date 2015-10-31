<?php
/**
 * @file
 * opendata_sitewide.features.inc
 */

/**
 * Implements hook_filter_default_formats_alter().
 */
function opendata_sitewide_filter_default_formats_alter(&$data) {
  if (isset($data['html'])) {
    unset($data['html']['filters']['filter_html']);
  }
}

/**
 * Implements hook_strongarm_alter().
 */
function opendata_sitewide_strongarm_alter(&$data) {
  if (isset($data['admin_theme'])) {
    $data['admin_theme']->value = 'seven'; /* WAS: 'nuboot_radix' */
  }
}
