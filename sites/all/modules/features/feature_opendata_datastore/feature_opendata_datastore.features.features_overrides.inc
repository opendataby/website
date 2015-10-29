<?php
/**
 * @file
 * feature_opendata_datastore.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function feature_opendata_datastore_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: views_view
  $overrides["views_view.datasets.display|default|display_options|exposed_form|options"] = array(
    'submit_button' => 'Применить',
    'reset_button_label' => 'Сбросить',
    'exposed_sorts_label' => 'Сортировать по',
    'sort_asc_label' => 'По возрастанию',
    'sort_desc_label' => 'По убыванию',
  );
  $overrides["views_view.datasets.display|default|display_options|fields|nid|alter|text"] = 'изменить';
  $overrides["views_view.datasets.display|default|display_options|fields|nid|label"] = 'Управление Хранилищем Данных';
  $overrides["views_view.datasets.display|default|display_options|fields|title_1|label"] = 'Набор данных';
  $overrides["views_view.datasets.display|default|display_options|fields|title|label"] = 'Русурс';
  $overrides["views_view.datasets.display|default|display_options|pager|options|expose"] = array(
    'items_per_page_label' => 'Элементов на страницу',
    'items_per_page_options_all_label' => '- Все -',
    'offset_label' => 'Пропустить',
  );
  $overrides["views_view.datasets.display|default|display_options|pager|options|tags"] = array(
    'first' => '« первая',
    'previous' => '‹ предыдущая',
    'next' => 'следующая ›',
    'last' => 'последняя »',
  );
  $overrides["views_view.datasets.display|default|display_options|title"] = 'Управление Хранилищем Данных';
  $overrides["views_view.datasets.display|default|display_options|use_more_text"] = 'ещё';

 return $overrides;
}
