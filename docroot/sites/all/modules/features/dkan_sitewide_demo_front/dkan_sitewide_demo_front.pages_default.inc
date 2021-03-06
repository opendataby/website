<?php
/**
 * @file
 * dkan_sitewide_demo_front.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function dkan_sitewide_demo_front_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'front';
  $page->task = 'page';
  $page->admin_title = 'Front page';
  $page->admin_description = '';
  $page->path = 'front';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_front__panel_context_e436cffa-9ab6-4bf4-8775-a5842b506d96';
  $handler->task = 'page';
  $handler->subtask = 'front';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'ipe',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(),
      'logic' => 'and',
    ),
    'name' => '',
  );
  $display = new panels_display();
  $display->layout = 'full_width';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'header' => NULL,
      'column1' => NULL,
      'column2' => NULL,
      'middle' => NULL,
      'secondcolumn1' => NULL,
      'secondcolumn2' => NULL,
      'footer' => NULL,
      'top-first' => NULL,
      'top-second' => NULL,
      'bottom-first' => NULL,
      'bottom-second' => NULL,
      'bottom-third' => NULL,
      'bottom-fourth' => NULL,
      'middle-bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '53a00d34-5bc4-4b11-aad6-a5615c73e388';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-8aa431e2-a9e8-4d73-b043-aa57ecbf0947';
    $pane->panel = 'middle';
    $pane->type = 'block';
    $pane->subtype = 'views-front_page_group_grid-block';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '8aa431e2-a9e8-4d73-b043-aa57ecbf0947';
    $display->content['new-8aa431e2-a9e8-4d73-b043-aa57ecbf0947'] = $pane;
    $display->panels['middle'][0] = 'new-8aa431e2-a9e8-4d73-b043-aa57ecbf0947';
    $pane = new stdClass();
    $pane->pid = 'new-1233cfbe-d4d6-41a0-926e-29feec02bb39';
    $pane->panel = 'middle';
    $pane->type = 'views_panes';
    $pane->subtype = 'Projects-front_slideshow';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '1233cfbe-d4d6-41a0-926e-29feec02bb39';
    $display->content['new-1233cfbe-d4d6-41a0-926e-29feec02bb39'] = $pane;
    $display->panels['middle'][1] = 'new-1233cfbe-d4d6-41a0-926e-29feec02bb39';
    $pane = new stdClass();
    $pane->pid = 'new-e3c2825c-8b09-4947-8dc9-977fd779ac4c';
    $pane->panel = 'middle-bottom';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Case studies',
      'title' => '',
      'body' => '<h2>Как используются открытые данные</h2>
<ul class="front-case-studies">
	<li><a href="/blog/777">В бизнесе</a></li>
	<li><a href="/blog/776">Для города</a></li>
	<li><a href="/blog/775">В журналистике</a></li>
</ul>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'front-pane-case-studies',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'e3c2825c-8b09-4947-8dc9-977fd779ac4c';
    $display->content['new-e3c2825c-8b09-4947-8dc9-977fd779ac4c'] = $pane;
    $display->panels['middle-bottom'][0] = 'new-e3c2825c-8b09-4947-8dc9-977fd779ac4c';
    $pane = new stdClass();
    $pane->pid = 'new-bdb76ecd-c9d6-4aea-90ad-f1eb03028fe3';
    $pane->panel = 'middle-bottom';
    $pane->type = 'views';
    $pane->subtype = 'blog';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '3',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block_recent_blogs',
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
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'bdb76ecd-c9d6-4aea-90ad-f1eb03028fe3';
    $display->content['new-bdb76ecd-c9d6-4aea-90ad-f1eb03028fe3'] = $pane;
    $display->panels['middle-bottom'][1] = 'new-bdb76ecd-c9d6-4aea-90ad-f1eb03028fe3';
    $pane = new stdClass();
    $pane->pid = 'new-e9a59ddf-15b0-4a29-8ef6-ef460ba539e0';
    $pane->panel = 'top-first';
    $pane->type = 'block';
    $pane->subtype = 'dkan_sitewide_demo_front-dkan_add_front';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'front-block-site-description',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'e9a59ddf-15b0-4a29-8ef6-ef460ba539e0';
    $display->content['new-e9a59ddf-15b0-4a29-8ef6-ef460ba539e0'] = $pane;
    $display->panels['top-first'][0] = 'new-e9a59ddf-15b0-4a29-8ef6-ef460ba539e0';
    $pane = new stdClass();
    $pane->pid = 'new-949696cf-520f-40a4-af80-725bca8b2f13';
    $pane->panel = 'top-first';
    $pane->type = 'block';
    $pane->subtype = 'views-popular_tags-block';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '949696cf-520f-40a4-af80-725bca8b2f13';
    $display->content['new-949696cf-520f-40a4-af80-725bca8b2f13'] = $pane;
    $display->panels['top-first'][1] = 'new-949696cf-520f-40a4-af80-725bca8b2f13';
    $pane = new stdClass();
    $pane->pid = 'new-11969a4b-795a-40df-8d66-91f6daec6c20';
    $pane->panel = 'top-first';
    $pane->type = 'block';
    $pane->subtype = 'dkan_sitewide-dkan_sitewide_search_bar';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '11969a4b-795a-40df-8d66-91f6daec6c20';
    $display->content['new-11969a4b-795a-40df-8d66-91f6daec6c20'] = $pane;
    $display->panels['top-first'][2] = 'new-11969a4b-795a-40df-8d66-91f6daec6c20';
    $pane = new stdClass();
    $pane->pid = 'new-ab17edbb-ca9c-441a-b9c9-0eac961027cf';
    $pane->panel = 'top-second';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = FALSE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => '',
      'title' => '',
      'body' => 'Пиши на info@opendata.by',
      'format' => 'html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'ab17edbb-ca9c-441a-b9c9-0eac961027cf';
    $display->content['new-ab17edbb-ca9c-441a-b9c9-0eac961027cf'] = $pane;
    $display->panels['top-second'][0] = 'new-ab17edbb-ca9c-441a-b9c9-0eac961027cf';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-e9a59ddf-15b0-4a29-8ef6-ef460ba539e0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['front'] = $page;

  return $pages;

}
