<?php
/**
 * @file
 * opendata_dataset_content_types.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function opendata_dataset_content_types_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_base
  $overrides["field_base.field_author.field_author"]["DELETED"] = TRUE;
  $overrides["field_base.field_frequency.field_frequency"]["DELETED"] = TRUE;
  $overrides["field_base.field_public_access_level.field_public_access_level"]["DELETED"] = TRUE;
  $overrides["field_base.field_tags.field_tags"]["DELETED"] = TRUE;

  // Exported overrides for: field_group
  $overrides["field_group.group_additional|node|dataset|form.group_additional|node|dataset|form"]["DELETED"] = TRUE;
  $overrides["field_group.group_link_api|node|resource|form.group_link_api|node|resource|form"]["DELETED"] = TRUE;
  $overrides["field_group.group_link_file|node|resource|form.group_link_file|node|resource|form"]["DELETED"] = TRUE;
  $overrides["field_group.group_primary|node|dataset|form.group_primary|node|dataset|form"]["DELETED"] = TRUE;

  // Exported overrides for: field_instance
  $overrides["field_instance.node-dataset-body.node-dataset-body"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_additional_info.node-dataset-field_additional_info"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_author.node-dataset-field_author"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_contact_email.node-dataset-field_contact_email"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_contact_name.node-dataset-field_contact_name"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_data_dictionary.node-dataset-field_data_dictionary"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_frequency.node-dataset-field_frequency"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_granularity.node-dataset-field_granularity"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_license.node-dataset-field_license"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_public_access_level.node-dataset-field_public_access_level"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_related_content.node-dataset-field_related_content"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_resources.node-dataset-field_resources"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_spatial.node-dataset-field_spatial"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_spatial_geographical_cover.node-dataset-field_spatial_geographical_cover"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_tags.node-dataset-field_tags"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_temporal_coverage.node-dataset-field_temporal_coverage"]["DELETED"] = TRUE;
  $overrides["field_instance.node-resource-body.node-resource-body"]["DELETED"] = TRUE;
  $overrides["field_instance.node-resource-field_dataset_ref.node-resource-field_dataset_ref"]["DELETED"] = TRUE;
  $overrides["field_instance.node-resource-field_format.node-resource-field_format"]["DELETED"] = TRUE;
  $overrides["field_instance.node-resource-field_link_remote_file.node-resource-field_link_remote_file"]["DELETED"] = TRUE;
  $overrides["field_instance.node-resource-field_upload.node-resource-field_upload"]["DELETED"] = TRUE;

  // Exported overrides for: taxonomy
  $overrides["taxonomy.format.format"]["DELETED"] = TRUE;
  $overrides["taxonomy.tags.tags"]["DELETED"] = TRUE;

  // Exported overrides for: variable
  $overrides["variable.field_bundle_settings_node__dataset.field_bundle_settings_node__dataset"]["DELETED"] = TRUE;

 return $overrides;
}
