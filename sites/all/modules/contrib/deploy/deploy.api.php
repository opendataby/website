<?php

/**
 * @file
 * Hooks provided by the Deploy module.
 */

/**
 * Allow modules to modify an entity before it gets deployed.
 *
 * @param $entity
 *   The entity being deployed.
 *
 * @param $entity_type
 *   The entity type; for example 'node' or 'user'.
 */
function hook_deploy_entity_alter(&$entity, $entity_type) {

}

/**
 * Allow modules to add preprocess or postprocess callbacks to a deployment.
 *
 * @return array
 *   A nested array containing preprocess and/or postprocess operations. The
 *   first level of the array needs to contain the keys 'postprocess' and/or
 *   'preprocess'.
 *
 *   The second level is an array of operations, where each operation contains a
 *   'callback' key with the name of the function to be run. Each callback
 *   function accepts two parameters:
 *   - plan_name: The machine name of the deployment plan.
 *   - entity: The entity being deployed.
 *
 * @see DeployProcessor::preProcess()
 * @see DeployProcessor::postProcess()
 */
function hook_deploy_operation_info() {
  return array(
    'postprocess' => array(
      array('callback' => 'deploy_manager_postprocess_operation'),
    ),
  );
}

/**
 * Allow module to alter a deploy plan when it is loaded.
 *
 * @param $plan
 *   The deployment plan to be altered.
 */
function hook_deploy_plan_load_alter(&$plan) {

}

/**
 * Allow module to react to publishing a deploy plan.
 *
 * @param $status
 *   The boolean result of publishing the plan.
 */
function hook_deploy_plan_publish($status) {
  // Set a message based on the deployment result.
  if ($status) {
    drupal_set_message(t('Deployment was successful.'));
  }
  else {
    drupal_set_message(t('Deployment failed.'), 'error');
  }
}
