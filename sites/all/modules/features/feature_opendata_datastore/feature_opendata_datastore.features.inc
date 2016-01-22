<?php
/**
 * @file
 * feature_opendata_datastore.features.inc
 */

/**
 * Implements hook_default_search_api_index_alter().
 */
function feature_opendata_datastore_default_search_api_index_alter(&$data) {
  if (isset($data['datasets'])) {
    unset($data['datasets']);
  }
}

/**
 * Implements hook_default_search_api_server_alter().
 */
function feature_opendata_datastore_default_search_api_server_alter(&$data) {
  if (isset($data['datasets'])) {
    unset($data['datasets']);
  }
}

/**
 * Implements hook_views_default_views_alter().
 */
function feature_opendata_datastore_views_default_views_alter(&$data) {
  if (isset($data['datasets'])) {
    unset($data['datasets']);
  }
}
