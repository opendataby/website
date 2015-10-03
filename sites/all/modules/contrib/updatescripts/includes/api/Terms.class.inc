<?php
/**
 * @copyright 	2012 (c) By Bright Solutions GmbH
 * @author		  Marc Sven Kleinboehl
 *
 * A class which can create hierarchical term structures.
 */

namespace UpdateScriptAPI;

class Terms {
  
  /**
   * Creates a set of terms in a specific vocabulary.
   *
   * @param  string  $vocabulary				The machine name of the destination vocabulary.
   * @param 	array	 $termDefinitions	 	An array of (nested) term definitions.
   * @return  boolean										TRUE on success.
   */
  public static function __invoke ($vocabularyName, array $termDefinitions) {
    
    $vocabulary = taxonomy_vocabulary_machine_name_load($vocabularyName);
    if ($vocabulary === FALSE) {
      return FALSE;
    }
    
    self::scanRecursive ($vocabulary->vid, $termDefinitions);
    
    return TRUE;
  }
  
  /**
   * Creates a single term.
   *
   * @param integer $vid			The database ID of the destination vocabulary.
   * @param string	$name			The name of the new term.-
   * @param array   $fields		A set of term fields. 
   * @param integer $parent		An optional database ID of potential parent term.
   * @return  boolean					TRUE on success.
   */
  private static function createTerm ($vid, $name, array $fields, $parent) {#
    
    $term = (object)array (
      'name'   => $name,
      'vid'    => $vid,
      'parent' => $parent
    );
    
    self:: createFields ($term, $fields);
    taxonomy_term_save($term);

    return isset ($term->tid) && $term->tid > 0 ? $term->tid : FALSE;
  }
  
  /**
   * Scans a definitions array recursively.
   *
   * @param integer $vid			The database ID of the destination vocabulary.
   * @param array	  $input	 	An array of (nested) term definitions.
   */
  private static function scanRecursive ($vid, array $input, $tid = 0) {
 
    foreach ($input as $inputLevel) {
 
      $fields   = isset ($inputLevel['fields']) ? $inputLevel['fields'] : array ();
      $childs   = isset ($inputLevel['childs']) ? $inputLevel['childs'] : array ();
      $name     = isset ($inputLevel['name']) ? $inputLevel['name'] : 'unknown';
      $new_tid  = self::createTerm ($vid, $name, $fields, $tid);
      
      if ($new_tid !== FALSE) {
        self::scanRecursive ($vid, $childs, $new_tid);
      }
    }
    
    return;
  }
  
  /**
   * Adds field values to a term.
   *
   * @param object_ref			A term object reference.
   * @param  array						An array of natural field/value descriptions.
   */
  private static function createFields (&$term, array $fields) {
 
    $term = (array)$term;
    $term = array_merge ($term, $fields); 
    $term = (object)$term;
    
    return;
  }
}

