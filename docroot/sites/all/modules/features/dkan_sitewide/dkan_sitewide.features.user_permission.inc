<?php
/**
 * @file
 * dkan_sitewide.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function dkan_sitewide_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'view disqus comments'.
  $permissions['view disqus comments'] = array(
    'name' => 'view disqus comments',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'disqus',
  );

  return $permissions;
}
