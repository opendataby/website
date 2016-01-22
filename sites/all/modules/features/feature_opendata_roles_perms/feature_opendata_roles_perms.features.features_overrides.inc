<?php
/**
 * @file
 * feature_opendata_roles_perms.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_opendata_roles_perms_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: user_permission
  $overrides["user_permission.administer advanced pane settings.administer advanced pane settings"]["DELETED"] = TRUE;
  $overrides["user_permission.administer page manager.administer page manager"]["DELETED"] = TRUE;
  $overrides["user_permission.administer pane access.administer pane access"]["DELETED"] = TRUE;
  $overrides["user_permission.administer panels layouts.administer panels layouts"]["DELETED"] = TRUE;
  $overrides["user_permission.administer panels styles.administer panels styles"]["DELETED"] = TRUE;
  $overrides["user_permission.administer path breadcrumbs.administer path breadcrumbs"]["DELETED"] = TRUE;
  $overrides["user_permission.administer permissions.administer permissions"]["DELETED"] = TRUE;
  $overrides["user_permission.administer users.administer users"]["DELETED"] = TRUE;
  $overrides["user_permission.administer views.administer views"]["DELETED"] = TRUE;
  $overrides["user_permission.change layouts in place editing.change layouts in place editing"]["DELETED"] = TRUE;
  $overrides["user_permission.perform unlimited index queries.perform unlimited index queries"]["DELETED"] = TRUE;
  $overrides["user_permission.use ipe with page manager.use ipe with page manager"]["DELETED"] = TRUE;
  $overrides["user_permission.use page manager.use page manager"]["DELETED"] = TRUE;
  $overrides["user_permission.use panels caching features.use panels caching features"]["DELETED"] = TRUE;
  $overrides["user_permission.use panels dashboard.use panels dashboard"]["DELETED"] = TRUE;
  $overrides["user_permission.use panels in place editing.use panels in place editing"]["DELETED"] = TRUE;
  $overrides["user_permission.use panels locks.use panels locks"]["DELETED"] = TRUE;
  $overrides["user_permission.use text format html.use text format html"]["DELETED"] = TRUE;
  $overrides["user_permission.view pane admin links.view pane admin links"]["DELETED"] = TRUE;

 return $overrides;
}
