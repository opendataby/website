<?php
/**
 * @file
 * feature_opendata_context.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_opendata_context_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: context
  $overrides["context.dataset_search.disabled"] = FALSE;
  $overrides["context.dataset_search.reactions|block|blocks|facetapi-AbuAoaiaio6DzODdgSKx7mdmYXObBzp7"]["DELETED"] = TRUE;
  $overrides["context.dataset_search.reactions|block|blocks|facetapi-VBBDnNWYupC3PxCnXOq4e4ds4sAU4W7s|weight"] = -31;
  $overrides["context.dataset_search.reactions|block|blocks|facetapi-dqCRnp6cKP1cSzAsNB6zqFtY9AVEa0mp"]["DELETED"] = TRUE;
  $overrides["context.dataset_search.reactions|block|blocks|facetapi-wsVI1ENUXwf4Rz08n9fg2WvfQ0Gs5h2a"]["DELETED"] = TRUE;
  $overrides["context.dataset_search.reactions|block|blocks|facetapi-y0bmt1wN50B9oCuMeoazc1hpKiMkSQ2A"]["DELETED"] = TRUE;
  $overrides["context.dataset_search.reactions|block|blocks|facetapi-yW6mJ3GaJF0LypnLPa433Bf9GI8QdWd9"]["DELETED"] = TRUE;
  $overrides["context.sitewide.reactions|block|blocks|dkan_sitewide-dkan_sitewide_footer_author"]["DELETED"] = TRUE;
  $overrides["context.sitewide.reactions|block|blocks|dkan_sitewide-dkan_sitewide_search_bar"]["DELETED"] = TRUE;
  $overrides["context.sitewide.reactions|block|blocks|dkan_sitewide-dkan_sitewide_user_menu"]["DELETED"] = TRUE;
  $overrides["context.sitewide.reactions|block|blocks|menu-menu-footer-menu"] = array(
    'module' => 'menu',
    'delta' => 'menu-footer-menu',
    'region' => 'footer',
    'weight' => -10,
  );
  $overrides["context.sitewide.reactions|block|blocks|system-main-menu"]["DELETED"] = TRUE;

 return $overrides;
}
