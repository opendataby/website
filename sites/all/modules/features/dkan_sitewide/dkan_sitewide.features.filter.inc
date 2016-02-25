<?php
/**
 * @file
 * dkan_sitewide.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function dkan_sitewide_filter_default_formats() {
  $formats = array();

  // Exported format: HTML.
  $formats['html'] = array(
    'format' => 'html',
    'name' => 'HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_markdown' => array(
        'weight' => -11,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_url' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'filter_htmlcorrector' => array(
        'weight' => 10,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
