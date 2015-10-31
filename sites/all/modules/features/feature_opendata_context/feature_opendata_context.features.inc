<?php
/**
 * @file
 * feature_opendata_context.features.inc
 */

/**
 * Implements hook_context_default_contexts_alter().
 */
function feature_opendata_context_context_default_contexts_alter(&$data) {
  if (isset($data['dataset_search'])) {
    $data['dataset_search']->disabled = FALSE; /* WAS: TRUE */
    $data['dataset_search']->reactions['block']['blocks']['facetapi-VBBDnNWYupC3PxCnXOq4e4ds4sAU4W7s']['weight'] = -31; /* WAS: -21 */
    unset($data['dataset_search']->reactions['block']['blocks']['facetapi-AbuAoaiaio6DzODdgSKx7mdmYXObBzp7']);
    unset($data['dataset_search']->reactions['block']['blocks']['facetapi-dqCRnp6cKP1cSzAsNB6zqFtY9AVEa0mp']);
    unset($data['dataset_search']->reactions['block']['blocks']['facetapi-wsVI1ENUXwf4Rz08n9fg2WvfQ0Gs5h2a']);
    unset($data['dataset_search']->reactions['block']['blocks']['facetapi-y0bmt1wN50B9oCuMeoazc1hpKiMkSQ2A']);
    unset($data['dataset_search']->reactions['block']['blocks']['facetapi-yW6mJ3GaJF0LypnLPa433Bf9GI8QdWd9']);
  }
  if (isset($data['sitewide'])) {
    $data['sitewide']->reactions['block']['blocks']['menu-menu-footer-menu'] = array(
      'module' => 'menu',
      'delta' => 'menu-footer-menu',
      'region' => 'footer',
      'weight' => -10,
    ); /* WAS: '' */
    unset($data['sitewide']->reactions['block']['blocks']['dkan_sitewide-dkan_sitewide_footer_author']);
    unset($data['sitewide']->reactions['block']['blocks']['dkan_sitewide-dkan_sitewide_search_bar']);
    unset($data['sitewide']->reactions['block']['blocks']['dkan_sitewide-dkan_sitewide_user_menu']);
    unset($data['sitewide']->reactions['block']['blocks']['system-main-menu']);
  }
}
