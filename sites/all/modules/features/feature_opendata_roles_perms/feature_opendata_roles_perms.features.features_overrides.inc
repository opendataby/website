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
  $overrides["user_permission.administer advanced pane settings.roles|administrator"]["DELETED"] = TRUE;
  $overrides["user_permission.administer advanced pane settings.roles|editor"] = 'editor';
  $overrides["user_permission.administer page manager.roles|editor"] = 'editor';
  $overrides["user_permission.administer pane access.roles|administrator"]["DELETED"] = TRUE;
  $overrides["user_permission.administer pane access.roles|editor"] = 'editor';
  $overrides["user_permission.administer panels layouts.roles|editor"] = 'editor';
  $overrides["user_permission.administer panels styles.roles|editor"] = 'editor';
  $overrides["user_permission.administer path breadcrumbs.roles|editor"] = 'editor';
  $overrides["user_permission.administer permissions.roles|administrator"]["DELETED"] = TRUE;
  $overrides["user_permission.administer users.roles|administrator"]["DELETED"] = TRUE;
  $overrides["user_permission.administer views.roles|administrator"]["DELETED"] = TRUE;
  $overrides["user_permission.change layouts in place editing.roles|administrator"]["DELETED"] = TRUE;
  $overrides["user_permission.change layouts in place editing.roles|editor"] = 'editor';
  $overrides["user_permission.perform unlimited index queries.roles|anonymous user"] = 'anonymous user';
  $overrides["user_permission.perform unlimited index queries.roles|authenticated user"] = 'authenticated user';
  $overrides["user_permission.use ipe with page manager.roles|administrator"]["DELETED"] = TRUE;
  $overrides["user_permission.use ipe with page manager.roles|editor"] = 'editor';
  $overrides["user_permission.use page manager.roles|editor"] = 'editor';
  $overrides["user_permission.use panels caching features.roles|editor"] = 'editor';
  $overrides["user_permission.use panels dashboard.roles|administrator"]["DELETED"] = TRUE;
  $overrides["user_permission.use panels dashboard.roles|editor"] = 'editor';
  $overrides["user_permission.use panels in place editing.roles|administrator"]["DELETED"] = TRUE;
  $overrides["user_permission.use panels in place editing.roles|editor"] = 'editor';
  $overrides["user_permission.use panels locks.roles|editor"] = 'editor';
  $overrides["user_permission.use text format html.roles|authenticated user"] = 'authenticated user';
  $overrides["user_permission.view pane admin links.roles|administrator"]["DELETED"] = TRUE;
  $overrides["user_permission.view pane admin links.roles|editor"] = 'editor';

 return $overrides;
}
