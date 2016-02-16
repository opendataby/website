<?php
/**
 * @file
 * Deploy Services module services functions.
 */

/**
 * Implements hook_services_resources().
 */
function deploy_services_services_resources() {
  $resources = array('deploy' => array());

  $resources['deploy']['index'] = array(
    'help' => t('This method returns a list of deployment plans'),
    'callback' => 'deploy_services_index',
    'file' => array('type' => 'inc', 'module' => 'deploy', 'name' => 'deploy.services'),
    // TODO add support for args
    'args' => array(),
    'access arguments' => array('administer deployments'),
  );

  $resources['deploy']['create'] = array(
    'help' => t('Creates a deployment plan'),
    'callback' => 'deploy_services_create',
    'file' => array('type' => 'inc', 'module' => 'deploy', 'name' => 'deploy.services'),
    'args' => array(
      array(
        'name' => 'data',
        'type' => 'struct',
        'description' => 'The plan object',
        'source' => 'data',
        'optional' => FALSE,
      ),
    ),
    'access arguments' => array('administer deployments'),
  );

  $resources['deploy']['retrieve'] = array(
    'file' => array('type' => 'inc', 'module' => 'deploy', 'name' => 'deploy.services'),
    'help' => t('Retrieve a deployment plan'),
    'callback' => 'deploy_services_retrieve',
    'args' => array(
      array(
        'name' => 'name',
        'type' => 'string',
        'description' => 'The name of the plan to fetch',
        'source' => array('path' => '0'),
        'optional' => FALSE,
      ),
    ),
    'access arguments' => array('administer deployments'),
  );

  $resources['deploy']['update'] = array(
    'callback' => 'deploy_services_update',
    'file' => array('type' => 'inc', 'module' => 'deploy', 'name' => 'deploy.services'),
    'args' => array(
      array(
        'name' => 'name',
        'optional' => FALSE,
        'source' => array('path' => 0),
        'description' => 'The name of the deployment plan.',
        'type' => 'int',
      ),
      array(
        'name' => 'config',
        'optional' => FALSE,
        'source' => 'data',
        'description' => 'The configuration for the deployment plan.',
        'type' => 'array',
      ),
    ),
    'access arguments' => array('administer deployments'),
  );

  $resources['deploy']['targeted_actions'] = array();
  $resources['deploy']['targeted_actions']['deploy'] = array(
    'help' => t('This method deploys a deployment plan.'),
    'callback' => 'deploy_services_deploy',
    'file' => array('type' => 'inc', 'module' => 'deploy', 'name' => 'deploy.services'),
    'args' => array(
      array(
        'name' => 'name',
        'type' => 'string',
        'description' => 'The name of the plan to fetch',
        'source' => array('path' => '0'),
        'optional' => FALSE,
      ),
    ),
    'access arguments' => array('administer deployments'),
  );

  $resources['deploy']['targeted_actions']['diff'] = array(
    'help' => t('This method provides a diff of a plan.'),
    'callback' => 'deploy_services_diff_plan',
    'file' => array('type' => 'inc', 'module' => 'deploy_services', 'name' => 'deploy_services.services'),
    'args' => array(
      array(
        'name' => 'name',
        'type' => 'string',
        'description' => 'The name of the plan to fetch',
        'source' => array('path' => '0'),
        'optional' => FALSE,
      ),
    ),
    'access arguments' => array('diff deployment plans'),
  );

  return $resources;
}

/**
 * Services index operation callback.
 *
 * @return
 *   A list of available deployment plans.
 */
function deploy_services_index() {
  $plans = deploy_plan_load_all();

  foreach ($plans as $plan) {
    if (is_object($plan)) {
      unset($plan->aggregator->plan);
      unset($plan->processor->plan);
    }
  }

  return $plans;
}

/**
 * Services create operation callback.
 *
 * @param arary $data
 *  The configuration for the plan.
 *
 * @return array
 *  Details of the new plan.
 */
function deploy_services_create($data) {
  $plan = deploy_plan_save($data);

  return array(
    'pid' => $plan->pid,
    'name' => $plan->name,
    'uri' => services_resource_uri(array('deploy', $plan->name)),
  );
}

/**
 * Services retrieve operation callback.
 *
 * @param $name
 *   The name of the plan to retrieve.
 *
 * @return
 *  The deployment plan object or FALSE if not found.
 */
function deploy_services_retrieve($name) {
  $plan = deploy_plan_load($name);


  if (is_object($plan)) {
    unset($plan->aggregator->plan);
    unset($plan->processor->plan);
  }

  return $plan;
}

/**
 * Services update operation callback.
 *
 * @param string $name
 *   The name of the plan to update.
 * @param arary $data
 *  The configuration for the plan.
 *
 * @return array
 *  Details of the updated plan.
 */
function deploy_services_update($name, $data) {
  $data['name'] = $name;
  $plan = deploy_plan_save($data);

  return array(
    'pid' => $plan->pid,
    'name' => $plan->name,
    'uri' => services_resource_uri(array('deploy', $plan->name)),
  );
}

/**
 * Services deploy action callback.
 *
 * @param $name
 *   The name of the plan to retrieve.
 *
 * @return
 *   TRUE on success, Exception on error or FALSE if the plan is not found.
 */
function deploy_services_deploy($name) {
  $plan = deploy_plan_load($name);
  if (!$plan) {
    return services_error(t('Not Found'), 404, t("Plan '@plan' not found", array('@plan' => $plan)));
  }

  try {
    $plan->deploy();
  } catch (Exception $e) {
    return services_error(t('Internal Server Error'), 500, $e->getMessage());
  }
  return TRUE;
}

/**
 * Services targeted action to show diff of all entities of a plan
 *
 * @param string $plan_name
 *   The name of the plan to diff.
 *
 * @return array
 *   A list of all entities diffed from the given deploy plan.
 */
function deploy_services_diff_plan($plan_name) {
  $diffs = array();

  $plan = deploy_plan_load($plan_name);
  // TODO handle plan not being found - need to return a 404.
  $entities = deploy_manager_get_entities($plan->name);

  foreach ($entities as $entity) {
    $diffs["{$entity['type']}-{$entity['id']}-{$entity['revision_id']}"] = deploy_services_diff_entity($entity['type'], $entity['id'], $entity['revision_id']);
  }
  return $diffs;
}

/**
 * Helper function to diff two revisions.
 *
 * @param string $type
 *   The entity type. (Ex: node)
 * @param int $new_revision
 *   The new revision key.
 * @param int $old_revision (optional)
 *   The old revision key.
 *
 * @return array
 *   An array with the diff and the info of entity.
 */
function deploy_services_diff_entity($type, $id, $new_revision, $old_revision = NULL) {
  module_load_include('inc', 'diff', 'diff.pages');

  $entity_info = entity_get_info($type);

  $id_key = $entity_info['entity keys']['id'];

  $bundle_key = NULL;
  if (!empty($entity_info['entity keys']['bundle'])) {
    $bundle_key = $entity_info['entity keys']['bundle'];
  }

  $revision_key = NULL;
  if (!empty($entity_info['entity keys']['revision'])) {
    $revision_key = $entity_info['entity keys']['revision'];
  }

  if ($new_revision) {
    $new_entity = entity_revision_load($type, $new_revision);
  }
  else {
    $new_entity = entity_load_single($type, $id);
  }

  if (!$new_entity) {
    return NULL;
  }

  // Set up the latest revision before the $new_revision.
  if (isset($entity_info['revision table']) && !$old_revision) {
    $select = db_select($entity_info['revision table'], 'rt')
      ->condition($revision_key, $new_entity->{$revision_key}, '<')
      ->condition($id_key, $new_entity->{$id_key});
    $select->addExpression("MAX({$revision_key})", 'max_rev');
    $old_revision = $select->execute()
      ->fetchField();
  }

  if ($old_revision) {
    $old_entity = entity_revision_load($type, $old_revision);
  }
  elseif ('file' == $type) {
    // hack because file entities are broken!
    $old_entity = (object) array(
      'fid' => $id,
      'uid' => $new_entity->uid,
      'filename' => $new_entity->filename,
      'uri' => $new_entity->uri,
      'filemime' => $new_entity->filemime,
      'filesize' => 0,
      'status' => $new_entity->status,
      'timestamp' => 0,
      'uuid' => '',
    );
  }
  else {
    /*
    If the old entity can't be found create a new empty one.
    This a hack to make sure the diff shows new entities properly.
    */
    $entity_values = array(
      $id_key => $new_entity->{$id_key},
    );

    if ($bundle_key) {
      $entity_values[$bundle_key] = $new_entity->{$bundle_key};
    }

    $old_entity = entity_create($type, $entity_values);
    field_attach_load($type, array($new_entity->{$id_key} => $old_entity), FIELD_LOAD_REVISION);
  }

  $context = array('entity_type' => $type);
  $uri = entity_uri($type, $new_entity);
  $uri['options']['absolute'] = TRUE;

  $diff = array();
  $info = array(
    'label' => entity_label($type, $new_entity),
    'old_label' => entity_label($type, $old_entity),
    'fields' => array(),
    'url' => url($uri['path'], $uri['options']),
  );
  $entity_diff = diff_compare_entities($old_entity, $new_entity, $context);
  foreach ($entity_diff as $field => $data) {
    if ('#sorted' == $field) {
      continue;
    }

    $context = $type;
    if (!empty($bundle_key)) {
      $context = $new_entity->{$bundle_key};
    }

    $info['fields'][$field] = field_info_instance($type, $field, $context);
    list($old_field, $new_field) = diff_extract_state($data);
    $diff[$field] = diff_get_rows($old_field, $new_field, FALSE);
  }

  if (empty($diff)) {
    $diff = NULL;
  }

  return array('diff' => $diff, 'info' => $info);
}
