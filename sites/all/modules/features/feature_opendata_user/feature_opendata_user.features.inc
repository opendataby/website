<?php
/**
 * @file
 * feature_opendata_user.features.inc
 */

/**
 * Implements hook_views_default_views_alter().
 */
function feature_opendata_user_views_default_views_alter(&$data) {
  if (isset($data['user_profile_fields'])) {
    $data['user_profile_fields']->display['default']->display_options['arguments']['uid']['exception'] = array(
      'title' => 'Все',
    ); /* WAS: '' */
    $data['user_profile_fields']->display['default']->display_options['exposed_form']['options'] = array(
      'submit_button' => 'Применить',
      'reset_button_label' => 'Сбросить',
      'exposed_sorts_label' => 'Сортировать по',
      'sort_asc_label' => 'По возрастанию',
      'sort_desc_label' => 'По убыванию',
    ); /* WAS: '' */
    $data['user_profile_fields']->display['default']->display_options['use_more_text'] = 'ещё'; /* WAS: '' */
  }
  if (isset($data['user_profile_search'])) {
    $data['user_profile_search']->display['default']->display_options['arguments']['author']['exception'] = array(
      'title' => 'Все',
    ); /* WAS: '' */
    $data['user_profile_search']->display['default']->display_options['empty']['area']['content'] = 'По данному запросу ничего не найдено. '; /* WAS: 'No results were found. Please try another keyword.' */
    $data['user_profile_search']->display['default']->display_options['exposed_form']['options'] = array(
      'submit_button' => 'Применить',
      'reset_button_label' => 'Сбросить',
      'exposed_sorts_label' => 'Сортировать по',
      'sort_asc_label' => 'По возрастанию',
      'sort_desc_label' => 'По убыванию',
    ); /* WAS: '' */
    $data['user_profile_search']->display['default']->display_options['pager']['options']['expose'] = array(
      'items_per_page_label' => 'Элементов на страницу',
      'items_per_page_options_all_label' => '- Все -',
      'offset_label' => 'Пропустить',
    ); /* WAS: '' */
    $data['user_profile_search']->display['default']->display_options['pager']['options']['tags'] = array(
      'first' => '« первая',
      'previous' => '‹ предыдущая',
      'next' => 'следующая ›',
      'last' => 'последняя »',
    ); /* WAS: '' */
    $data['user_profile_search']->display['default']->display_options['use_more_text'] = 'ещё'; /* WAS: '' */
  }
}
