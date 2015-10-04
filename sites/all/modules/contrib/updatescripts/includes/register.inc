<?php
/**
 * @copyright 	2013+ (c) By Bright Solutions GmbH
 * @author		  Marc Sven Kleinboehl
 * 
 */

// We hate magic numbers.
define ('UPDATESCRIPTS_NEXT_BEST_NUMBER_STEP_SIZE', 10);
define ('UPDATESCRIPTS_NEXT_BEST_NUMBER_DIGITS', 4);
define ('UPDATESCRIPTS_PAGINATION_PAGE_SIZE', 8);

/**
 * Detects unprocessed updatescripts.
 *
 * @return array	An array which contains the names of the updatescipts.
 */
function _updatescripts_detect_unprocessed_scripts () {
  
  static $unprocessed_scripts = array ();
  
  if (! empty ($unprocessed_scripts)) {
    return $unprocessed_scripts;
  }
  
  $found_scripts           = file_scan_directory(_updatescripts_get_scripts_path (), '/.*\.php$/');  
  $processed_scripts       = _updatescripts_get_hashs_of_processed_scripts ();
 
  foreach ($found_scripts as $file) {

    if (! in_array (md5 ($file->uri), $processed_scripts)) {
      $unprocessed_scripts[intval ($file->filename)] = $file->uri;
    }
  } 
  
  ksort ($unprocessed_scripts);
  
  return $unprocessed_scripts;
}

/**
 * Returns an array which contains hashs of processed scripts.
 *
 * @return array	The array which contains the hashs.
 */
function _updatescripts_get_hashs_of_processed_scripts () {
  
  $processed_scripts = array ();
  
  $result = db_select ('updatescripts_register', 'r')
  ->fields ('r', array ('log', 'update_hash'))
  ->condition ('processed', true, '=') 
  ->execute();
  
  while ($row = $result->fetchAssoc ()) {
    $processed_scripts[] = $row['update_hash'];
  }

  return $processed_scripts;
}

/**
 * Returns an array which contains informations about processed scripts.
 *
 * @param boolean $paged (Optional)	TRUE for using with pagination.
 * @return array	The array which contains the informations.
 */
function _updatescripts_get_processed_scripts ($paged = FALSE) {

	$processed_scripts = array ();

	$db_query = db_select ('updatescripts_register', 'r');
		
	if ($db_query == FALSE) {
	  return array ();
	}
	$db_query->fields ('r', array ('update_hash', 'register_time', 'script', 'processed', 'process_times'));
	$db_query->orderBy('register_time', 'DESC');
	
	if ($paged == TRUE) {
	  $result = $db_query->extend ('PagerDefault')->limit (UPDATESCRIPTS_PAGINATION_PAGE_SIZE)->execute(); 	 
	}else{
	  $result = $db_query->execute(); 
	}

	while ($row = $result->fetchAssoc ()) {
		$processed_scripts[] = $row;
	}

	return $processed_scripts;
}

/**
 * Reverts a specific registered script.
 * The script will be ready for processing again.
 *
 * @param string $update_hash	The has of the registered script.
 */
function _updatescripts_revert_script ($update_hash) {
   
  // Load data.
  $script = db_select ('updatescripts_register', 'r')
  ->fields ('r', array (
    'script',
    'process_times'
  ))
  ->condition ('update_hash', $update_hash, '=')
  ->execute ();
  
  $script = $script->fetchObject ();
  if ($script === FALSE) {
    return;
  }
  
  // Revert.
  db_update ('updatescripts_register')
  ->fields (array (
  	'processed' => (integer)FALSE,
  ))
  ->condition ('update_hash', $update_hash, '=')
  ->execute ();

  
  module_invoke_all('updatescripts_revert', $script->script, $script->process_times);
  
  return;
}

/**
 * Retrieves the log of a specific registered script.
 *
 * @param string $update_hash	The has of the registered script.
 * @return string				The result as string.
 */
function _updatescripts_get_script_log ($update_hash) {

  $result = db_select ('updatescripts_register', 'r')
  ->fields ('r', array ('log'))
  ->condition ('update_hash', $update_hash, '=')
  ->range (0, 1)
  ->execute();  

  $row = $result->fetchAssoc ();
  if ($row === FALSE) {
    return t('Log not available.');
  }
  
	return $row['log'];
}

/**
 * Retrieves the log of a specific registered script.
 *
 * @param string $update_hash	The has of the registered script.
 * @return string				The result as string.
 */
function _updatescripts_get_script_logs () {

  $result = db_select ('updatescripts_register', 'r')
  ->fields ('r', array ('log'))
  ->orderBy ('register_time', 'ASC')
  ->execute();

  $logs = array ();

  While ($row = $result->fetchAssoc ()) {
    if ($row !== FALSE) {
      $logs[] = $row['log'];
    }
  }
  
	return $logs;
}

/**
 * Detects and retrieves the next best number for a new updatescript.
 *
 * @return integer	The number for a new updatescript.
 */
function _updatescripts_detect_next_best_script_number () {
  
  $file           = null;
  $found_scripts  = file_scan_directory(_updatescripts_get_scripts_path (), '/.*\.php$/');  
  $best_number    = 0;
  
    foreach ($found_scripts as $file) {
      
      $version = intval ($file->filename);
      
      if ($version > $best_number) {
      
        $best_number = $version + UPDATESCRIPTS_NEXT_BEST_NUMBER_STEP_SIZE;
      }
  }
  
  if (UPDATESCRIPTS_NEXT_BEST_NUMBER_STEP_SIZE > $best_number) {
  
    $best_number = UPDATESCRIPTS_NEXT_BEST_NUMBER_STEP_SIZE;
  }
  
  return str_pad($best_number, UPDATESCRIPTS_NEXT_BEST_NUMBER_DIGITS ,'0', STR_PAD_LEFT);;
}
