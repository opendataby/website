<?php
 /**
 * @file
 * Definition of ajax_comments_handler_field_list_comments. 
 * TODO: Comments per page as setting
 * TODO: Flat or nested as option
 */

/**
 * Handler for showing an ajaxified list of comments.
 */
class ajax_comments_handler_field_list_comments extends views_handler_field_entity {

  function option_definition() {
    $options = parent::option_definition();
    $options['ajax_comments_display_add_comment_form'] = array('default' => FALSE, 'bool' => TRUE);
    return $options;
  }
  
  function options_form(&$form, &$form_state) {
    $form['ajax_comments_display_add_comment_form'] = array(
      '#title' => t('Show Add Comment form'),
      '#description' => t("Enable to display the Add Comment form below the list of comments."),
      '#type' => 'checkbox', 
      '#default_value' => $this->options['ajax_comments_display_add_comment_form'],
    );
    parent::options_form($form, $form_state);
  }
  

  /**
   * Render the list of comments
   * modified to add the ajax_comments wrapper and the add comment form option.
   */
  function render($values) {
    if (user_access('post comments') && $node = $this->get_value($values)) {
      // Init with dummy Comment. For explanation look at ajax_comments_process_node().
      $result = array('comments' => array('dummyComment' => array(
        '#prefix' => '<div class="ajax-comment-wrapper ajax-comment-dummy-comment" style="display:none">',
        '#type' => 'item',
        '#markup' => '',
        '#suffix' => '</div>',
      )));

      // Only attempt to render comments if the node has visible comments.
      // Unpublished comments are not included in $node->comment_count, so show
      // comments unconditionally if the user is an administrator.
      if (($node->comment_count && user_access('access comments')) ||
        user_access('administer comments')) {
        $mode = variable_get('comment_default_mode_' . $node->type, COMMENT_MODE_THREADED);
        $comments_per_page = variable_get('comment_default_per_page_' . $node->type, 150);
        if ($cids = $this->comment_get_thread($node, $mode, $comments_per_page)) {
          $comments = comment_load_multiple($cids);
          comment_prepare_thread($comments);
          $build = comment_view_multiple($comments, $node);
          // TODO: There seems to be a problem with nested pagers :/
          //$build['pager']['#theme'] = 'pager';

          $result['comments'] += $build;
        }
      }

      // Append comment form if needed.
      if (user_access('post comments') && $node->comment == COMMENT_NODE_OPEN 
          && (variable_get('comment_form_location_' . $node->type, COMMENT_FORM_BELOW) == COMMENT_FORM_BELOW 
          && $this->options['ajax_comments_display_add_comment_form'])) {
        $result['comment_form'] = drupal_get_form("comment_node_{$node->type}_form", (object) array('nid' => $node->nid));
      }

      // Theme comments
      $result += array(
          '#theme' => 'comment_wrapper__node_' . $node->type, 
          '#node' => $node, 
          'comments' => array(),
          'comment_form' => array(),
      );
      return $result;
    }
  }

  /* 
   * We need to fetch this in our own method since Drupal doesn't seeem
   * to support nested pagers 
   */
  function comment_get_thread($node, $mode, $comments_per_page = 150) {
    $query = db_select('comment', 'c');
    $query->addField('c', 'cid');
    $query
      ->condition('c.nid', $node->nid)
      ->addTag('node_access')
      ->addTag('comment_filter')
      ->addMetaData('node', $node);
      //->limit(0,$comments_per_page);
    if (!user_access('administer comments')) {
      $query->condition('c.status', COMMENT_PUBLISHED);
    }
    if ($mode === COMMENT_MODE_FLAT) {
      $query->orderBy('c.cid', 'ASC');
    }
    

    $cids = $query->execute()->fetchCol();

    return $cids;
  }
}
