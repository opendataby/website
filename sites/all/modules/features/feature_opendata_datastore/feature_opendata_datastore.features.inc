<?php
/**
 * @file
 * feature_opendata_datastore.features.inc
 */

/**
 * Implements hook_views_default_views_alter().
 */
function feature_opendata_datastore_views_default_views_alter(&$data) {
  if (isset($data['datasets'])) {
    $data['datasets']->display['default']->display_options['exposed_form']['options'] = array(
      'submit_button' => 'Применить',
      'reset_button_label' => 'Сбросить',
      'exposed_sorts_label' => 'Сортировать по',
      'sort_asc_label' => 'По возрастанию',
      'sort_desc_label' => 'По убыванию',
    ); /* WAS: '' */
    $data['datasets']->display['default']->display_options['fields']['nid']['alter']['text'] = 'изменить'; /* WAS: 'edit' */
    $data['datasets']->display['default']->display_options['fields']['nid']['label'] = 'Управление Хранилищем Данных'; /* WAS: 'Manage Datastore' */
    $data['datasets']->display['default']->display_options['fields']['title_1']['label'] = 'Набор данных'; /* WAS: 'Dataset' */
    $data['datasets']->display['default']->display_options['fields']['title']['label'] = 'Русурс'; /* WAS: 'Resource' */
    $data['datasets']->display['default']->display_options['pager']['options']['expose'] = array(
      'items_per_page_label' => 'Элементов на страницу',
      'items_per_page_options_all_label' => '- Все -',
      'offset_label' => 'Пропустить',
    ); /* WAS: '' */
    $data['datasets']->display['default']->display_options['pager']['options']['tags'] = array(
      'first' => '« первая',
      'previous' => '‹ предыдущая',
      'next' => 'следующая ›',
      'last' => 'последняя »',
    ); /* WAS: '' */
    $data['datasets']->display['default']->display_options['title'] = 'Управление Хранилищем Данных'; /* WAS: 'Manage Datastore' */
    $data['datasets']->display['default']->display_options['use_more_text'] = 'ещё'; /* WAS: '' */
  }
}
