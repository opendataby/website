<?php
/*
 * @copyright 	2012 (c) By Bright Solutions GmbH
 * @author			Sebastian Kauschke
 *
 * @file 
 * 
 * Allows poor windows users to execute the updatescript processing via drush.
 * 
 * For more informations, run: drush runbsu _h
 */

// Declaring the commandline arguments.
define ('UPDATESCRIPTS_CMD_ARG_SPECIFIC_FILE', '_d');
define ('UPDATESCRIPTS_CMD_ARG_SILENT', '_s');
define ('UPDATESCRIPTS_CMD_ARG_HELP', '_h');


/*
 * Shows drush commands to drush.
 * @return array	An array which contains informations about the drush command items.
 */
function updatescripts_drush_command() {
  $items = array();

  $items['updatescripts'] = array(
      'description' => 'Run BS updatescripts',
      'aliases'     => array('runbsu'),
  );
  
  $items['batch-process-updatescripts'] = array(
      'description' => 'Run BS updatescripts in a batch process.',
      'aliases'     => array('batchbsu'),
  );
  
  $items['unprocessed-updatescripts'] = array(
      'description' => 'Shows all unprocessed updatescripts.',
      'aliases'     => array('bsuup'),
  );
  
  $items['create-updatescript'] = array(
      'description' => 'Creates a new updatescript.',
      'aliases'     => array('crusp'),
  );

  return $items;
}

/**
 * Help Information for drush commands
 * 
 * @param string $section 	Specifies the help document section.
 */
function updatescripts_drush_help($section) {
 
  switch ($section) {
    case 'drush:updatescripts':
      return file_get_contents(
        __DIR__ . '/help/drush_updatescripts.txt'
      );
      
    case 'drush:create-updatescript':
      return file_get_contents(
        __DIR__ . '/help/drush_create_updatescript.txt'
      );
      
    case 'drush:unprocessed-updatescripts':
      return file_get_contents(
        __DIR__ . '/help/drush_unprocessed_updatescripts.txt'
      );
      
    case 'drush:batch-process-updatescripts':
      return file_get_contents(
        __DIR__ . '/help/drush_batch-process_updatescripts.txt'
      );
  }
  
  return;
}

function drush_updatescripts_batch_process_updatescripts() {
  
  if (strtolower(PHP_OS) != 'linux') {
    drush_print('This function can not run on a none-linux OS.');
    return;
  }
 
  module_load_include('inc', 'updatescripts', 'includes/register');
  
  $updatescripts = _updatescripts_detect_unprocessed_scripts ();
 
  if (empty($updatescripts)) {
    return;
  }
  
  $next_script = reset($updatescripts);
  
  drush_print('Running scripts in background.');
  
  
  module_load_include ('inc', 'updatescripts', 'includes/processor_remote');
  
  _updatescripts_run_script (
    $next_script
  );
 
  drush_shell_exec('nohup drush batchbsu >nohup.out 2>&1 &');
  
  return;
}

/**
 * Command callback.
 * Lists all unprocessed updatescripts.
 */
function drush_updatescripts_unprocessed_updatescripts() {
  
  module_load_include('inc', 'updatescripts', 'includes/register');
  
  $updatescripts = _updatescripts_detect_unprocessed_scripts ();
 
  if (empty($updatescripts)) {
    drush_print('0 unprocessed scripts found.');
    return;
  }
  
  foreach($updatescripts as $uri) {
    drush_print(basename($uri));
  }
  
  drush_print(count($updatescripts) . ' unprocessed scripts found.');
  
  return;
}

/**
 * Command callback.
 * Creates an updatescript.
 *
 * @param string $author    The author of the new updatescript.
 * @param string $usage     The usage description of the new updatescript.
 * @param string $code      (optional) The code (one line) to process with the new updatescript.
 */
function drush_updatescripts_create_updatescript($author, $usage = NULL, $code = NULL) {
       
  if ($author === NULL) {
    drush_print('Missing author argument.');
    return;
  }
         
  if ($usage === NULL) {
    drush_print('Missing usage argument.');
    return;
  }
  
  if ($code === NULL) {
    $code = '// Put your updatescript code here!';
  }
     
  drupal_load('module', 'updatescripts');
  module_load_include('inc', 'updatescripts', 'includes/register');
 
  $script_file = _updatescripts_detect_next_best_script_number () . 
  '-' . substr(strtolower(
      preg_replace(
        '@[^a-zA-Z0-9_-]+@', 
        '-', 
        $usage 
      )
    ),
    0,
    32
  ) . '.php';
 
  if (@file_put_contents(
    DRUPAL_ROOT . '/' . _updatescripts_get_scripts_path() . '/' . $script_file,
    "<?php\n" .
    "/**\n * @file   " . $script_file . "\n * @author " . $author . "\n*/\n\n" .   
    "\$this->setAuthor('" . $author . "');\n" . 
    "\$this->setDescription('" . $usage . "');\n\n" .
    $code . "\n\n".  
    "\$this->finished();\n"    
  ) === FALSE) {
    drush_set_error(
      'Error creating updatescript.', 
      'Couldn\'t create the updatescript. Check the permissions of the updatescripts folder.'
    );
    return;
  }
  
  drush_print('Created updatescript successfuly.');
 
  return;
}


/*
 * drush updatescripts runs the updatescripts.
 */
function drush_updatescripts () {
 
  $commandline_arguments = _updatescripts_get_arguments ();

  // Was the help document ordered?
  if ($commandline_arguments[UPDATESCRIPTS_CMD_ARG_HELP]) {
    _updatescripts_render_help ();
    return; 
  }  
 
  variable_set('site_offline', '1'); // Lock site.
  
  module_load_include ('inc', 'updatescripts', 'includes/processor_remote');
  
  // Normal mode or has a specific file to process?
  if (! isset ($commandline_arguments[UPDATESCRIPTS_CMD_ARG_SPECIFIC_FILE])) {

    $message = _updatescripts_process (drupal_get_private_key ());

  }else{
    _updatescripts_run_script (
      _updatescripts_get_scripts_path() . '/' .
      $commandline_arguments[UPDATESCRIPTS_CMD_ARG_SPECIFIC_FILE]
    );
    $message = 'A single script has been processed.';
  }
  
  variable_set('site_offline', '0'); // Unlock site.

  drush_shell_exec("drush clear-cache all");
  
  if (! $commandline_arguments[UPDATESCRIPTS_CMD_ARG_SILENT]) {
    drush_print($message);
  }
  
  return;
}

/*
 * Retrieves the list of commandline arguments.
 * @return array 	An array which contains the commandline arguments.
 */
function _updatescripts_get_arguments () {
  
  // Set defaults:
  $arguments[UPDATESCRIPTS_CMD_ARG_SILENT] = false;
  $arguments[UPDATESCRIPTS_CMD_ARG_HELP]   = false;
  
  // Fetch argument informations.
  $arguments_amount = $_SERVER['argc'];  
  $arguments_values = array ();
  	
  // No arguments? Nothing to do!
  if ($arguments_amount == 0) {
    return $arguments_values; 
  }
  
  $i = 0;
	
  while ($i < $arguments_amount) {
 
    $current_argument = $_SERVER['argv'][$i];
    
    switch ($current_argument) {
      case UPDATESCRIPTS_CMD_ARG_SPECIFIC_FILE:        
        $i++;
        $arguments[$current_argument] = $_SERVER['argv'][$i];
        break;

      case UPDATESCRIPTS_CMD_ARG_HELP:
      case UPDATESCRIPTS_CMD_ARG_SILENT:
        $arguments[$current_argument] = true;
        break;
        
      // EXTEND HERE FOR FUTURE COMMANDLINE ARGUMENT EXTENDING!!!
    }
    
    $i++;
  }
  
  return $arguments;
}

/*
 * Renders a help document out to the console.
 */
function _updatescripts_render_help () {
  
  drush_print(file_get_contents(
        __DIR__ . '/help/drush_updatescripts.txt'
  ));
   
  return;
}
