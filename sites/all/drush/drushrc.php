<?php
// Ignore the data in these tables, but keep the table structures.
$options['structure-tables']['common'] = array(
  'cache',
  'cache_admin_menu',
  'cache_block',
  'cache_bootstrap',
  'cache_field',
  'cache_filter',
  'cache_form',
  'cache_image',
  'cache_libraries',
  'cache_menu',
  'cache_page',
  'cache_path',
  'cache_token',
  'cache_update',
  'cache_views',
  'cache_views_data',
  'history',
  'search_dataset',
  'search_index',
  'search_node_links',
  'search_total',
  'sessions',
  'watchdog',
);
// Use the list of cache tables above.
$options['structure-tables-key'] = 'common';

// Enable verbose mode.
$options['v'] = 1;

// Ensure all rsync commands use verbose output.
$command_specific['rsync'] = array(
  'verbose' => TRUE,
  'exclude-paths' => 'blog',
  );
?>
