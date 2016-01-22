<?php
/**
 * @file
 * feature_opendata_search.features.inc
 */

/**
 * Implements hook_facetapi_default_facet_settings_alter().
 */
function feature_opendata_search_facetapi_default_facet_settings_alter(&$data) {
  if (isset($data['search_api@datasets:block:author'])) {
    unset($data['search_api@datasets:block:author']);
  }
  if (isset($data['search_api@datasets:block:field_license'])) {
    unset($data['search_api@datasets:block:field_license']);
  }
  if (isset($data['search_api@datasets:block:field_resources:field_format'])) {
    unset($data['search_api@datasets:block:field_resources:field_format']);
  }
  if (isset($data['search_api@datasets:block:field_tags'])) {
    unset($data['search_api@datasets:block:field_tags']);
  }
  if (isset($data['search_api@datasets:block:og_group_ref'])) {
    unset($data['search_api@datasets:block:og_group_ref']);
  }
}
