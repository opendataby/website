<?php
/**
 * @file
 * feature_opendata_groups.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_opendata_groups_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.node-dataset-og_group_ref.display|teaser|weight"] = 20;
  $overrides["field_instance.node-dataset-og_group_ref.label"] = 'Издатель';
  $overrides["field_instance.node-dataset-og_group_ref.settings|behaviors|og_widget|access_override"] = 0;
  $overrides["field_instance.node-dataset-og_group_ref.widget|weight"] = 15;

  // Exported overrides for: variable
  $overrides["variable.pathauto_node_group_pattern.value"] = 'group/[node:nid]';

  // Exported overrides for: views_view
  $overrides["views_view.dkan_group_members.display|default|display_options|arguments|gid|exception"] = array(
    'title' => 'Все',
  );
  $overrides["views_view.dkan_group_members.display|default|display_options|arguments|gid|title"] = 'участники';
  $overrides["views_view.dkan_group_members.display|default|display_options|exposed_form|options"] = array(
    'submit_button' => 'Применить',
    'reset_button_label' => 'Сбросить',
    'exposed_sorts_label' => 'Сортировать по',
    'sort_asc_label' => 'По возрастанию',
    'sort_desc_label' => 'По убыванию',
  );
  $overrides["views_view.dkan_group_members.display|default|display_options|pager|options|expose"] = array(
    'items_per_page_label' => 'Элементов на страницу',
    'items_per_page_options_all_label' => '- Все -',
    'offset_label' => 'Пропустить',
  );
  $overrides["views_view.dkan_group_members.display|default|display_options|pager|options|tags"] = array(
    'first' => '« первая',
    'previous' => '‹ предыдущая',
    'next' => 'следующая ›',
    'last' => 'последняя »',
  );
  $overrides["views_view.dkan_group_members.display|default|display_options|use_more_text"] = 'ещё';
  $overrides["views_view.dkan_og_extras_group_members.display|block_1|display_options|fields|name|label"] = 'Пользователь';
  $overrides["views_view.dkan_og_extras_group_members.display|block_1|display_options|fields|og_roles|label"] = 'Роль';
  $overrides["views_view.dkan_og_extras_group_members.display|default|display_options|exposed_form|options"] = array(
    'submit_button' => 'Применить',
    'reset_button_label' => 'Сбросить',
    'exposed_sorts_label' => 'Сортировать по',
    'sort_asc_label' => 'По возрастанию',
    'sort_desc_label' => 'По убыванию',
  );
  $overrides["views_view.dkan_og_extras_group_members.display|default|display_options|fields|name|label"] = 'Пользователь';
  $overrides["views_view.dkan_og_extras_group_members.display|default|display_options|fields|og_roles|label"] = 'Роль';
  $overrides["views_view.dkan_og_extras_group_members.display|default|display_options|pager|options|expose"] = array(
    'items_per_page_label' => 'Элементов на страницу',
    'items_per_page_options_all_label' => '- Все -',
    'offset_label' => 'Пропустить',
  );
  $overrides["views_view.dkan_og_extras_group_members.display|default|display_options|pager|options|tags"] = array(
    'first' => '« первая',
    'previous' => '‹ предыдущая',
    'next' => 'следующая ›',
    'last' => 'последняя »',
  );
  $overrides["views_view.dkan_og_extras_group_members.display|default|display_options|use_more_text"] = 'ещё';
  $overrides["views_view.group_block.display|default|display_options|arguments|gid|exception"] = array(
    'title' => 'Все',
  );
  $overrides["views_view.group_block.display|default|display_options|exposed_form|options"] = array(
    'submit_button' => 'Применить',
    'reset_button_label' => 'Сбросить',
    'exposed_sorts_label' => 'Сортировать по',
    'sort_asc_label' => 'По возрастанию',
    'sort_desc_label' => 'По убыванию',
  );
  $overrides["views_view.group_block.display|default|display_options|use_more_text"] = 'ещё';
  $overrides["views_view.groups_page.display|default|display_options|exposed_form|options"] = array(
    'submit_button' => 'Применить',
    'reset_button_label' => 'Сбросить',
    'exposed_sorts_label' => 'Сортировать по',
    'sort_asc_label' => 'По возрастанию',
    'sort_desc_label' => 'По убыванию',
  );
  $overrides["views_view.groups_page.display|default|display_options|pager|options|expose"] = array(
    'items_per_page_label' => 'Элементов на страницу',
    'items_per_page_options_all_label' => '- Все -',
    'offset_label' => 'Пропустить',
  );
  $overrides["views_view.groups_page.display|default|display_options|pager|options|tags"] = array(
    'first' => '« первая',
    'previous' => '‹ предыдущая',
    'next' => 'следующая ›',
    'last' => 'последняя »',
  );
  $overrides["views_view.groups_page.display|default|display_options|title"] = 'Группы данных';
  $overrides["views_view.groups_page.display|default|display_options|use_more_text"] = 'ещё';
  $overrides["views_view.groups_search.display|default|display_options|arguments|og_group_ref|exception"] = array(
    'title' => 'Все',
  );
  $overrides["views_view.groups_search.display|default|display_options|empty|area|content"] = 'По данному запросу ничего не найдено. ';
  $overrides["views_view.groups_search.display|default|display_options|exposed_form|options"] = array(
    'submit_button' => 'Применить',
    'reset_button_label' => 'Сбросить',
    'exposed_sorts_label' => 'Сортировать по',
    'sort_asc_label' => 'По возрастанию',
    'sort_desc_label' => 'По убыванию',
  );
  $overrides["views_view.groups_search.display|default|display_options|pager|options|expose"] = array(
    'items_per_page_label' => 'Элементов на страницу',
    'items_per_page_options_all_label' => '- Все -',
    'offset_label' => 'Пропустить',
  );
  $overrides["views_view.groups_search.display|default|display_options|pager|options|tags"] = array(
    'first' => '« первая',
    'previous' => '‹ предыдущая',
    'next' => 'следующая ›',
    'last' => 'последняя »',
  );
  $overrides["views_view.groups_search.display|default|display_options|sorts|changed|expose|label"] = 'Дата изменена';
  $overrides["views_view.groups_search.display|default|display_options|sorts|title|expose|label"] = 'Заголовок';
  $overrides["views_view.groups_search.display|default|display_options|use_more_text"] = 'ещё';
  $overrides["views_view.og_count.display|default|display_options|arguments|gid|exception"] = array(
    'title' => 'Все',
  );
  $overrides["views_view.og_count.display|default|display_options|exposed_form|options"] = array(
    'submit_button' => 'Применить',
    'reset_button_label' => 'Сбросить',
    'exposed_sorts_label' => 'Сортировать по',
    'sort_asc_label' => 'По возрастанию',
    'sort_desc_label' => 'По убыванию',
  );
  $overrides["views_view.og_count.display|default|display_options|fields|gid|alter|text"] = '[gid] Датасеты';
  $overrides["views_view.og_count.display|default|display_options|pager|options"] = array(
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
  );
  $overrides["views_view.og_count.display|default|display_options|use_more_text"] = 'ещё';

 return $overrides;
}
