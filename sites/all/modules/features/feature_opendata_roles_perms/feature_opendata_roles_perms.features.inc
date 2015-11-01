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
    $data['administer advanced pane settings']['roles']['editor'] = 'editor'; /* WAS: '' */
    unset($data['administer advanced pane settings']['roles']['administrator']);
  }
  if (isset($data['administer page manager'])) {
    $data['administer page manager']['roles']['editor'] = 'editor'; /* WAS: '' */
  }
  if (isset($data['administer pane access'])) {
    $data['administer pane access']['roles']['editor'] = 'editor'; /* WAS: '' */
    unset($data['administer pane access']['roles']['administrator']);
  }
  if (isset($data['administer panels layouts'])) {
    $data['administer panels layouts']['roles']['editor'] = 'editor'; /* WAS: '' */
  }
  if (isset($data['administer panels styles'])) {
    $data['administer panels styles']['roles']['editor'] = 'editor'; /* WAS: '' */
  }
  if (isset($data['administer path breadcrumbs'])) {
    $data['administer path breadcrumbs']['roles']['editor'] = 'editor'; /* WAS: '' */
  }
  if (isset($data['administer permissions'])) {
    unset($data['administer permissions']['roles']['administrator']);
  }
  if (isset($data['administer users'])) {
    unset($data['administer users']['roles']['administrator']);
  }
  if (isset($data['administer views'])) {
    unset($data['administer views']['roles']['administrator']);
  }
  if (isset($data['change layouts in place editing'])) {
    $data['change layouts in place editing']['roles']['editor'] = 'editor'; /* WAS: '' */
    unset($data['change layouts in place editing']['roles']['administrator']);
  }
  if (isset($data['perform unlimited index queries'])) {
    $data['perform unlimited index queries']['roles']['anonymous user'] = 'anonymous user'; /* WAS: '' */
    $data['perform unlimited index queries']['roles']['authenticated user'] = 'authenticated user'; /* WAS: '' */
  }
  if (isset($data['use ipe with page manager'])) {
    $data['use ipe with page manager']['roles']['editor'] = 'editor'; /* WAS: '' */
    unset($data['use ipe with page manager']['roles']['administrator']);
  }
  if (isset($data['use page manager'])) {
    $data['use page manager']['roles']['editor'] = 'editor'; /* WAS: '' */
  }
  if (isset($data['use panels caching features'])) {
    $data['use panels caching features']['roles']['editor'] = 'editor'; /* WAS: '' */
  }
  if (isset($data['use panels dashboard'])) {
    $data['use panels dashboard']['roles']['editor'] = 'editor'; /* WAS: '' */
    unset($data['use panels dashboard']['roles']['administrator']);
  }
  if (isset($data['use panels in place editing'])) {
    $data['use panels in place editing']['roles']['editor'] = 'editor'; /* WAS: '' */
    unset($data['use panels in place editing']['roles']['administrator']);
  }
  if (isset($data['use panels locks'])) {
    $data['use panels locks']['roles']['editor'] = 'editor'; /* WAS: '' */
  }
  if (isset($data['use text format html'])) {
    $data['use text format html']['roles']['authenticated user'] = 'authenticated user'; /* WAS: '' */
  }
  if (isset($data['view pane admin links'])) {
    $data['view pane admin links']['roles']['editor'] = 'editor'; /* WAS: '' */
    unset($data['view pane admin links']['roles']['administrator']);
  }
}
