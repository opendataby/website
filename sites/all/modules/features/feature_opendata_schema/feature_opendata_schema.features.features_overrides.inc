<?php
/**
 * @file
 * feature_opendata_schema.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_opendata_schema_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: open_data_schema_apis
  $overrides["open_data_schema_apis.ckan_current_package_list_with_resources.ckan_current_package_list_with_resources"]["DELETED"] = TRUE;
  $overrides["open_data_schema_apis.ckan_group_list.ckan_group_list"]["DELETED"] = TRUE;
  $overrides["open_data_schema_apis.ckan_group_package_show.ckan_group_package_show"]["DELETED"] = TRUE;
  $overrides["open_data_schema_apis.ckan_package_list.ckan_package_list"]["DELETED"] = TRUE;
  $overrides["open_data_schema_apis.ckan_package_show.ckan_package_show"]["DELETED"] = TRUE;
  $overrides["open_data_schema_apis.ckan_resource_show.ckan_resource_show"]["DELETED"] = TRUE;
  $overrides["open_data_schema_apis.data_json.data_json"]["DELETED"] = TRUE;
  $overrides["open_data_schema_apis.data_json_1_1.data_json_1_1"]["DELETED"] = TRUE;

 return $overrides;
}
