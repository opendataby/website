<?php
/**
 * @file
 * feature_opendata_voting.features.inc
 */

/**
 * Implements hook_field_default_field_instances_alter().
 */
function feature_opendata_voting_field_default_field_instances_alter(&$data) {
  if (isset($data['node-dataset-field_rating'])) {
    $data['node-dataset-field_rating']['display']['teaser']['weight'] = 11; /* WAS: 0 */
    $data['node-dataset-field_rating']['widget']['weight'] = 8; /* WAS: 19 */
  }
}
