<?php

/**
 * @file
 * Rules implementations for ad hoc plans.
 */

/**
 * Implements hook_rules_action_info().
 */
function deploy_adhoc_plan_rules_action_info() {
  return array(
    'deploy_adhoc_plan_rules_action_deploy_plan' => array(
      'label' => t('Deploy ad hoc plan'),
      'group' => t('Deploy'),
      'access callback' => 'deploy_adhoc_plan_session_exists',
    ),
    'deploy_adhoc_plan_rules_action_add_to_managed_plan' => array(
      'label' => t('Add entity to ad hoc deployment plan'),
      'group' => t('Deploy'),
      'access callback' => 'deploy_adhoc_plan_session_exists',
      'parameter' => array(
        'entity' => array(
          'type' => 'entity',
          'label' => t('Entity'),
          'description' => t('The entity that shall be added to the plan.'),
          'wrapped' => TRUE,
        ),
      ),
    ),
    'deploy_adhoc_plan_manager_action_delete_from_plan' => array(
      'label' => t('Remove entity from ad hoc deployment plan'),
      'group' => t('Deploy'),
      'access callback' => 'deploy_adhoc_plan_session_exists',
      'parameter' => array(
        'entity' => array(
          'type' => 'entity',
          'label' => t('Entity'),
          'description' => t('The entity that shall be removed from the plan.'),
          'wrapped' => TRUE,
        ),
      ),
    ),
  );
}

/**
 * Action callback for the "Deploy a plan" action.
 */
function deploy_adhoc_plan_rules_action_deploy_plan($plan_name) {
  if (!empty($_SESSION['deploy_auto_plan_user_plan'])) {
    $plan = deploy_manager_plan_load($_SESSION['deploy_auto_plan_user_plan']);
    if ($plan) {
      $plan->deploy();
      return;
    }
  }
  drupal_set_message(t('Cannot deploy ad hoc plan.'), 'warning');
}

/**
 * Action callback for the "Add to ad hoc deploy plan" action.
 */
function deploy_adhoc_plan_rules_action_add_to_managed_plan($entity_wrapper) {
  if (empty($_SESSION['deploy_auto_plan_user_plan']) || !deploy_manager_plan_load($_SESSION['deploy_auto_plan_user_plan'])) {
    drupal_set_message(t('No ad hoc plan to add to.'), 'warning', FALSE);
    return;
  }
  $entity_type = $entity_wrapper->type();
  $entity = $entity_wrapper->value();
  deploy_manager_add_to_plan($_SESSION['deploy_auto_plan_user_plan'], $entity_type, $entity);
}

/**
 * Action callback for the "Remove from ad hoc deploy plan" action.
 */
function deploy_adhoc_plan_manager_action_delete_from_plan($entity_wrapper) {
  if (empty($_SESSION['deploy_auto_plan_user_plan']) || !deploy_manager_plan_load($_SESSION['deploy_auto_plan_user_plan'])) {
    drupal_set_message(t('No ad hoc plan to remove from.'), 'warning', FALSE);
    return;
  }
  $entity_type = $entity_wrapper->type();
  $entity = $entity_wrapper->value();
  deploy_manager_delete_from_plan($_SESSION['deploy_auto_plan_user_plan'], $entity_type, $entity);
}

/**
 * Access callback to ensure an ad hoc plan is set for the current user.
 */
function deploy_adhoc_plan_session_exists() {
  if (!empty($_SESSION['deploy_auto_plan_user_plan'])) {
    return TRUE;
  }

  return FALSE;
}
