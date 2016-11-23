<?php
/**
 * @file
 * dkan_sitewide.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function dkan_sitewide_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['menu-menu-footer-menu'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'menu-footer-menu',
    'module' => 'menu',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'data_radix' => array(
        'region' => 'footer',
        'status' => 1,
        'theme' => 'data_radix',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 0,
  );

  return $export;
}
