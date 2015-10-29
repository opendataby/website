<?php
/**
 * @copyright 	2012 (c) By Bright Solutions GmbH
 * @author		Marc Sven Kleinboehl
 *
 * Contains some API host methods for the update scripts. 
 */

abstract class UpdateScriptAPI {

  protected abstract function log ($message);

 /**
  * Installs modules.
  *
  * @param array $modules	An array of module names.
  */
  protected function setupModules (array $modules) {

    foreach ($modules as $module) {
      if (! module_enable (array($module))) {
        $this->log (t('Error while installing module @module.', array ('@module'=>$module)));
      }
    }

    return;
  }
   
 /**
  * Uninstalls modules.
  *
  * @param array $modules	An array of module names.
  */
  protected function unsetupModules (array $modules) {
     
    foreach ($modules as $module) {
      if (! module_disable (array($module))) {
        $this->log (t('Error while uninstalling module @module.', array ('@module'=>$module)));
      }
    }
     
    return;
  }
   
  /**
   * Installs themes.
   * @param array $themes	An array of theme names.
   */
  protected function setupThemes (array $themes) {
     
    foreach ($themes as $theme) {
      theme_enable (array($theme));
    }

    return;
  }

   
 /**
  * Uninstalls themes.
  *
  * @param array $themes	An array of theme names.
  */
  protected function unsetupThemes (array $modules) {
     
    foreach ($themes as $theme) {
      theme_disable (array($theme));
    }
     
    return;
  }
   
 /**
  * Set the active theme.
  *
  * @param string $themeName The name of the theme.
  * @param boolean $adminTheme (Optional)TRUE, if you want to set the admin theme.
  */
  protected function setDefaultTheme ($themeName, $adminTheme = FALSE) {

    if ($adminTheme) {
      variable_set('admin_theme', $themeName);
    }else{
      variable_set('theme_default', $themeName);
    }
    
    return;
  }
 

 /**
  * Executes a drush command.
  *
  * @param string $commandLine	The command to execute.
  */
  protected function drush ($commandLine) {
 
    if (function_exists('drush_shell_exec')) {      
      $result = drush_shell_exec('drush -y -r "' . getcwd() . '" ' . $commandLine);
      $log    = implode("\n", drush_shell_exec_output());      
    }else{
      $result = $this->drushShellExec($commandLine);
      $log    = $result;
    }
   
    if ($result === FALSE){
      $this->log (t('Can not execute drush command line.'));
    }else{
      $this->log ($log);
    }   
   
    return;
  }
  
  /**
   * A none-CLI drush_shell_exec function. 
   *
   * @param string $commandLine  The command to execute.   
   */
  private function drushShellExec($commandLine) {
          
    $handle = @popen('drush -y -r "' . getcwd() . '" ' . $commandLine, 'r'); 
    if (! $handle) {
      return FALSE;
    }
 
    $buffer = '';
 
    while (!feof($handle)) { 
      $buffer .= fread($handle, 1024); 
    } 
 
    pclose($handle);
      
    return $buffer; 
  }
   
  /**
   * Translates a string which was defined in a t-function.
   *
   * @param string 		$target_language_prefix
	 * @param string 		$source_expression
	 * @param string 		$translated_expresion
	 * @return boolean  TRUE on success
   */
  public function setLanguageWording ($targetLanguagePrefix, $sourceExpression, $translatedExpression) {
    
    $results = db_query ('SELECT s.source, s.location, s.lid, s.textgroup, t.translation, t.language FROM {locales_source} s LEFT JOIN {locales_target} t ON s.lid = t.lid WHERE s.source=:source', array (
      ':source' => $sourceExpression
    ));
 
    foreach($results as $row) {

      if (!empty($row->translation)) {
        db_query("UPDATE {locales_target} SET translation =:trans WHERE lid=:lid AND language=:lang", array(
            ':trans'  => $translatedExpression, 
            ':lid'    => $row->lid, 
            ':lang'   => $targetLanguagePrefix
          )
        );
      } else {
        db_query("INSERT INTO {locales_target} (lid, translation, language) VALUES (:lid, :trans, :lang)", array(
            ':trans'  => $translatedExpression, 
            ':lid'    => $row->lid, 
            ':lang'   => $targetLanguagePrefix
          )
        );
      }
    }
    
    return TRUE;
  }
  
  /**
   * Creates a set of new taxonomy terms on a destinated vocabulary.
   * It supports hierarchical terminologies.
   *
   * @param 	string			$vocabularyName			The destination vocabulary.
   * @param		array				$termDefinitions		This array describes the set of new terms.
   * 																					I.ex.:
   * 																					array (
   * 																						array('name'=>'this is term A'),
   * 																						array(
   * 																							'name'		=>'this is term B',
   * 																							'fields'	=>array (
   * 																								'description' => 'This is a description',
   * 																								'field_term_age' => array (
   * 																									LANGUAGE_NONE => array (
   * 																										array ('value' => '55 years')
   * 																									)
   * 																								)
   * 																							),
   * 																							'clients' => array (
   *    																						array('name'=>'this is term B-2'),
   * 																							)
   *																						),		
   * 																					)
   */
  public function createVocabularyTerms ($vocabularyName, array $termDefinitions) {
    
    module_load_include ('inc', 'updatescripts', 'includes/api/Terms.class');
    
    return UpdateScriptAPI\Terms($vocabularyName, $termDefinitions);
  }
}

