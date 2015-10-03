<?php
/*
 * @copyright 	2012 (c) By Bright Solutions GmbH
 * @author		Marc Sven Kleinboehl
 *
 * This include file contains all of the functions for configuration of the updatescript processor.
 */

/*
 * The form callback which defines the form for configurating the updatescript processor.
 */
function _updatescripts_configuration_form ($form_state) {
  
  $settings = variable_get ('updatescripts', array ());
  
  $form['updatescripts'] = array (
    '#type'         => 'fieldset',
    '#title'	      => t('Settings'),
    '#tree'		      => TRUE,
    '#description'	=> t('This settings form contains all the config forms of the submodules of the updatescript processor.')
  );
  
  $form['updatescripts']['general'] = array (  
    '#type'         => 'fieldset',
    '#title'	      => t('Updatescripts processor'),
    '#tree'		      => TRUE,
  );
  
  $form['updatescripts']['general']['overlay_button'] = array (  
    '#type'           => 'checkbox',
    '#default_value'	=> _updatescripts_get_config_value ('general', 'overlay_button'),
    '#title'					=> t('Overlay button'),
    '#description'		=> t('Shows an updatescript overlay button ad the left middle side of each page.')
  );
  
  module_invoke_all('updatescripts_config_form', $form, $form_state, $settings);
  
  return system_settings_form ($form);
}

