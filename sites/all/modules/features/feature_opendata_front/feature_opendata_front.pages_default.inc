<?php
/**
 * @file
 * feature_opendata_front.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function feature_opendata_front_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'frontpage';
  $page->task = 'page';
  $page->admin_title = 'Frontpage';
  $page->admin_description = '';
  $page->path = 'front';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_frontpage__panel';
  $handler->task = 'page';
  $handler->subtask = 'frontpage';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
    'access' => array(
      'logic' => 'and',
    ),
  );
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
  $display->title = 'Открытые данные Беларуси';
  $display->uuid = '3a8aeb40-b428-4b58-90f2-f24b7e028563';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-2df55a55-76f8-4f3d-b793-4326d678ebff';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'block-5';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '<none>',
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
    $pane->uuid = '2df55a55-76f8-4f3d-b793-4326d678ebff';
    $display->content['new-2df55a55-76f8-4f3d-b793-4326d678ebff'] = $pane;
    $display->panels['middle'][0] = 'new-2df55a55-76f8-4f3d-b793-4326d678ebff';
    $pane = new stdClass();
    $pane->pid = 'new-d3ff3986-83d1-4ae3-91bb-6bd80237b0ea';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'block-6';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '<none>',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'd3ff3986-83d1-4ae3-91bb-6bd80237b0ea';
    $display->content['new-d3ff3986-83d1-4ae3-91bb-6bd80237b0ea'] = $pane;
    $display->panels['middle'][1] = 'new-d3ff3986-83d1-4ae3-91bb-6bd80237b0ea';
    $pane = new stdClass();
    $pane->pid = 'new-197c7457-d073-4ba6-b92d-dc5d8db69ffd';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = '_front_projects_in_slideshow-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '197c7457-d073-4ba6-b92d-dc5d8db69ffd';
    $display->content['new-197c7457-d073-4ba6-b92d-dc5d8db69ffd'] = $pane;
    $display->panels['middle'][2] = 'new-197c7457-d073-4ba6-b92d-dc5d8db69ffd';
    $pane = new stdClass();
    $pane->pid = 'new-c9c5a468-65d3-449e-ae7d-039cab656fc4';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'quicktabs-broadcast';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
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
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'c9c5a468-65d3-449e-ae7d-039cab656fc4';
    $display->content['new-c9c5a468-65d3-449e-ae7d-039cab656fc4'] = $pane;
    $display->panels['middle'][3] = 'new-c9c5a468-65d3-449e-ae7d-039cab656fc4';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-2df55a55-76f8-4f3d-b793-4326d678ebff';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['frontpage'] = $page;

  return $pages;

}
