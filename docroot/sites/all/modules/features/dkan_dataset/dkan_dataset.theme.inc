<?php

/**
 * @file
 * Theme functions for datasets.
 */

/**
 * Implements hook_theme().
 */
function dkan_dataset_theme() {
  $theme = array(
    'dkan_dataset_resource_view' => array(
      'variables' => array('node' => NULL),
    ),
    'dkan_dataset_release_date_view' => array(
      'variables' => array('node' => NULL),
    ),
    'dkan_dataset_modified_date_view' => array(
      'variables' => array('node' => NULL),
    ),
    'dkan_dataset_identifier_view' => array(
      'variables' => array('node' => NULL),
    ),
    'dkan_dataset_resource_teaser_view' => array(
      'variables' => array('node' => NULL),
    ),
    'dkan_dataset_teaser_link' => array(
      'variables' => array(
        'title' => NULL,
        'nid' => NULL,
        'desc' => NULL,
        'format' => NULL,
        'type' => NULL,
      ),
    ),
    'dkan_dataset_teaser_preview_link' => array(
      'variables' => array('node' => NULL),
    ),
    'dkan_dataset_preview_settings_external_table_form' => array(
      'render element' => 'form',
      'file' => 'dkan_dataset.admin.inc',
    ),
  );
  return $theme;
}
/**
 * Outputs the identifier content.
 */
function theme_dkan_dataset_identifier_view($vars) {
  return '<div property="dcterms:identifier" class="field-name-field-identifier">' . $vars['node']->uuid . '</div>';
}

/**
 * Outputs the modified date content.
 */
function theme_dkan_dataset_modified_date_view($vars) {
  return '<div property="dcterms:modified" class="field-name-field-modified-date">' . date('Y-m-d', $vars['node']->changed) . '</div>';
}

/**
 * Outputs the release date content.
 */
function theme_dkan_dataset_release_date_view($vars) {
  return '<div property="dcterms:issued" class="field-name-field-release-date">' . date('Y-m-d', $vars['node']->created) . '</div>';
}

/**
 * Output the resource into the node content.
 */
function theme_dkan_dataset_resource_view($vars) {
  $output = '<h4>' . t('Data and Resources') . '</h4>';
  $node = entity_metadata_wrapper('node', $vars['node']);
  $nodes = $node->field_resources->value();
  $links = array();
  $output .= '<div property="dcat:distribution">';

  if (isset($nodes)) {
    $file_count = 0;
    foreach ($nodes as $node) {
      // Node could be empty if it has been deleted.
      if (!$node || !node_access('view', $node)) {
        continue;
      }
      $node_wrapper = entity_metadata_wrapper('node', $node);
      $body = $node_wrapper->body->value();
      $term = '';
      if (isset($body['safe_value'])) {
        $desc = '<p class="description">' . dkan_dataset_text_trim($body['safe_value'], 80) . '</p>';
      }
      else {
        $desc = '<p class="description"></p>';
      }
      $format = t("data");
      if (isset($node->field_format) && $node->field_format && $node_wrapper->field_format->value()) {
        $format = $node_wrapper->field_format->value()->name;
      }
      if (isset($node->field_upload[LANGUAGE_NONE])) {
        $type = 'file_upload';
        $file_count++;
      }
      elseif (isset($node->field_link_remote_file[LANGUAGE_NONE])) {
        $type = 'link_remote_file';
      }
      else {
        $type = 'link_api';
      }
      $teaser_link = theme('dkan_dataset_teaser_preview_link', array('node' => $node, 'type' => $type));
      $links[] = theme('dkan_dataset_teaser_link', array(
        'link' => $teaser_link, 'title' => $node->title, 'nid' => $node->nid, 'desc' => $desc,
        'format' => $format, 'type' => $type, 'node' => $node,
      ));
    }
    if ($file_count > 1) {
      $download_all = '<div property="dcat:Distribution"><span class="links">';
      $download_all .= l('Download All <i class="fa fa-download"></i>', 'node/' . $vars['node']->nid . '/dataset/download', array(
        'html' => TRUE,
        'attributes' => array(
          'class' => array('btn', 'btn-primary')
        )
      ));
      $download_all .= '</span></div>';
      $links[] = $download_all;
    }
    $output .= theme('item_list', array('items' => $links, 'attributes' => array('class' => array('resource-list'))));
    // Close first dcat declaration.
    $output .= '</div>';
  }
  return $output;
}

/**
 * Provides direct link url for resource.
 */
function dkan_dataset_resource_direct_link($node) {
  if (isset($node->field_upload[LANGUAGE_NONE])) {
    $url = file_create_url($node->field_upload[LANGUAGE_NONE][0]['uri']);
  }
  elseif (isset($node->field_link_remote_file[LANGUAGE_NONE])) {
    $url = $node->field_link_remote_file[LANGUAGE_NONE][0]['uri'];
  }
  elseif (isset($node->field_link_api[LANGUAGE_NONE])) {
    $url = $node->field_link_api[LANGUAGE_NONE][0]['url'];
  }
  else {
    $url = '';
  }
  return $url;
}


/**
 * Theme function for DKAN Dataset teaser link.
 */
function theme_dkan_dataset_teaser_link($vars) {

  $desc = $vars['desc'];
  $output = '<div property="dcat:Distribution">';
  $format = '<span data-toggle="tooltip" data-placement="top" data-original-title="' . $vars['format'] . '" class="format-label" property="dc:format" data-format="' . $vars['format'] . '">' . $vars['format'] . '</span>';

  $title = l($vars['title'] . $format, 'node/' . $vars['nid'], array(
    'html' => TRUE,
    'attributes' => array(
      'class' => array('heading'),
      'title' => $vars['title'],
      'property' => 'dcat:accessURL',
    ))
  );
  $output .= $title . $desc . '<span class="links">' . $vars['link'] . '</span></div>';

  return $output;
}


/**
 * Theme function to create "open with" version of teaser links on Datasets.
 */
function theme_dkan_dataset_teaser_preview_link($vars) {
  $preview_link = $direct_link = '';
  $resource = $vars['node'];
  $url = dkan_dataset_resource_direct_link($resource);
  if ($vars['type'] == 'file_upload' || $vars['type'] == 'link_remote_file') {
    $direct_link = l(
      '<i class="fa fa-download"><span> '. t('Download') . '</span></i>',
      $url,
      array(
        'html' => TRUE,
        'attributes' => array(
          'class' => array('btn', 'btn-primary', 'data-link'),
        ),
      )
    );
  }
  else {
    $direct_link = l(
      '<i class="fa fa-external-link"><span> ' . t('Go to resource') . '</i>',
      $url,
      array(
        'html' => TRUE,
        'attributes' => array(
          'class' => array('btn', 'btn-primary', 'data-link'),
        ),
      )
    );
  }
  $node = $vars['node'];
  $previews = dkan_dataset_teaser_external_previews_for_resource($node);
  if (count($previews)) {
    // If multiple previews, use the "open with" format
    if (count($previews) > 1) {
      $preview_link =
      '<div class="btn-group">
        <button class="btn btn-primary" data-toggle="dropdown">' . t('Open With') . '</button>
          <button class="btn btn-primary" data-toggle="dropdown">
            <span class="caret"></span><span class="sr-only">Toggle dropdown</span>
          </button>
        <ul class="dropdown-menu">
      ';
      foreach ($previews as $provider => $preview) {
        $preview_link .=
          '<li class="' . $provider . ' ">
            <a href="' . $preview['url'] . '" title="">
              <span> ' . $preview['name'] . '</span>
            </a>
          </li>';
      }
      $preview_link .= '</ul></div>';
    }
    // Otherwise use single button
    else {
      $machine_name = current(array_keys($previews));
      $preview = $previews[$machine_name];
      if ($machine_name == 'dkan') {
        $button_text = t('Preview');
      }
      else {
        $button_text = $preview['name'];
      }
      $preview_link = l(
        '<i class="fa fa-bar-chart"><span> ' . $button_text . '</span></i>',
        $preview['url'],
        array(
          'html' => TRUE,
          'attributes' => array(
            'class' => array('btn', 'btn-primary'),
          ),
        )
      );
    }
  }
  $link = $preview_link . $direct_link;
  return $link;

}

/**
 * Output the resource into the node content.
 */
function theme_dkan_dataset_resource_teaser_view($vars) {
  if ($vars['node']->type == 'dataset') {
    $node = entity_metadata_wrapper('node', $vars['node']);
    $nodes = $node->field_resources->value();
  }
  else {
    $nodes = array($vars['node']);
  }
  $links = array();
  if (isset($nodes)) {
    // Data links for generate grouping resources link.
    $links_data = array();
    foreach ($nodes as $node) {
      $node_wrapper = entity_metadata_wrapper('node', $node);
      $name = dkan_dataset_get_resource_format($node);
      $term = '';

      // Check node is published.
      if (isset($node->status) && $node->status) {
        if (!isset($links_data[$name])) {
          $links_data[$name] = array(
            'term_name' => $name,
            'count' => 1,
            'url' => 'node/' . $vars['node']->nid,
            'link' => array(
              'attributes' => array(
                'class' => array('label'),
                'title' => t('Resources') . ': ' . $vars['node']->title,
                'data-format' => $name,
              ),
            ),
          );
        }
        else {
          $links_data[$name]['count'] = $links_data[$name]['count'] + 1;
        }
      }
    }
    foreach ($links_data as $term_name => $link) {
      $links[] = '<span class="count-resource">' . $link['count'] . 'x</span>' . l($term_name, $link['url'], $link['link']);
    }
    $output = theme('item_list', array('items' => $links, 'attributes' => array('class' => array('resource-list'))));
  }
  return $output;
}

/**
 * Theme function for previews form table
 */
function theme_dkan_dataset_preview_settings_external_table_form(&$vars) {
  $form = $vars['form'];
  $rows = $form['rows'];
  $header =
  $content = array(
      '#theme' => 'table',
      '#header' => $form['#header'],
      '#rows' => array(),
    );
  // Traverse each row.  @see element_chidren().
  foreach (element_children($rows) as $row_index) {
    $row = array();
    // Traverse each column in the row.  @see element_children().
    foreach (element_children($rows[$row_index]) as $col_index) {
      // Render the column form element.
      $row[] = array('data' => drupal_render($rows[$row_index][$col_index]));
    }
    // Add the row to the table.
    $content['#rows'][] = $row;
  }

  // Redner the table and return.
  return drupal_render($content);

}
