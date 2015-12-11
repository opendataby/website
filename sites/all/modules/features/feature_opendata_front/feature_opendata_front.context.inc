<?php
/**
 * @file
 * feature_opendata_front.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function feature_opendata_front_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'front';
  $context->description = '';
  $context->tag = 'Page';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'panels_mini-featured_groups' => array(
          'module' => 'panels_mini',
          'delta' => 'featured_groups',
          'region' => 'preface_third',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Page');
  $export['front'] = $context;

  return $export;
}
