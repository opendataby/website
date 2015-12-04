<?php
/**
 * @file
 * Style plugin for Semantic Panels.
 */

$plugin = array(
  'title' => t('Semantic'),
  'description' => t('Semantic Style.'),

  // Region.
  'render region' => 'semantic_panels_render_region',
  'settings form' => 'semantic_panels_region_settings_form',

  // Pane.
  'render pane' => 'semantic_panels_render_pane',
  'pane settings form' => 'semantic_panels_pane_settings_form',
  'pane settings form submit' => 'semantic_panels_pane_settings_form_submit',
  'all contexts' => TRUE,
);

/**
 * Region settings form.
 */
function semantic_panels_region_settings_form($settings) {
  $elements = _semantic_panels_get_elements();

  $form = array();

  $form['separator']['active'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add separator'),
    '#description' => t('Enable/disable separator between panes.'),
    '#default_value' => $settings['separator']['active'],
  );
  $form['separator']['element_type'] = array(
    '#title' => t('HTML element'),
    '#type' => 'select',
    '#options' => $elements,
    '#default_value' => $settings['separator']['element_type'],
    '#dependency' => array(
      'edit-settings-separator-active' => array(1),
    ),
    '#tree' => TRUE,
  );
  $form['separator']['show_css'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create a CSS class'),
    '#default_value' => !empty($settings['separator']['show_css']),
    '#dependency' => array(
      'edit-settings-separator-active' => array(TRUE),
    ),
    '#tree' => TRUE,
  );
  $form['separator']['element_class'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS class'),
    '#default_value' => $settings['separator']['element_class'],
    '#dependency' => array(
      'edit-settings-separator-show-css' => array(TRUE),
      'edit-settings-separator-active' => array(TRUE),
    ),
    '#dependency_count' => 2,
    '#tree' => TRUE,
  );

  return $form;
}

/**
 * Render region.
 */
function theme_semantic_panels_render_region($vars) {
  $settings = $vars['settings'];

  $output = '';
  $separator = '';

  if (!empty($settings['separator']) && $settings['separator']['active'] === 1) {
    $attributes = array();

    if (!empty($settings['separator']['show_css']) && !empty($settings['separator']['element_class'])) {
      $attributes['class'] = $settings['separator']['element_class'];
    }

    $separator = "<{$settings['separator']['element_type']}" . drupal_attributes($attributes) . "></{$settings['separator']['element_type']}>";
  }

  $output = implode($separator, $vars['panes']);

  drupal_alter('semantic_panels_region', $output, $vars);

  return $output;
}

function _semantic_panels_form_element(&$form, $settings, $element_key, $element_human_title, $display, $link_elem = TRUE){
  $elements = _semantic_panels_get_elements();

  $form[$element_key] = array(
    '#type' => 'fieldset',
    '#title' => $element_human_title,
    '#collapsible' => TRUE,
    '#tree' => TRUE,
    '#states' => array(
      'visible' => array( '[name="settings[define_custom]"]' => array('checked' => TRUE) ),
    )
  );
  $form[$element_key]['type'] = array(
    '#title' => t('HTML element'),
    '#type' => 'select',
    '#options' => $elements,
    '#default_value' => isset($settings[$element_key]['type']) ? $settings[$element_key]['type'] : '',
  );

  _semantic_panels_form_element_attributes($form,  $settings, $element_key);
  if ($link_elem){
    // TODO: Move link setting to another (new?) module. Set this in pane settings form instead. Allow to set classes and attributes on link?
    _semantic_panels_form_element_link($form, $settings, $element_key, $display);
  }

}

/**
 * Pane settings form.
 */
function semantic_panels_pane_settings_form($settings, $display = NULL) {
  $form = array();

  _semantic_panels_form_element($form, $settings, 'element_title', t('Title'), $display);
  _semantic_panels_form_element($form, $settings, 'element_content', t('Content'), $display);
  _semantic_panels_form_element($form, $settings, 'element_wrapper',t('Wrapper'), $display, FALSE);

  // Default classes.
  $form['add_default_classes'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add default classes'),
    '#default_value' => isset($settings['add_default_classes']) ? $settings['add_default_classes'] : 1,
    '#description' => t('If checked default classes will be added on every element. They will always be added to the wrapper element (to not break contextual links).'),
    '#states' => array(
      'visible' => array( '[name="settings[define_custom]"]' => array('checked' => TRUE) ),
    )
  );

  return $form;
}

function _semantic_panels_context_token_types_map($l){
  return $l->keyword;
}

/**
 * Get "Other Attribute(s)" fieldset
 */
function _semantic_panels_form_element_attributes(&$root_element, $settings, $element_key){
  $attributes = _semantic_panels_get_attributes();
  $element_key_class = '';

  if(is_array($element_key)){
    foreach($element_key as $key){
      $root_element = &$root_element[$key];
      $settings = &$settings[$key];

      $key_class = str_replace('_', '-', $key);
      $element_key_class = ($element_key_class == '') ? $key_class : $element_key_class . '-' . $key_class;
    }
  }else{
    $root_element = &$root_element[$element_key];
    $settings = &$settings[$element_key];
    $element_key_class =  str_replace('_', '-', $element_key);
  }

  $root_element['class_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add CSS class(es)'),
    '#default_value' => isset($settings['class_enable']) ? $settings['class_enable'] : 0,
    '#attributes' => array(
      'class' => array($element_key_class . '-class-enable')
    )
  );
  $root_element['class'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS class(es)'),
    '#default_value' => isset($settings['class']) ? $settings['class'] : '',
    '#states' => array(
      'visible' => array( '.' . $element_key_class . '-class-enable' => array('checked' => TRUE) ),
    )
  );

  $root_element['attributes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Other attribute(s)'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('You can override the available attributes below by setting the <em>semantic_panels_attributes</em> variable.')
  );

  foreach($attributes as $attribute => $attribute_data){

    $root_element['attributes'][$attribute] = array(
      '#type' => 'fieldset',
      '#title' => $attribute,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE
    );

    $root_element['attributes'][$attribute]['enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add <em>@attribute</em> attribute', array('@attribute' => $attribute)),
      '#default_value' => isset($settings['attributes'][$attribute]['enabled']) ? $settings['attributes'][$attribute]['enabled'] : 0,
      '#attributes' => array(
        'class' => array($element_key_class . '-' . $attribute . '-enabled')
      )
    );

    $root_element['attributes'][$attribute]['value'] = array(
      '#type' => 'textfield',
      '#title' => t("<em>@attribute</em> value",array('@attribute' => $attribute)),
      '#default_value' => isset($settings['attributes'][$attribute]['value']) ? $settings['attributes'][$attribute]['value'] : '',
      '#states' => array(
        'visible' => array( '.' . $element_key_class . '-' . $attribute . '-enabled' => array('checked' => TRUE) ),
      ),
      '#description' => t('Value is not required')
    );

  }
}

function _semantic_panels_form_element_link(&$root_element, $settings, $element_key, $display){
  $element_key_class =  str_replace('_', '-', $element_key);

  $root_element[$element_key]['link_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Output as link'),
    '#default_value' => isset($settings[$element_key]['link_enabled']) ? $settings[$element_key]['link_enabled'] : 0,
    '#attributes' => array(
      'class' => array($element_key_class . '-link-enabled')
    )
  );
  $root_element[$element_key]['link'] = array(
    '#type' => 'fieldset',
    '#title' => 'Link options',
    '#states' => array(
      'visible' => array( '.' . $element_key_class . '-link-enabled' => array('checked' => TRUE) ),
    ),
  );
  $root_element[$element_key]['link']['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Link path'),
    '#default_value' => isset($settings[$element_key]['link']['path']) ? $settings[$element_key]['link']['path'] : '',
    '#description' => t('The Drupal path or absolute URL for this link.'),
  );
  if(module_exists('token')){
    $root_element[$element_key]['link']['contexts'] = array(
      '#title' => t('Substitutions'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $tokens_types = isset($display->context) && !empty($display->context) ? array_map('_semantic_panels_context_token_types_map', $display->context) : array();
    $root_element[$element_key]['link']['contexts']['tokens']['help'] = array(
      '#theme' => 'token_tree',
      '#token_types' => $tokens_types,
    );
    if (!empty($tokens_types)){
      $root_element[$element_key]['link']['path']['#description'] .= t(' You may access panel context(s) keywords and other tokens from the <em>Substitutions</em> below.');
    }else{
      $root_element[$element_key]['link']['path']['#description'] .= t(' If you add context(s) to this panel you may access their keywords from the <em>Substitutions</em> below.');    }
  }else{
    $root_element[$element_key]['link']['path']['#description'] .= t(' Enable token module to access panel context(s) keywords and other tokens.');
  }

  _semantic_panels_form_element_attributes($root_element, $settings, array($element_key, 'link'));
}

/**
 * Pane settings form submit handler.
 */
function semantic_panels_pane_settings_form_submit($form, &$settings, $form_state) {

  foreach($settings as &$style_element){
    if(isset($style_element['attributes'])){
      _semantic_panels_attributes_save($style_element);
    }
    if(isset($style_element['link']['attributes'])){
      _semantic_panels_attributes_save($style_element['link']);
    }
  }
}

function _semantic_panels_attributes_save(&$style_element){
  $style_element['attributes_array'] = array();
  foreach($style_element['attributes'] as $machine_name => $attribute_settings){
    if(empty($style_element['attributes'][$machine_name]['enabled'])){
      // Don't save disabled attributes
      unset($style_element['attributes'][$machine_name]);
    }else{
      // Build up $settings['attributes_array'] ready for drupal_attributes with only enabled attributes
      $style_element['attributes_array'][$machine_name] = $style_element['attributes'][$machine_name]['value'];
    }
  }
}

/**
 * Preprocess variables for semantic-panels-pane.tpl.php
 */
function template_preprocess_semantic_panels_pane(&$vars) {
  // Make $vars contain all the stuff that the normal panels_pane has.
  template_preprocess_panels_pane($vars);

  $pane_semantic_settings = $vars['settings'];

  // Title wrapper.
  $vars['title_html'] = '';

  if ($vars['title']) {
    $element_data = array(
      'content' => $vars['title'],
      'default_type' => 'h2',
      'default_classes' => 'pane-title',
      'context' => $vars['display']->context,
    );

    $vars['title_html'] = _semantic_panels_get_html('element_title', $element_data, $pane_semantic_settings);
  }

  // Content wrapper.
  $vars['content_html'] = '';

  if ($vars['content']) {
    $element_data = array(
      'content' => $vars['content'],
      'default_type' => 'div',
      'default_classes' => 'pane-content',
      'context' => $vars['display']->context,
    );

    $vars['content_html'] = _semantic_panels_get_html('element_content', $element_data, $pane_semantic_settings);
  }

  // Full pane wrapper.
  $vars['wrapper_type'] = _semantic_panels_get_type($pane_semantic_settings['element_wrapper']['type']);

  if(!empty($vars['wrapper_type'])){

    if (!empty($pane_semantic_settings['element_wrapper']['class'])) {
      $vars['classes_array'] = array_merge($vars['classes_array'], explode(' ', $pane_semantic_settings['element_wrapper']['class']));
    }

    if (!empty($pane_semantic_settings['element_wrapper']['attributes_array'])) {
      $vars['attributes_array'] = array_merge($vars['attributes_array'], $pane_semantic_settings['element_wrapper']['attributes_array']);
    }

  }
}

/**
 * Render pane.
 */
function theme_semantic_panels_render_pane($vars) {
  return theme('semantic_panels_pane', $vars);
}

function _semantic_panels_get_options_styles(){
  $options = array(
    '' => t('Select a predefined style')
  );
  foreach(semantic_panels_style_load_all() as $style){
    if(!empty($style->category)){
      $options[$style->category][$style->name] = $style->admin_title;
    }else{
      $options[$style->name] = $style->admin_title;
    }
  }
  return $options;
}