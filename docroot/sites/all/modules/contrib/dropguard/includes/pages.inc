<?php

/**
 * @file
 * Contains page callbacks for Drop Guard module.
 */

/**
 * Access callback for page which exposes info about a web site.
 *
 * @param string $type
 *   Type of request. Currently supported two types:
 *   - connect. Checks if Drop Guard is able to connect to this web site.
 *   - modules. Returns array with information about enabled modules/themes.
 */
function dropguard_site_info_callback($type) {

  // Prevent this page from caching by drupal.
  drupal_page_is_cacheable(FALSE);

  // If Drop Guard wants only to check connection status, then we don't have to
  // expose any data. And access already checked in page access callback.
  if ($type == 'connect') {
    drupal_json_output(TRUE);
  }
  // If Drop Guard wants to get info about installed modules, we need to provide
  // this info here.
  else {
    // Get setting which provides information about way to update distribution
    // if it is enabled in this project. We've checked that this value exists
    // during access callback for the current page.
    $distribution_update = $_POST['distribution_update'];

    // Get information about currently enabled modules/themes/core/distribution.
    $data = dropguard_enabled_projects_info($distribution_update);

    // Encrypt and print data in json.
    drupal_json_output(dropguard_encrypt($data));
  }
}
