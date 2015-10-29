<?php
/*
 * @copyright 	2012 (c) By Bright Solutions GmbH
 * @author		Marc Sven Kleinboehl
 *
 * This include file contains all the stuff we could need in other include files.
 */

/**
 * A config getter procedure.
 *
 * @param string $group						The config group ID.
 * @param string $key							The config key.
 * @param string $default_value		The default value will returned if not succeed.
 */
function _updatescripts_get_config_value ($group, $key, $default_value = FALSE) {
  
  $config = variable_get ('updatescripts', array ());
 
  if (! isset ($config[$group][$key])) {
    return $default_value;
  }
 
  return $config[$group][$key];
}