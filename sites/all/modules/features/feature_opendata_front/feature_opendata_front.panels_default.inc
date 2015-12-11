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
    $pane->pid = 'new-95b50f74-9538-4aaa-ba11-ac20ead11021';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'dkan_groups_featured-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'items_per_page' => '9',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '95b50f74-9538-4aaa-ba11-ac20ead11021';
    $display->content['new-95b50f74-9538-4aaa-ba11-ac20ead11021'] = $pane;
    $display->panels['middle'][0] = 'new-95b50f74-9538-4aaa-ba11-ac20ead11021';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $mini->display = $display;
  $export['featured_groups'] = $mini;

  return $export;
}
