<?php
/**
 * @file
 * feature_opendata_search.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_opendata_search_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: facetapi
  $overrides["facetapi.search_api@datasets:block:author.search_api@datasets:block:author"]["DELETED"] = TRUE;
  $overrides["facetapi.search_api@datasets:block:field_license.search_api@datasets:block:field_license"]["DELETED"] = TRUE;
  $overrides["facetapi.search_api@datasets:block:field_resources:field_format.search_api@datasets:block:field_resources:field_format"]["DELETED"] = TRUE;
  $overrides["facetapi.search_api@datasets:block:field_tags.search_api@datasets:block:field_tags"]["DELETED"] = TRUE;
  $overrides["facetapi.search_api@datasets:block:og_group_ref.search_api@datasets:block:og_group_ref"]["DELETED"] = TRUE;

  // Exported overrides for: node
  $overrides["node.dataset.dataset"]["DELETED"] = TRUE;

 return $overrides;
}
