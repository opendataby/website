<?php

/**
 * @file
 * Contains administrative forms to manage Drop Guard settings.
 */

/**
 * Main settings form of Drop Guard module.
 */
function dropguard_settings_form($form) {

  $link = l(t('Drop Guard'), 'http://drop-guard.net');
  $form['info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Connect to Drop Guard'),
    '#description' => t('All information below are available when creating a new project to support automated updates using !link', array('!link' => $link)),
    '#collapsible' => TRUE,
  );

  $form['info']['dropguard_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('User ID'),
    '#description' => t('Copy the User ID here from the Drop Guard service. It is available during the creation or editing process of a project.'),
    '#required' => TRUE,
    '#maxlength' => 10,
    '#size' => 10,
    '#element_validate' => array('element_validate_integer_positive'),
    '#default_value' => variable_get('dropguard_client_id'),
  );

  // We call it "Access token", but it is actually a base64-encoded public key
  // for openssl encryption/decryption. Just to avoid misunderstandings from
  // client point of view, we want to provide the most user-friendly name.
  $form['info']['dropguard_openssl_public_key'] = array(
    '#type' => 'textarea',
    '#title' => t('Access Token'),
    '#description' => t('Copy the Access Token to this textarea from Drop Guard service. It is available during the creation or editing process of a project.'),
    '#required' => TRUE,
    '#size' => 6,
    '#default_value' => variable_get('dropguard_openssl_public_key'),
  );

  // Make sure that PHP OpenSSL library is enabled.
  // Print warning message and disable possibility to input date otherwise.
  if (!extension_loaded('openssl')) {
    $form['info']['#description'] .= '<br/><span style="color:red;">' . t('<a href="@url">PHP OpenSSL extension</a> is missing on your server. Drop Guard needs it for the secure transfer of information from your web site.', array('@url' => 'http://php.net/manual/en/book.openssl.php')) . '</span>';
    $form['info']['dropguard_client_id']['#disabled'] = TRUE;
    $form['info']['dropguard_openssl_public_key']['#disabled'] = TRUE;
  }

  return system_settings_form($form);
}

/**
 * Validate main settings form of Drop Guard module.
 */
function dropguard_settings_form_validate($form, &$form_state) {
  $values = &$form_state['values'];

  // Trim possible whitespaces.
  $values['dropguard_client_id'] = trim($values['dropguard_client_id']);
  $values['dropguard_openssl_public_key'] = trim($values['dropguard_openssl_public_key']);
}
