<?php
/*
 * @copyright 	2012 (c) By Bright Solutions GmbH
 * @author		Marc Sven Kleinboehl
 *
 * This include file contains all of the functions of the aspect for remote driven processing of the update scripts.
 */

/*
 * Checks whether the user is allowed to process the updatescripts.
 */
function _updatescripts_processing_permitted ($submitted_key) {
  
  global $user;
  
  return (isset ($user->uid) && $user->uid == 1) || $submitted_key ==  drupal_get_private_key ();
}

/*
 * Sends a HTTP response message.
 * @param integer	$status		The HTTP status code..
 * @param string	$message	The message.
 */
function _updatescripts_send_HTTP_response ($status, $message) {
  
  static $status_codes = array (
    '200' => 'OK',
    '304' => 'Not modified',
    '403' => 'Forbidden',
  	'404' => 'Not found'    
  );
  
  $status = $status . ' ' . $status_codes[$status];

  header('HTTP/1.0 ' . $status);
  header('Status: ' . $status);
  header('Content-Type: text/plain');
  
  print ($message);
  
  return;
}

/*
 * Starts an updatescript process.
 * @param string $drupal_private_key	The private key of the drupal installation for authorisation issue.
 */
function _updatescripts_process ($drupal_private_key) {
  
  if (! lock_acquire('updatescripts')) {
    print (t('Error. Temporaly not possible. Updatescript processing is currently locked for a concurrent process.'));
    return;
  }
  
  
  if (! _updatescripts_processing_permitted ($drupal_private_key)) {
    if (php_sapi_name() != 'cli') {
      _updatescripts_send_HTTP_response (403, t('Access denied.'));
    }else{
      print (t('Access denied'));
    }
    return;
  }
  
  module_load_include ('inc', 'updatescripts', 'includes/register');
  
  $unprocessed_scripts = _updatescripts_detect_unprocessed_scripts ();
 
  if (empty ($unprocessed_scripts)) {
    if (php_sapi_name() != 'cli') {
     _updatescripts_send_HTTP_response (304, t('No new scripts available.'));
    }else{
      print(t('No new scripts available.'));
    }
    
    lock_release ('updatescripts');
    return;
  }
  
  variable_set ('site_offline' , '1');
  
  module_load_include ('inc', 'updatescripts', 'includes/UpdatescriptEntity.class');
  
  foreach ($unprocessed_scripts as $script) {
    _updatescripts_run_script ($script);
  }
  
  menu_cache_clear_all();
  cache_clear_all();
  
  variable_set ('site_offline' , '0');

  if (php_sapi_name() != 'cli') {
    _updatescripts_send_HTTP_response (200, t('Ok'));
  }else{
    print (t('Ok'));
  }
  
  lock_release ('updatescripts');
  
  return null;
}

/*
 * Runs a single script.
 * @param string	$script	The filename of the script.
 */
function _updatescripts_run_script ($script) {
  
  module_load_include ('inc', 'updatescripts', 'includes/UpdatescriptEntity.class');
  
  $scriptEntity = UpdateScriptEntity::load($script);
  $scriptEntity->saveEntity ();
  unset ($scriptEntity);
  
  return;
}