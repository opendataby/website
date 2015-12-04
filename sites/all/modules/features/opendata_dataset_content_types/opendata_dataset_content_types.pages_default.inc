<?php
/**
 * @file
 * opendata_dataset_content_types.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function opendata_dataset_content_types_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view__panel_context_27e3817e-b0b9-475d-b3a1-9838e5ddf0c0';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -99;
  $handler->conf = array(
    'title' => 'single dataset',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'dataset' => 'dataset',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
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
  $display->title = '';
  $display->uuid = '8c123371-c8ca-4ec6-8e1a-d269caaab2cd';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-a6bd9976-d7ed-42f0-bd3e-a2f6b4226d41';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:body';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'hidden',
      'formatter' => 'text_default',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
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
    $pane->uuid = 'a6bd9976-d7ed-42f0-bd3e-a2f6b4226d41';
    $display->content['new-a6bd9976-d7ed-42f0-bd3e-a2f6b4226d41'] = $pane;
    $display->panels['middle'][0] = 'new-a6bd9976-d7ed-42f0-bd3e-a2f6b4226d41';
    $pane = new stdClass();
    $pane->pid = 'new-e19ab8e6-0fe6-42be-a8cb-9bc65db20034';
    $pane->panel = 'middle';
    $pane->type = 'entity_field_extra';
    $pane->subtype = 'node:resources';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'full',
      'context' => 'argument_entity_id:node_1',
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
    $pane->uuid = 'e19ab8e6-0fe6-42be-a8cb-9bc65db20034';
    $display->content['new-e19ab8e6-0fe6-42be-a8cb-9bc65db20034'] = $pane;
    $display->panels['middle'][1] = 'new-e19ab8e6-0fe6-42be-a8cb-9bc65db20034';
    $pane = new stdClass();
    $pane->pid = 'new-9f4dd856-2278-4e92-b138-c2273db97ec1';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_tags';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'i18n_taxonomy_term_reference_link',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-md-4',
    );
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '9f4dd856-2278-4e92-b138-c2273db97ec1';
    $display->content['new-9f4dd856-2278-4e92-b138-c2273db97ec1'] = $pane;
    $display->panels['middle'][2] = 'new-9f4dd856-2278-4e92-b138-c2273db97ec1';
    $pane = new stdClass();
    $pane->pid = 'new-d5d4231a-6061-48da-b20c-f54d4d5acc95';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_geo';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'i18n_taxonomy_term_reference_link',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-md-4',
    );
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'd5d4231a-6061-48da-b20c-f54d4d5acc95';
    $display->content['new-d5d4231a-6061-48da-b20c-f54d4d5acc95'] = $pane;
    $display->panels['middle'][3] = 'new-d5d4231a-6061-48da-b20c-f54d4d5acc95';
    $pane = new stdClass();
    $pane->pid = 'new-e2aea30a-9915-4a4b-ab67-c75d742a885e';
    $pane->panel = 'middle';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_spec_projects';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'i18n_taxonomy_term_reference_link',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
      'override_title_heading' => 'h2',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => '',
      'css_class' => 'col-md-4',
    );
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = 'e2aea30a-9915-4a4b-ab67-c75d742a885e';
    $display->content['new-e2aea30a-9915-4a4b-ab67-c75d742a885e'] = $pane;
    $display->panels['middle'][4] = 'new-e2aea30a-9915-4a4b-ab67-c75d742a885e';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-a6bd9976-d7ed-42f0-bd3e-a2f6b4226d41';
  $handler->conf['display'] = $display;
  $export['node_view__panel_context_27e3817e-b0b9-475d-b3a1-9838e5ddf0c0'] = $handler;

  return $export;
}
