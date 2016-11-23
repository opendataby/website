<?php
/**
 * @file
 * Deploy UI page functions.
 */

/**
 * Page callback for the overview page.
 */
function deploy_ui_overview_page() {
  $plans = deploy_plan_load_all_enabled();
  $blocks = array();

  // Iterate over all plans.
  foreach ($plans as $plan) {
    $info = array();

    // Get the entity keys from the aggregator.
    $entity_keys = $plan->getEntities();
    foreach ($entity_keys as $entity_key) {
      // Get the entity info and all entities of this type.
      $entity_info = entity_get_info($entity_key['type']);

      if (!empty($entity_info['entity keys']['revision']) && !empty($entity_key['revision_id'])) {
        $entity = entity_revision_load($entity_key['type'], $entity_key['revision_id']);
      }
      else {
        $entity = entity_load_single($entity_key['type'], $entity_key['id']);
      }

      $title = "{$entity_key['type']}:{$entity_key['id']}";
      $label = entity_label($entity_key['type'], $entity);
      if ($label) {
        $title = $label;
      }

      if ($entity_info['entity keys']['revision'] && !empty($entity_key['revision_id'])) {
        $title = t('@title (rev:@rev_id)', array('@title' => $title, '@rev_id' => $entity_key['revision_id']));
      }

      // Some entities fail fatally with entity_uri() and
      // entity_extract_ids(). So handle this gracefully.
      try {
        $uri = entity_uri($entity_key['type'], $entity);
        if ($uri) {
          $title = l($title, $uri['path'], $uri['options']);
        }
      }
      catch (Exception $e) {
        watchdog_exception('deploy_ui', $e);
      }
      // Construct a usable array for the theme function.
      $info[] = array(
        'title' => $title,
        'type' => $entity_info['label'],
      );
    }

    // Construct a usable array for the theme function.
    $blocks[] = array(
      'plan_name' => check_plain($plan->name),
      'plan_title' => check_plain($plan->title),
      'plan_description' => check_plain($plan->description),
      'content' => theme('deploy_ui_overview_plan_content', array('info' => $info)),
      'fetch_only' => $plan->fetch_only,
      'status' => deploy_plan_get_status($plan->name),
    );
  }
  return theme('deploy_ui_overview', array('blocks' => $blocks));
}

/**
 * Theme callback for a plan's content.
 */
function theme_deploy_ui_overview_plan_content($variables) {
  $info = $variables['info'];
  $header = array(t('Title'), t('Type'));
  $rows = array();

  foreach ($info as $values) {
    $rows[] = array($values['title'], $values['type']);
  }
  if (empty($rows)) {
    $rows = array(array(array(
      'colspan' => 2,
      'data' => t('Currently no content in this plan.'),
    )));
  }
  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Theme callback for the overview page.
 */
function theme_deploy_ui_overview($variables) {
  drupal_add_css(drupal_get_path('module', 'deploy_ui') . '/css/deploy_ui.admin.css');

  $blocks = $variables['blocks'];
  $container = array();

  $i = 0;
  foreach ($blocks as $block) {
    $position = ++$i % 2 ? 'left' : 'right';
    $container[$position][] = $block;
  }

  $output = '<div class="admin clearfix">';
  foreach ($container as $position => $blocks) {
    foreach ($blocks as $block) {
      $status_info = deploy_status_info($block['status']);

      $output .= '<div class="' . $position . ' clearfix">';
      $output .= '<div class="admin-panel deploy-panel">';
      $output .= '<h3>' . $block['plan_title'] . '</h3>';
      if (!$block['fetch_only'] && $status_info) {
        $output .= '<div class="messages ' . $status_info['class'] . '">';
        $output .= '<h4 class="element-invisible">Status message</h4>';
        $output .= $status_info['title'];
        $output .= '</div>';
      }
      $output .= '<div class="description">';
      $output .= '<h4 class="element-invisible">Plan description</h4>';
      $output .= $block['plan_description'];
      $output .= '</div>';
      if (!$block['fetch_only']) {
        $actions = array(
          array(
            'title' => t('Deploy'),
            'href' => 'admin/structure/deploy/plans/list/' . $block['plan_name'] . '/deploy',
            'query' => array(
              'cancel_path' => $_GET['q'],
            ),
          ),
          array(
            'title' => t('Empty'),
            'href' => 'admin/structure/deploy/' . $block['plan_name'] . '/empty',
          ),
        );
        $output .= theme('links', array('links' => $actions, 'attributes' => array('class' => 'action-links')));
      }
      else {
        $output .= '<div class="description">' . t('This plan is <em>fetch-only</em>, and can therefore not be deployed in push fashion.') . '</div>';
      }
      $output .= '<div class="body">';
      $output .= $block['content'];
      $output .= '</div>';
      $output .= '</div>';
      $output .= '</div>';
    }
  }
  $output .= '</div>';
  return $output;
}

/**
 * Form constructor for the empty plan page.
 */
function deploy_ui_empty_plan_form($form, &$form_state, $plan) {
  $form = array();

  $form['deploy_plan'] = array(
    '#type' => 'value',
    '#value' => $plan,
  );

  return confirm_form(
    $form,
    t('Are you sure you want to empty the !name plan?', array(
      '!name' => $plan->name,
      )
    ),
    'admin/structure/deploy',
    t('Emptying the plan will remove all items from the plan.'),
    t('Empty'),
    t('Cancel')
  );
}

/**
 * Submit handler for empty plan form.
 */
function deploy_ui_empty_plan_form_submit($form, &$form_state) {
  $plan = $form_state['values']['deploy_plan'];

  // Get the entity keys from the aggregator.
  $entity_keys = $plan->getEntities();

  foreach ($entity_keys as $entity_key) {
    $entity = entity_load_single($entity_key['type'], $entity_key['id']);
    deploy_manager_delete_from_plan($plan->name, $entity_key['type'], $entity);
  }

  drupal_set_message(
    t('All items were removed from the !plan plan.', array('!plan' => $plan->title))
  );

  $form_state['redirect'] = 'admin/structure/deploy';
}
