<?php
/**
 * @file
 * feature_opendata_front.panels_default.inc
 */

/**
 * Implements hook_default_panels_mini().
 */
function feature_opendata_front_default_panels_mini() {
  $export = array();

  $mini = new stdClass();
  $mini->disabled = FALSE; /* Edit this to true to make a default mini disabled initially */
  $mini->api_version = 1;
  $mini->name = 'featured_groups';
  $mini->category = 'OpenData';
  $mini->admin_title = 'Featured groups';
  $mini->admin_description = 'Featured groups on the home page';
  $mini->requiredcontexts = array();
  $mini->contexts = array();
  $mini->relationships = array();
  $display = new panels_display();
  $display->layout = 'onecol';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'a7a0545a-1b6c-4b7b-b973-b3c91f7712c4';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-65b9922e-845b-46d3-8dd4-e23d8ebd26c5';
    $pane->panel = 'middle';
    $pane->type = 'views';
    $pane->subtype = 'opendata_groups_grid';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '12',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '65b9922e-845b-46d3-8dd4-e23d8ebd26c5';
    $display->content['new-65b9922e-845b-46d3-8dd4-e23d8ebd26c5'] = $pane;
    $display->panels['middle'][0] = 'new-65b9922e-845b-46d3-8dd4-e23d8ebd26c5';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $mini->display = $display;
  $export['featured_groups'] = $mini;

  return $export;
}
