<?php
/**
 * @file
 * opendata_sitewide.quicktabs.inc
 */

/**
 * Implements hook_quicktabs_default_quicktabs().
 */
function opendata_sitewide_quicktabs_default_quicktabs() {
  $export = array();

  $quicktabs = new stdClass();
  $quicktabs->disabled = FALSE; /* Edit this to true to make a default quicktabs disabled initially */
  $quicktabs->api_version = 1;
  $quicktabs->machine_name = 'broadcast';
  $quicktabs->ajax = 0;
  $quicktabs->hide_empty_tabs = FALSE;
  $quicktabs->default_tab = 999999;
  $quicktabs->title = 'Прямой эфир';
  $quicktabs->tabs = array(
    0 => array(
      'bid' => 'views_delta_blog-block_1',
      'hide_title' => 1,
      'title' => 'Блог OpenData',
      'weight' => '-100',
      'type' => 'block',
    ),
    1 => array(
      'bid' => 'block_delta_3',
      'hide_title' => 1,
      'title' => 'Группы Google',
      'weight' => '-99',
      'type' => 'block',
    ),
    2 => array(
      'vid' => 'tweets',
      'display' => 'page_2',
      'args' => '',
      'title' => 'Твиттер',
      'weight' => '-98',
      'type' => 'view',
    ),
  );
  $quicktabs->renderer = 'ui_tabs';
  $quicktabs->style = 'nostyle';
  $quicktabs->options = array(
    'history' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Блог OpenData');
  t('Группы Google');
  t('Прямой эфир');
  t('Твиттер');

  $export['broadcast'] = $quicktabs;

  return $export;
}
