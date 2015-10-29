<?php
/**
 * @copyright 	2012 (c) By Bright Solutions GmbH
 * @author		Marc Sven Kleinboehl
 * 
 * The update script entity represents a processing update script.
 */

require_once drupal_get_path ('module', 'updatescripts') . '/includes/UpdatescriptAPI.class.inc';

class UpdateScriptEntity extends UpdateScriptAPI {
  
  private $description;
  private $author;
  private $finished;
  private $log;
  private $filepath;
  private $oldLog;
  
  /**
   * PLEASE, use this factory method, for creating an instance of this class.
   *
   * @param string $filename	The filename of the update script file.
   * @return object						Returns an object of this class.
   */
  public static function load ($filename) {
    
    $result = db_select ('updatescripts_register', 'r')
    ->fields ('r', array ('log', 'process_times'))
    ->condition ('update_hash', md5 ($filename), '=')
    ->range(0,1)
    ->execute();
    
    $updateData = $result->fetchObject ();
    if (! $updateData) {
      return new UpdatescriptEntity ($filename);
    }
    
    return new UpdatescriptEntity ($filename, $updateData);
  }
  
  /**
   * Ctor
   *
   * @param string $filename		The filename of the update script file.
   * @param object $updateData	(optional) This object will used, only on re-executing of an update script. It contains the data of the registered script.
   */
  public function __construct ($filename, $updateData = null) {

    $this->setAuthor (t('Unknown'));
    $this->setDescription (t('No description'));       
       
    $this->update = ! empty ($updateData);

    if ($this->update) {
      $this->oldLog       = $updateData->log;
      $this->processTimes = $updateData->process_times;
    }else{
      $this->processTimes = 0;
    }

    $this->filepath = $filename;
    $this->finished = false;
    
    $this->scriptEval ($filename);
    
    return;
  }
  
  /**
   * Executes a script and logs the output of the runtime.
   *
   * @param string $filename	The full filename of the script.
   */
  private function scriptEval ($filename) {

    ob_start();
      include DRUPAL_ROOT . '/' . $filename;
      $output = ob_get_contents();
    ob_end_clean();
    
    $this->log ($output);
    
    return;
  }
  
  /**
   * It is a host-method, for using inside an updatescript.
   * Sets the author of the update script.
   *
   * @param string $author	The name of the author of the update script.
   */
  private function setAuthor ($author) {

    $this->author = $author;
    
    return;
  }
  
  /**
   * It is a host-method, for using inside an updatescript.
   * Sets the description of the script.
   *
   * @param	string	$description	The description text which describes what the update script will do.
   */
  private function setDescription ($description) {
  
  	$this->description = $description;
  
  	return;
  }
  
  /**
   * It is a host-method, for using inside an updatescript.
   * Adds a message to the script log.
   *
   * @param string $logMessage	The message text.	
   */
  protected function log ($logMessage) {

  	$this->log .= $logMessage . "\n"; 
  	
  	module_invoke_all('updatescripts_process_log', $logMessage);
  
  	return;
  }
  
  /**
   * It is a host-method, for using inside an update script.
   * Use it to finish processing the respective update script.
   * Otherwise, the script will run again and again, and again. Perfekt for batch updating.
   */
  private function finished () {
  
  	$this->finished = true;
  
  	return;
  }
  
  /**
   * Saves the state of the entity into the database register for updatescripts.
   * Use this function after processing a single updatescript.
   */
  public function saveEntity () {
 
    $this->log = t('Filepath: @filepath', array ('@filepath'=>$this->filepath)) . "\n" .
                 t('Process data: @date', array ('@date'=>format_date(time()))) . "\n" .
                 t('Author: @author', array ('@author'=>$this->author)) . "\n" .
                 t('Process times: @times', array ('@times'=>$this->processTimes)) . "\n" .
                 t('Description:') . "\n" .
                 $this->description . "\n" .
                 t('Message:') . "\n" .
                 $this->log . "\n\n\n";
    
    if ($this->update) {
      
      db_update ('updatescripts_register')
      ->fields (array (
                'processed'       => (integer)$this->finished,
                'process_times'	  => $this->processTimes + 1,
                'log'			        => $this->oldLog . $this->log
      ))
      ->condition ('update_hash', md5($this->filepath), '=')
      ->execute ();
      
      return;
    }
    
    db_insert ('updatescripts_register')
    ->fields (array(
              'update_hash'     => md5($this->filepath),
              'script'			    => basename ($this->filepath),
              'register_time'	  => time(),
              'processed'       => (integer)$this->finished,
              'process_times'	  => 1,
              'log'	            => $this->log
    ))
    ->execute ();
    
    module_invoke_all('updatescripts_process_closed', $this->filepath, $this->update, $this->author, $this->description);
    
    return;
  }
}
