<?php

$update_free_access = FALSE;
$drupal_hash_salt = '77ZV3FrUZwI8t3SieDN0TV2TWa1vzOWwFYSHtUWWwdY';
ini_set('session.gc_probability', 1);
ini_set('session.gc_divisor', 100);
ini_set('session.gc_maxlifetime', 200000);
ini_set('session.cookie_lifetime', 2000000);

$conf['404_fast_paths_exclude'] = '/\/(?:styles)\//';
$conf['404_fast_paths'] = '/\.(?:txt|png|gif|jpe?g|css|js|ico|swf|flv|cgi|bat|pl|dll|exe|asp)$/i';
$conf['404_fast_html'] = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN" "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd"><html xmlns="http://www.w3.org/1999/xhtml"><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL "@path" was not found on this server.</p></body></html>';

/**
 * Master module configuration.
 */
$conf['install_profile'] = 'dkan';
$conf['master_version'] = 2;
$conf['master_modules'] = array(
  'base' => array(
    'dkan',
    'dkan_sitewide_roles_perms',
    'variable',
    'unlink_defaults',
    'l10n_update',
    'i18nviews',
    'i18n',
    'metatag',
    'dropguard',
    'blog',
    'fe_block',
    'feature_od_projects',
    'googleanalytics',
    'feature_od_publication',
    'backup_migrate',
    'xmlsitemap',
    'xmlsitemap_node',
    'xmlsitemap_engines',
    'cpn',
  ),
  'local' => array(),
  'dev' => array(),
  'live' => array(),
);
$conf['master_uninstall_blacklist'] = array(
  'base' => array(),
  'local' => array(),
  'dev' => array(),
  'live' => array(),
);
$conf['master_removable_blacklist'] = array(
  0 => 'modules/*',
);

$local_settings = __DIR__ . '/settings.local.php';
if (file_exists($local_settings)) {
  include $local_settings;
}
