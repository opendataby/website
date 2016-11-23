<?php
/**
 * @file
 * dkan_sitewide_demo_front.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function dkan_sitewide_demo_front_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['block-google_group_front'] = array(
    'cache' => -1,
    'custom' => 0,
    'machine_name' => 'google_group_front',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'data_radix' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'data_radix',
        'weight' => 0,
      ),
      'nuboot_radix' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'nuboot_radix',
        'weight' => 0,
      ),
    ),
    'title' => 'Google group',
    'visibility' => 0,
  );

  return $export;
}
