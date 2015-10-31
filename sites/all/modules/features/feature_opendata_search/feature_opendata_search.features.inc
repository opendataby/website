<?php
/**
 * @file
 * feature_opendata_search.features.inc
 */

/**
 * Implements hook_context_default_contexts_alter().
 */
function feature_opendata_search_context_default_contexts_alter(&$data) {
  if (isset($data['dataset'])) {
    $data['dataset']->reactions['breadcrumb'] = 'mataset'; /* WAS: 'dataset' */
    unset($data['dataset']->reactions['block']['blocks']['dkan_sitewide-dkan_sitewide_license']);
    unset($data['dataset']->reactions['block']['blocks']['dkan_sitewide-dkan_sitewide_social']);
  }
}

/**
 * Implements hook_facetapi_default_facet_settings_alter().
 */
function feature_opendata_search_facetapi_default_facet_settings_alter(&$data) {
  if (isset($data['search_api@datasets:block:author'])) {
    $data['search_api@datasets:block:author']->settings['active_sorts']['active'] = 0; /* WAS: 'active' */
    $data['search_api@datasets:block:author']->settings['active_sorts']['count'] = 0; /* WAS: 'count' */
    $data['search_api@datasets:block:author']->settings['active_sorts']['indexed'] = 0; /* WAS: '' */
    $data['search_api@datasets:block:author']->settings['empty_text'] = array(
      'value' => '',
      'format' => 'html',
    ); /* WAS: '' */
    $data['search_api@datasets:block:author']->settings['sort_order']['indexed'] = 4; /* WAS: '' */
    $data['search_api@datasets:block:author']->settings['sort_weight']['indexed'] = 0; /* WAS: '' */
    $data['search_api@datasets:block:author']->settings['submit_realm'] = 'Сохранить и вернуться к настройкам'; /* WAS: '' */
  }
  if (isset($data['search_api@datasets:block:field_license'])) {
    $data['search_api@datasets:block:field_license']->enabled = FALSE; /* WAS: TRUE */
  }
  if (isset($data['search_api@datasets:block:field_resources:field_format'])) {
    $data['search_api@datasets:block:field_resources:field_format']->enabled = FALSE; /* WAS: TRUE */
  }
  if (isset($data['search_api@datasets:block:field_tags'])) {
    $data['search_api@datasets:block:field_tags']->enabled = FALSE; /* WAS: TRUE */
  }
  if (isset($data['search_api@datasets:block:og_group_ref'])) {
    $data['search_api@datasets:block:og_group_ref']->settings['active_sorts']['active'] = 0; /* WAS: 'active' */
    $data['search_api@datasets:block:og_group_ref']->settings['active_sorts']['count'] = 0; /* WAS: 'count' */
    $data['search_api@datasets:block:og_group_ref']->settings['active_sorts']['indexed'] = 0; /* WAS: '' */
    $data['search_api@datasets:block:og_group_ref']->settings['empty_text'] = array(
      'value' => '',
      'format' => 'html',
    ); /* WAS: '' */
    $data['search_api@datasets:block:og_group_ref']->settings['sort_order']['indexed'] = 4; /* WAS: '' */
    $data['search_api@datasets:block:og_group_ref']->settings['sort_weight']['indexed'] = 0; /* WAS: '' */
    $data['search_api@datasets:block:og_group_ref']->settings['submit_realm'] = 'Сохранить и вернуться к настройкам'; /* WAS: '' */
  }
}

/**
 * Implements hook_views_default_views_alter().
 */
function feature_opendata_search_views_default_views_alter(&$data) {
  if (isset($data['dataset'])) {
    $data['dataset']->display['block_1'] = unserialize('O:13:"views_display":7:{s:15:"display_options";a:10:{s:5:"query";a:2:{s:4:"type";s:11:"views_query";s:7:"options";a:0:{}}s:8:"defaults";a:10:{s:5:"title";b:0;s:9:"css_class";b:0;s:5:"pager";b:0;s:12:"style_plugin";b:0;s:13:"style_options";b:0;s:10:"row_plugin";b:0;s:11:"row_options";b:0;s:6:"header";b:0;s:6:"footer";b:0;s:6:"fields";b:0;}s:5:"title";s:20:"Обновления";s:9:"css_class";s:21:"block-recent-datasets";s:5:"pager";a:2:{s:4:"type";s:4:"some";s:7:"options";a:2:{s:14:"items_per_page";s:1:"5";s:6:"offset";s:1:"0";}}s:12:"style_plugin";s:7:"default";s:10:"row_plugin";s:6:"fields";s:6:"footer";a:1:{s:4:"area";a:5:{s:2:"id";s:4:"area";s:5:"table";s:5:"views";s:5:"field";s:4:"area";s:7:"content";s:68:"<a class="block-footer-link" href="/dataset">Все наборы</a>";s:6:"format";s:4:"html";}}s:6:"fields";a:1:{s:5:"title";a:6:{s:2:"id";s:5:"title";s:5:"table";s:25:"search_api_index_datasets";s:5:"field";s:5:"title";s:5:"label";s:0:"";s:19:"element_label_colon";b:0;s:14:"link_to_entity";i:1;}}s:17:"block_description";s:24:"[front, recent datasets]";}s:8:"db_table";s:13:"views_display";s:3:"vid";i:0;s:2:"id";s:7:"block_1";s:13:"display_title";s:8:"Блок";s:14:"display_plugin";s:5:"block";s:8:"position";i:0;}'); /* WAS: '' */
    $data['dataset']->display['default']->display_options['empty']['area']['content'] = 'Ничего не найдено. Попробуйте другой запрос.'; /* WAS: 'No results were found. Please try another keyword.' */
    $data['dataset']->display['default']->display_options['exposed_form']['options'] = array(
      'submit_button' => 'Применить',
      'reset_button_label' => 'Сбросить',
      'exposed_sorts_label' => 'Сортировать по',
      'sort_asc_label' => 'По возрастанию',
      'sort_desc_label' => 'По убыванию',
    ); /* WAS: '' */
    $data['dataset']->display['default']->display_options['pager']['options']['expose'] = array(
      'items_per_page_label' => 'Элементов на страницу',
      'items_per_page_options_all_label' => '- Все -',
      'offset_label' => 'Пропустить',
    ); /* WAS: '' */
    $data['dataset']->display['default']->display_options['pager']['options']['tags'] = array(
      'first' => '« первая',
      'previous' => '‹ предыдущая',
      'next' => 'следующая ›',
      'last' => 'последняя »',
    ); /* WAS: '' */
    $data['dataset']->display['default']->display_options['title'] = 'Наборы данных'; /* WAS: 'Datasets' */
    $data['dataset']->display['default']->display_options['use_more_text'] = 'ещё'; /* WAS: '' */
    $data['dataset']->display['page']->display_options['defaults']['header'] = FALSE; /* WAS: '' */
    $data['dataset']->display['page']->display_options['defaults']['pager'] = FALSE; /* WAS: '' */
    $data['dataset']->display['page']->display_options['defaults']['title'] = FALSE; /* WAS: '' */
    $data['dataset']->display['page']->display_options['header'] = array(
      'result' => array(
        'id' => 'result',
        'table' => 'views',
        'field' => 'result',
        'content' => '@total наборов',
      ),
    ); /* WAS: '' */
    $data['dataset']->display['page']->display_options['pager'] = array(
      'type' => 'full',
      'options' => array(
        'items_per_page' => 11,
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
      ),
    ); /* WAS: '' */
    $data['dataset']->display['page']->display_options['title'] = 'Поиск данных'; /* WAS: '' */
    unset($data['dataset']->display['default']->display_options['sorts']['changed']['expose']);
    unset($data['dataset']->display['default']->display_options['sorts']['changed']['exposed']);
    unset($data['dataset']->display['default']->display_options['sorts']['title']);
  }
}
