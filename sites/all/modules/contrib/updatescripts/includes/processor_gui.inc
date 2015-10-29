<?php
/**
 * @copyright 	2012 (c) By Bright Solutions GmbH
 * @author		Marc Sven Kleinboehl
 *
 * This include file contains all of the functions of the aspect for GUI driven processing of the update scripts.
 */

/**
 * The form building callback of the GUI updatescript processing form.
 *
 * @learn more about submit callbacks @drupals form API manuals.
 */
function _updatescripts_batch_form() {
   
  drupal_add_library ('system', 'ui.dialog');
  drupal_add_js(array('updatescripts' => array('wait_loading_log' => t('Please, wait while the log is loading.'))), 'setting');
  drupal_add_js (drupal_get_path ('module', 'updatescripts') . '/js/updatescripts.js');

  module_load_include ('inc', 'updatescripts', 'includes/register');
  
  $form = array ();
  
  // Just a container for the jquery dialog which shows the log of a script.
  $form['dialog'] = array (
  	'#type'    => 'markup',
    '#markup'  => '<div id="updatescripts-dialog"></div>'
  );
  
  // Fieldset for unprocessed scripts.
  $form['unprocessed_scripts'] = array (
      '#type'    => 'fieldset',
      '#title'	 => t('Unprocessed scripts'),    
  );
  
  $form['unprocessed_scripts']['table'] = array (
      '#type'    => 'markup',
      '#markup'	 => _updatescripts_get_table_of_unprocessed_scripts ()
  );
    
  $form['unprocessed_scripts']['confirm'] = array (
			'#id'        => 'updatescripts-process-scripts-submit',
      '#type'      => 'submit',
      '#value'     => t('Start processing?'),
      '#disabled'  => count (_updatescripts_detect_unprocessed_scripts ()) == 0
  );
  
  // Fieldset which shows the next best number for a new script.
  $form['next_script_number'] = array (
      '#type'        => 'fieldset',
      '#title'	     => t('Next best number for a new update script'),
      '#description' => _updatescripts_detect_next_best_script_number () . '-your-fancy-updatescript.php'
  );
  
  // Fieldset for processed scripts.
  $form['processed_scripts'] = array (
        '#type'   => 'fieldset',
        '#title'  => t('Processed scripts'),    
  );
  
  $form['processed_scripts']['table'] = array (
        '#type'		 => 'markup',
        '#markup'	 => _updatescripts_get_table_of_processed_scripts ()
  );
  
  $form['processed_scripts']['links'] = array (
        '#type'		 => 'markup',
        '#markup'	 => theme ('updatescripts_icon_link', array ('icon_type' => 'log', 'url'=>'admin/config/updatescripts/meta-log.txt', 'blank'=>TRUE))
  );
  
  // Give credit where credit is due.
  $form['updatescript-footer'] = array (
    '#type'    => 'markup',
    '#markup'  => '<div id="updatescripts-footer">2012&copy; <a href="http://www.brightsolutions.de" title="Bright Solutions GmbH">By Bright Solutions GmbH</a> &bull; Written by <a href="http://www.hroudtwolf.de" title="Marc Sven Kleinboehl">Marc Sven Kleinboehl</a></div>'
  );
  
  return $form;
}

/**
 * The form submit callback of the  _updatescripts_batch_form  form.
 *
 * @learn more about submit callbacks @drupals form API manuals.
 */
function _updatescripts_batch_form_submit($form, &$form_state) {
  
  if (! lock_acquire('updatescripts')) {
    drupal_set_message(t('Temporaly not possible. Updatescript processing is currently locked for a concurrent process.'), 'error');
    return;
  }
    
  module_load_include('inc', 'updatescripts', 'includes/register');
  
  $scripts              = _updatescripts_detect_unprocessed_scripts ();
  $operations           = array ();
  $script_data_for_hook = array ();
  
  foreach ($scripts as $script) {
    $operations[] = array (
      '_updatescripts_process_script', 
      array ($script)
    );
    $script_data_for_hook[] = $script;
  }
  
  module_invoke_all('updatescripts_batch_process_created', $script_data_for_hook);

  $batch = array(
    'title'      => t('Processing'),
    'operations' => $operations,
    'finished'   => '_updatescripts_finish_processing',
    'file'       => drupal_get_path ('module', 'updatescripts') . 
                    '/includes/processor_gui.inc',
  );
  
  batch_set($batch);
  
  return;
}

/**
 * It is a task callback of the updatescript batch processing.
 * Learn more about batch callbacks @drupals batch API manuals.
 */
function _updatescripts_process_script($filepath, &$context) {
 
  module_load_include ('inc', 'updatescripts', 'includes/UpdatescriptEntity.class');
  
  $scriptEntity = UpdateScriptEntity::load($filepath);
  $scriptEntity->saveEntity ();
  unset ($scriptEntity);
  
  return;
}

/**
 * It is the last callback in a updatescript batch processing.
 * Learn more about batch callbacks @drupals batch API manuals.
 */
function _updatescripts_finish_processing ($success, $results, $operations) {
  
  lock_release ('updatescripts');
  
  if ($success) {
    drupal_set_message(t('Finished processing updatescripts.'));
  }else{
    
    $error = reset($operations);
    
    drupal_set_message(t('An error occured while processing updatescript @script.', array ('@script'=>print_r($error[0], TRUE))));
    
    menu_cache_clear_all();
    cache_clear_all();
  } 
  
  module_invoke_all('updatescripts_batch_process_finished', $success, $results, $operations);
   
  return;
}

/**
 * Creates a HTML table of not processed scripts.
 * @return string	The HTML table.
 */
function _updatescripts_get_table_of_unprocessed_scripts () {
  
  module_load_include ('inc', 'updatescripts', 'includes/register');
  
  $scripts = _updatescripts_detect_unprocessed_scripts ();
  $rows    = array ();
  
  if (empty ($scripts)) {
    drupal_set_message (t('This installation is up to date.'), 'updatescripts_status');
    return theme('status_messages', array ('display'=>'updatescripts_status'));
  }
  
  foreach ($scripts as $script) {
    $rows[] = array (
      basename ($script),
      format_date (filectime ($script)),
      format_size (filesize ($script))
    );
  }
  
  return theme ('table', array ('header'=>array (t('Filename'), t('Date'), t('Size')), 'rows'=>$rows));  
}

/**
 * Creates a HTML table of already processed scripts.
 *
 * @return string	The HTML table.
 */
function _updatescripts_get_table_of_processed_scripts () {

	module_load_include ('inc', 'updatescripts', 'includes/register');

	$registered = _updatescripts_get_processed_scripts (TRUE);
	$rows       = array ();

	if (empty ($registered)) {
		drupal_set_message (t('There are no updatescripts available.'), 'updatescripts_status');
		return theme('status_messages', array ('display'=>'updatescripts_status'));
	}

	foreach ($registered as $script) {
	  
	    $filepath = _updatescripts_get_scripts_path () . '/' . $script['script'];
	  
		$rows[] = array (
    		basename ($script['script']),
    		format_date ($script['register_time']),
    		$script['processed'] == TRUE ? t('Yes') : t('No'),
    		$script['process_times'],
    		($script['processed'] == TRUE ? l(t('Revert'),'admin/config/updatescripts/revert/' . $script['update_hash']) . '&nbsp;&bull;&nbsp;' : '') . 
		    l(t('Log'),'admin/config/updatescripts/log/' . $script['update_hash'], array('attributes' => array('class' => array('updatescripts-show-log-link'))))
		);
	}

	return theme ('table', array ('header'=>array (
	  t('Filename'), 
	  t('Register time'),
	  t('Process finished'),
	  t('Process times'),
	  t('Operation')
	), 'rows'=>$rows)) .
  theme('pager', array('tags' => array()));
}

/**
 * An AJAX callback. It delivers a full rendered output of the log of a script.
 *
 * @param string $update_hash	The hash of a registered updatescript.
 */
function _updatescripts_ajax_show_log ($update_hash) {

  module_load_include ('inc', 'updatescripts', 'includes/register');
  
  print (
    nl2br (
      _updatescripts_get_script_log ($update_hash)
    )
  );
 
  return;
}

/**
 * A confirm form for reverting updatescripts.
 *
 * @param string	$update_hash	The hash of a specific script you want to revert.
 */
function _updatescripts_revert_script_confirm_form ($form, $form_state, $update_hash) {
 
  $form                = array ();
  $form['update_hash'] = array (
    '#type'	  => 'value',
    '#value'  => $update_hash  
  );
  
  return confirm_form($form,
    	t('Are you sure you want to revert this script?'),
    	'admin/config/development/updatescripts',
    	t('This action cannot be undone.'),
    	t('Revert'),
    	t('Cancel'));
}

/**
 * The submit callback of the _updatescripts_revert_script_confirm_form form.
 */
function _updatescripts_revert_script_confirm_form_submit ($form, &$form_state) {
  
	$form_values = $form_state['values'];

	if ($form_values['confirm']) {
	  
	  module_load_include ('inc', 'updatescripts', 'includes/register');
	   
	  _updatescripts_revert_script ($form_values['update_hash']);
	  
	  drupal_set_message (t('Script reverted.'));
	}
	
	drupal_goto ('admin/config/development/updatescripts');
	
	return;
}
