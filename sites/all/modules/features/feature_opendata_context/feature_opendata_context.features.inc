<?php
/**
 * @file
 * feature_opendata_context.features.inc
 */

/**
 * Implements hook_context_default_contexts_alter().
 */
function feature_opendata_context_context_default_contexts_alter(&$data) {
  if (isset($data['dataset'])) {
    unset($data['dataset']);
  }
  if (isset($data['dataset_search'])) {
    unset($data['dataset_search']);
  }
  if (isset($data['sitewide'])) {
    unset($data['sitewide']);
  }
}

/**
 * Implements hook_views_default_views_alter().
 */
function feature_opendata_context_views_default_views_alter(&$data) {
  if (isset($data['dataset'])) {
    unset($data['dataset']);
  }
}
