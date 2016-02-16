<?php
/**
 * @file
 * NoDependencyIterator plugin class definition.
 */

/**
 * Iterator class for when there are no dependencies to iterate through.
 */
class NoDependencyIterator extends DeployIterator {

  /**
   * {@inheritdoc}
   */
  public function hasChildren() {
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function getChildrenEntities() {
    return array();
  }

  /**
   * {@inheritdoc}
   */
  public function getChildren() {
    return new EntityDependencyIterator(array(), $this);
  }
}
