<?php
/**
 * @file
 * dkan_sitewide_demo_front.quicktabs.inc
 */

/**
 * Implements hook_quicktabs_default_quicktabs().
 */
function dkan_sitewide_demo_front_quicktabs_default_quicktabs() {
  $export = array();

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'live_stream';
  $quicktabs->ajax = 1;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 999999;
  $quicktabs->title = 'Live stream';
  $quicktabs->tabs = array(
    0 => array(
      'vid' => 'blog',
      'display' => 'block_1',
      'args' => '',
      'title' => 'Блог',
      'weight' => '-100',
      'type' => 'view',
    ),
    1 => array(
      'machine_name' => '',
      'title' => 'Google группа',
      'weight' => '-99',
      'type' => 'qtabs',
    ),
  );
  $quicktabs->renderer = 'ui_tabs';
  $quicktabs->style = 'nostyle';
  $quicktabs->options = array(
    'history' => 0,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Google группа');
  t('Live stream');
  t('Блог');

  $export['live_stream'] = $quicktabs;

  return $export;
}
