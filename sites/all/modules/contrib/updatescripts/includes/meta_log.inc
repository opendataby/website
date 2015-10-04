<?php
/**
 * @copyright 	2012 (c) By Bright Solutions GmbH
 * @author		Marc Sven Kleinboehl
 *
 */

/**
 * The page callback of the meta-log menu link.
 * It renders just a log file.
 */
function _updatescripts_meta_log () {
  
  header ('Content-Type: text/plain');  
  header('Content-Disposition: attachment; filename="metalog.txt"');
  
  print t('Meta log file.') . "\n";
  print "-------------------------------------------------\n\n";
  
  module_load_include ('inc', 'updatescripts', 'includes/register');
  
  $logs = _updatescripts_get_script_logs ();
  
  foreach ($logs as $log) {
    print $log;
  }
  
  return NULL;
}
 