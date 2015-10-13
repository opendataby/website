<?php
/**
 * @file
 * feature_opendata_groups.features.inc
 */

/**
 * Implements hook_field_default_field_instances_alter().
 */
function feature_opendata_groups_field_default_field_instances_alter(&$data) {
  if (isset($data['node-dataset-og_group_ref'])) {
    $data['node-dataset-og_group_ref']['display']['teaser']['weight'] = 20; /* WAS: 3 */
    $data['node-dataset-og_group_ref']['label'] = 'Издатель'; /* WAS: 'Publisher' */
    $data['node-dataset-og_group_ref']['settings']['behaviors']['og_widget']['access_override'] = 0; /* WAS: '' */
    $data['node-dataset-og_group_ref']['widget']['weight'] = 15; /* WAS: 14 */
  }
}

/**
 * Implements hook_strongarm_alter().
 */
function feature_opendata_groups_strongarm_alter(&$data) {
  if (isset($data['pathauto_node_group_pattern'])) {
    $data['pathauto_node_group_pattern']->value = 'group/[node:nid]'; /* WAS: 'group/[node:title]' */
  }
}

/**
 * Implements hook_views_default_views_alter().
 */
function feature_opendata_groups_views_default_views_alter(&$data) {
  if (isset($data['dkan_group_members'])) {
    $data['dkan_group_members']->display['default']->display_options['arguments']['gid']['exception'] = array(
      'title' => 'Все',
    ); /* WAS: '' */
    $data['dkan_group_members']->display['default']->display_options['arguments']['gid']['title'] = 'участники'; /* WAS: '%1 members' */
    $data['dkan_group_members']->display['default']->display_options['exposed_form']['options'] = array(
      'submit_button' => 'Применить',
      'reset_button_label' => 'Сбросить',
      'exposed_sorts_label' => 'Сортировать по',
      'sort_asc_label' => 'По возрастанию',
      'sort_desc_label' => 'По убыванию',
    ); /* WAS: '' */
    $data['dkan_group_members']->display['default']->display_options['pager']['options']['expose'] = array(
      'items_per_page_label' => 'Элементов на страницу',
      'items_per_page_options_all_label' => '- Все -',
      'offset_label' => 'Пропустить',
    ); /* WAS: '' */
    $data['dkan_group_members']->display['default']->display_options['pager']['options']['tags'] = array(
      'first' => '« первая',
      'previous' => '‹ предыдущая',
      'next' => 'следующая ›',
      'last' => 'последняя »',
    ); /* WAS: '' */
    $data['dkan_group_members']->display['default']->display_options['use_more_text'] = 'ещё'; /* WAS: '' */
  }
  if (isset($data['dkan_og_extras_group_members'])) {
    $data['dkan_og_extras_group_members']->display['block_1']->display_options['fields']['name']['label'] = 'Пользователь'; /* WAS: 'User' */
    $data['dkan_og_extras_group_members']->display['block_1']->display_options['fields']['og_roles']['label'] = 'Роль'; /* WAS: 'Role' */
    $data['dkan_og_extras_group_members']->display['default']->display_options['exposed_form']['options'] = array(
      'submit_button' => 'Применить',
      'reset_button_label' => 'Сбросить',
      'exposed_sorts_label' => 'Сортировать по',
      'sort_asc_label' => 'По возрастанию',
      'sort_desc_label' => 'По убыванию',
    ); /* WAS: '' */
    $data['dkan_og_extras_group_members']->display['default']->display_options['fields']['name']['label'] = 'Пользователь'; /* WAS: 'User' */
    $data['dkan_og_extras_group_members']->display['default']->display_options['fields']['og_roles']['label'] = 'Роль'; /* WAS: 'Role' */
    $data['dkan_og_extras_group_members']->display['default']->display_options['pager']['options']['expose'] = array(
      'items_per_page_label' => 'Элементов на страницу',
      'items_per_page_options_all_label' => '- Все -',
      'offset_label' => 'Пропустить',
    ); /* WAS: '' */
    $data['dkan_og_extras_group_members']->display['default']->display_options['pager']['options']['tags'] = array(
      'first' => '« первая',
      'previous' => '‹ предыдущая',
      'next' => 'следующая ›',
      'last' => 'последняя »',
    ); /* WAS: '' */
    $data['dkan_og_extras_group_members']->display['default']->display_options['use_more_text'] = 'ещё'; /* WAS: '' */
  }
  if (isset($data['group_block'])) {
    $data['group_block']->display['default']->display_options['arguments']['gid']['exception'] = array(
      'title' => 'Все',
    ); /* WAS: '' */
    $data['group_block']->display['default']->display_options['exposed_form']['options'] = array(
      'submit_button' => 'Применить',
      'reset_button_label' => 'Сбросить',
      'exposed_sorts_label' => 'Сортировать по',
      'sort_asc_label' => 'По возрастанию',
      'sort_desc_label' => 'По убыванию',
    ); /* WAS: '' */
    $data['group_block']->display['default']->display_options['use_more_text'] = 'ещё'; /* WAS: '' */
  }
  if (isset($data['groups_page'])) {
    $data['groups_page']->display['default']->display_options['exposed_form']['options'] = array(
      'submit_button' => 'Применить',
      'reset_button_label' => 'Сбросить',
      'exposed_sorts_label' => 'Сортировать по',
      'sort_asc_label' => 'По возрастанию',
      'sort_desc_label' => 'По убыванию',
    ); /* WAS: '' */
    $data['groups_page']->display['default']->display_options['pager']['options']['expose'] = array(
      'items_per_page_label' => 'Элементов на страницу',
      'items_per_page_options_all_label' => '- Все -',
      'offset_label' => 'Пропустить',
    ); /* WAS: '' */
    $data['groups_page']->display['default']->display_options['pager']['options']['tags'] = array(
      'first' => '« первая',
      'previous' => '‹ предыдущая',
      'next' => 'следующая ›',
      'last' => 'последняя »',
    ); /* WAS: '' */
    $data['groups_page']->display['default']->display_options['title'] = 'Группы данных'; /* WAS: 'Groups' */
    $data['groups_page']->display['default']->display_options['use_more_text'] = 'ещё'; /* WAS: '' */
  }
  if (isset($data['groups_search'])) {
    $data['groups_search']->display['default']->display_options['arguments']['og_group_ref']['exception'] = array(
      'title' => 'Все',
    ); /* WAS: '' */
    $data['groups_search']->display['default']->display_options['empty']['area']['content'] = 'По данному запросу ничего не найдено. '; /* WAS: 'No results were found. Please try another keyword.' */
    $data['groups_search']->display['default']->display_options['exposed_form']['options'] = array(
      'submit_button' => 'Применить',
      'reset_button_label' => 'Сбросить',
      'exposed_sorts_label' => 'Сортировать по',
      'sort_asc_label' => 'По возрастанию',
      'sort_desc_label' => 'По убыванию',
    ); /* WAS: '' */
    $data['groups_search']->display['default']->display_options['pager']['options']['expose'] = array(
      'items_per_page_label' => 'Элементов на страницу',
      'items_per_page_options_all_label' => '- Все -',
      'offset_label' => 'Пропустить',
    ); /* WAS: '' */
    $data['groups_search']->display['default']->display_options['pager']['options']['tags'] = array(
      'first' => '« первая',
      'previous' => '‹ предыдущая',
      'next' => 'следующая ›',
      'last' => 'последняя »',
    ); /* WAS: '' */
    $data['groups_search']->display['default']->display_options['sorts']['changed']['expose']['label'] = 'Дата изменена'; /* WAS: 'Date changed' */
    $data['groups_search']->display['default']->display_options['sorts']['title']['expose']['label'] = 'Заголовок'; /* WAS: 'Title' */
    $data['groups_search']->display['default']->display_options['use_more_text'] = 'ещё'; /* WAS: '' */
  }
  if (isset($data['og_count'])) {
    $data['og_count']->display['default']->display_options['arguments']['gid']['exception'] = array(
      'title' => 'Все',
    ); /* WAS: '' */
    $data['og_count']->display['default']->display_options['exposed_form']['options'] = array(
      'submit_button' => 'Применить',
      'reset_button_label' => 'Сбросить',
      'exposed_sorts_label' => 'Сортировать по',
      'sort_asc_label' => 'По возрастанию',
      'sort_desc_label' => 'По убыванию',
    ); /* WAS: '' */
    $data['og_count']->display['default']->display_options['fields']['gid']['alter']['text'] = '[gid] Датасеты'; /* WAS: '[gid] Datasets' */
    $data['og_count']->display['default']->display_options['pager']['options'] = array(
      'expose' => array(
        'items_per_page_label' => 'Элементов на страницу',
        'items_per_page_options_all_label' => '- Все -',
        'offset_label' => 'Пропустить',
      ),
      'tags' => array(
        'first' => '« первая',
        'previous' => '‹ предыдущая',
        'next' => 'следующая ›',
        'last' => 'последняя »',
      ),
    ); /* WAS: '' */
    $data['og_count']->display['default']->display_options['use_more_text'] = 'ещё'; /* WAS: '' */
  }
}
