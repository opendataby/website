<?php
/**
 * @file
 * feature_opendata_groups.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_opendata_groups_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.node-dataset-og_group_ref.node-dataset-og_group_ref"]["DELETED"] = TRUE;

  // Exported overrides for: variable
  $overrides["variable.pathauto_node_group_pattern.pathauto_node_group_pattern"]["DELETED"] = TRUE;

  // Exported overrides for: views_view
  $overrides["views_view.dkan_group_members.dkan_group_members"]["DELETED"] = TRUE;
  $overrides["views_view.dkan_og_extras_group_members.dkan_og_extras_group_members"]["DELETED"] = TRUE;
  $overrides["views_view.group_block.group_block"]["DELETED"] = TRUE;
  $overrides["views_view.groups_page.groups_page"]["DELETED"] = TRUE;
  $overrides["views_view.groups_search.groups_search"]["DELETED"] = TRUE;
  $overrides["views_view.og_count.og_count"]["DELETED"] = TRUE;

 return $overrides;
}
