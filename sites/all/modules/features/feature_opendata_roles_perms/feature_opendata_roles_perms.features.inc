<?php
/**
 * @file
 * feature_opendata_roles_perms.features.inc
 */

/**
 * Implements hook_user_default_permissions_alter().
 */
function feature_opendata_roles_perms_user_default_permissions_alter(&$data) {
  if (isset($data['administer advanced pane settings'])) {
    unset($data['administer advanced pane settings']);
  }
  if (isset($data['administer page manager'])) {
    unset($data['administer page manager']);
  }
  if (isset($data['administer pane access'])) {
    unset($data['administer pane access']);
  }
  if (isset($data['administer panels layouts'])) {
    unset($data['administer panels layouts']);
  }
  if (isset($data['administer panels styles'])) {
    unset($data['administer panels styles']);
  }
  if (isset($data['administer path breadcrumbs'])) {
    unset($data['administer path breadcrumbs']);
  }
  if (isset($data['administer permissions'])) {
    unset($data['administer permissions']);
  }
  if (isset($data['administer users'])) {
    unset($data['administer users']);
  }
  if (isset($data['administer views'])) {
    unset($data['administer views']);
  }
  if (isset($data['change layouts in place editing'])) {
    unset($data['change layouts in place editing']);
  }
  if (isset($data['perform unlimited index queries'])) {
    unset($data['perform unlimited index queries']);
  }
  if (isset($data['use ipe with page manager'])) {
    unset($data['use ipe with page manager']);
  }
  if (isset($data['use page manager'])) {
    unset($data['use page manager']);
  }
  if (isset($data['use panels caching features'])) {
    unset($data['use panels caching features']);
  }
  if (isset($data['use panels dashboard'])) {
    unset($data['use panels dashboard']);
  }
  if (isset($data['use panels in place editing'])) {
    unset($data['use panels in place editing']);
  }
  if (isset($data['use panels locks'])) {
    unset($data['use panels locks']);
  }
  if (isset($data['use text format html'])) {
    unset($data['use text format html']);
  }
  if (isset($data['view pane admin links'])) {
    unset($data['view pane admin links']);
  }
}
