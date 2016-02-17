<?php
/**
 * @file
 * feature_od_content_types.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_od_content_types_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_base
  $overrides["field_base.field_upload.field_upload"]["DELETED"] = TRUE;

  // Exported overrides for: field_instance
  $overrides["field_instance.node-resource-field_upload.node-resource-field_upload"]["DELETED"] = TRUE;

 return $overrides;
}
