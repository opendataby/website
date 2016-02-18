<?php
/**
 * @file
 * dkan_sitewide_demo_front.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function dkan_sitewide_demo_front_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_frontpage';
  $strongarm->value = 'front';
  $export['site_frontpage'] = $strongarm;

  return $export;
}
