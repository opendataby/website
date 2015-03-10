<?php

/**
 * @file
 * AJAX comments settings form.
 */

/**
 * AJAX comments settings form.
 */
function ajax_comments_settings() {
  $form['ajax_comments_node_types'] = array(
    '#title' => t('Content types'),
    '#type' => 'checkboxes',
    '#description' => t('Select node types you want to activate ajax comments on. If you select nothing, AJAX Comments will be enabled everywhere.'),
    '#default_value' => variable_get('ajax_comments_node_types', array()),
    '#options' => node_type_get_names(),
  );
  $form['ajax_comments_notify'] = array(
    '#title' => t('Notification Message'),
    '#type' => 'checkbox',
    '#description' => t('Add notification message to comment when posted.'),
    '#default_value' => variable_get('ajax_comments_notify', ''),
  );

  $entity_info = entity_get_info('node');
  foreach ($entity_info['view modes'] as $view_mode => $view_mode_info) {
    $view_modes[$view_mode] = $view_mode_info['label'];
  }

  $form['ajax_comments_view_modes'] = array(
    '#title' => t('View modes'),
    '#type' => 'checkboxes',
    '#description' => t('Select which view modes you want to activate ajax comments on. If you select nothing, AJAX Comments will be enabled everywhere.'),
    '#default_value' => variable_get('ajax_comments_view_modes', array()),
    '#options' => $view_modes,
  );


  return system_settings_form($form);
}
