<?php
/**
 * @file
 * opendata_dataset_content_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function opendata_dataset_content_types_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_field_default_field_bases_alter().
 */
function opendata_dataset_content_types_field_default_field_bases_alter(&$data) {
  if (isset($data['field_author'])) {
    $data['field_author']['cardinality'] = -1; /* WAS: 1 */
  }
  if (isset($data['field_frequency'])) {
    $data['field_frequency']['settings']['allowed_values'][0] = 'Ежедневно'; /* WAS: 'Annually' */
    $data['field_frequency']['settings']['allowed_values'][1] = 'Непрерывно'; /* WAS: 'Continuously' */
    $data['field_frequency']['settings']['allowed_values'][2] = 'Нерегулярно'; /* WAS: 'Daily' */
    $data['field_frequency']['settings']['allowed_values'][3] = 'Раз в год'; /* WAS: 'Irregularly' */
    $data['field_frequency']['settings']['allowed_values'][4] = 'Раз в месяц'; /* WAS: 'Monthly' */
    $data['field_frequency']['settings']['allowed_values'][5] = 'Раз в неделю'; /* WAS: 'Weekly' */
  }
  if (isset($data['field_public_access_level'])) {
    $data['field_public_access_level']['settings']['allowed_values']['private'] = 'Частный'; /* WAS: 'Private' */
    $data['field_public_access_level']['settings']['allowed_values']['public'] = 'Публичный'; /* WAS: 'Public' */
    $data['field_public_access_level']['settings']['allowed_values']['restricted'] = 'Ограниченный'; /* WAS: 'Restricted' */
  }
  if (isset($data['field_tags'])) {
    $data['field_tags']['settings']['options_list_callback'] = 'i18n_taxonomy_allowed_values'; /* WAS: '' */
  }
}

/**
 * Implements hook_field_group_info_alter().
 */
function opendata_dataset_content_types_field_group_info_alter(&$data) {
  if (isset($data['group_additional|node|dataset|form'])) {
    $data['group_additional|node|dataset|form']->data['weight'] = 2; /* WAS: 1 */
  }
  if (isset($data['group_link_api|node|resource|form'])) {
    $data['group_link_api|node|resource|form']->data['weight'] = 14; /* WAS: 11 */
  }
  if (isset($data['group_link_file|node|resource|form'])) {
    $data['group_link_file|node|resource|form']->data['weight'] = 13; /* WAS: 9 */
  }
  if (isset($data['group_primary|node|dataset|form'])) {
    $data['group_primary|node|dataset|form']->data['children'][3] = 'field_geo'; /* WAS: 'title' */
    $data['group_primary|node|dataset|form']->data['children'][4] = 'field_spec_projects'; /* WAS: '' */
    $data['group_primary|node|dataset|form']->data['children'][5] = 'title'; /* WAS: '' */
  }
}

/**
 * Implements hook_field_default_field_instances_alter().
 */
function opendata_dataset_content_types_field_default_field_instances_alter(&$data) {
  if (isset($data['node-dataset-body'])) {
    $data['node-dataset-body']['display']['teaser']['weight'] = 4; /* WAS: 1 */
    $data['node-dataset-body']['label'] = 'Описание'; /* WAS: 'Description' */
    $data['node-dataset-body']['widget']['weight'] = 2; /* WAS: 1 */
  }
  if (isset($data['node-dataset-field_additional_info'])) {
    $data['node-dataset-field_additional_info']['display']['default']['settings']['style'] = 'inline'; /* WAS: '' */
    $data['node-dataset-field_additional_info']['display']['default']['type'] = 'double_field_unformatted_list'; /* WAS: 'double_field_table' */
    $data['node-dataset-field_additional_info']['display']['teaser']['weight'] = 13; /* WAS: 0 */
    $data['node-dataset-field_additional_info']['label'] = 'Дополнительная информация'; /* WAS: 'Additional Info' */
    $data['node-dataset-field_additional_info']['widget']['weight'] = 22; /* WAS: 21 */
    unset($data['node-dataset-field_additional_info']['display']['default']['settings']['table']);
  }
  if (isset($data['node-dataset-field_author'])) {
    $data['node-dataset-field_author']['default_value'][0] = array(
      'value' => 'http://',
    ); /* WAS: '' */
    $data['node-dataset-field_author']['description'] = 'Источник информации'; /* WAS: 'This is the author of the dataset.' */
    $data['node-dataset-field_author']['display']['teaser']['weight'] = 22; /* WAS: 6 */
    $data['node-dataset-field_author']['label'] = 'Источник'; /* WAS: 'Author' */
    $data['node-dataset-field_author']['widget']['settings']['size'] = 120; /* WAS: 60 */
  }
  if (isset($data['node-dataset-field_contact_email'])) {
    $data['node-dataset-field_contact_email']['display']['teaser']['weight'] = 15; /* WAS: 0 */
    $data['node-dataset-field_contact_email']['label'] = 'Контактный Email'; /* WAS: 'Contact Email' */
    $data['node-dataset-field_contact_email']['widget']['weight'] = 20; /* WAS: 19 */
  }
  if (isset($data['node-dataset-field_contact_name'])) {
    $data['node-dataset-field_contact_name']['display']['teaser']['weight'] = 19; /* WAS: 0 */
    $data['node-dataset-field_contact_name']['label'] = 'Контактное имя'; /* WAS: 'Contact Name' */
    $data['node-dataset-field_contact_name']['widget']['weight'] = 19; /* WAS: 18 */
  }
  if (isset($data['node-dataset-field_data_dictionary'])) {
    $data['node-dataset-field_data_dictionary']['display']['teaser']['weight'] = 16; /* WAS: 0 */
    $data['node-dataset-field_data_dictionary']['widget']['weight'] = 18; /* WAS: 17 */
  }
  if (isset($data['node-dataset-field_frequency'])) {
    $data['node-dataset-field_frequency']['description'] = 'Частота, с которой публикуется набор данных. Смотрите <a href="http://www.w3.org/TR/vocab-dcat/#Property:dataset_frequency">Ссылку</a> для информации.'; /* WAS: 'The frequency with which dataset is published.See <a href="http://www.w3.org/TR/vocab-dcat/#Property:dataset_frequency">DCAT frequency</a> for more info.' */
    $data['node-dataset-field_frequency']['display']['teaser']['weight'] = 17; /* WAS: 0 */
    $data['node-dataset-field_frequency']['label'] = 'Частота'; /* WAS: 'Frequency' */
  }
  if (isset($data['node-dataset-field_granularity'])) {
    $data['node-dataset-field_granularity']['display']['teaser']['weight'] = 18; /* WAS: 0 */
    $data['node-dataset-field_granularity']['label'] = 'Гранулярность'; /* WAS: 'Granularity' */
    $data['node-dataset-field_granularity']['widget']['weight'] = 17; /* WAS: 16 */
  }
  if (isset($data['node-dataset-field_license'])) {
    $data['node-dataset-field_license']['description'] = 'Определение лицензий и дополнительная информация могут быть найдены на сайте <a href="http://opendefinition.org">opendefinition.org</a>'; /* WAS: 'License definitions and additional information can be found at <a href="http://opendefinition.org">opendefinition.org</a>' */
    $data['node-dataset-field_license']['display']['teaser']['weight'] = 21; /* WAS: 5 */
    $data['node-dataset-field_license']['label'] = 'Лицензия'; /* WAS: 'License' */
    $data['node-dataset-field_license']['widget']['settings']['available_options'] = 'cc-by|Creative Commons Attribution
            cc-by-sa|Creative Commons Attribution Share-Alike
            cc-zero|Creative Commons CCZero
            cc-nc|Creative Commons Non-Commercial (Any)
            gfdl|GNU Free Documentation License
            notspecified|License Not Specified
            odc-by|Open Data Commons Attribution License
            odc-odbl|Open Data Commons Open Database License (ODbL)
            odc-pddl|Open Data Commons Public Domain Dedication and Licence (PDDL)
            other-at|Other (Attribution)
            other-nc|Other (Non-Commercial)
            other-closed|Other (Not Open)
            other-open|Other (Open)
            other-pd|Other (Public Domain)
            uk-ogl|UK Open Government Licence (OGL)'; /* WAS: 'cc-by|Creative Commons Attribution
    cc-by-sa|Creative Commons Attribution Share-Alike
    cc-zero|Creative Commons CCZero
    cc-nc|Creative Commons Non-Commercial (Any)
    gfdl|GNU Free Documentation License
    notspecified|License Not Specified
    odc-by|Open Data Commons Attribution License
    odc-odbl|Open Data Commons Open Database License (ODbL)
    odc-pddl|Open Data Commons Public Domain Dedication and Licence (PDDL)
    other-at|Other (Attribution)
    other-nc|Other (Non-Commercial)
    other-closed|Other (Not Open)
    other-open|Other (Open)
    other-pd|Other (Public Domain)
    uk-ogl|UK Open Government Licence (OGL)' */
    $data['node-dataset-field_license']['widget']['weight'] = 6; /* WAS: 3 */
  }
  if (isset($data['node-dataset-field_public_access_level'])) {
    $data['node-dataset-field_public_access_level']['display']['teaser']['weight'] = 14; /* WAS: 0 */
    $data['node-dataset-field_public_access_level']['label'] = 'Уровень доступа'; /* WAS: 'Public Access Level' */
    $data['node-dataset-field_public_access_level']['widget']['weight'] = 21; /* WAS: 20 */
  }
  if (isset($data['node-dataset-field_related_content'])) {
    $data['node-dataset-field_related_content']['description'] = 'Внутренняя или внешняя ссылка которая обеспечивает дополнительную информацию по набору данных.'; /* WAS: 'An internal link or link to an outside resource that provides additional context to the dataset.' */
    $data['node-dataset-field_related_content']['display']['teaser']['weight'] = 8; /* WAS: 0 */
    $data['node-dataset-field_related_content']['label'] = 'Похожие материалы'; /* WAS: 'Related Content' */
    $data['node-dataset-field_related_content']['widget']['weight'] = 24; /* WAS: 23 */
  }
  if (isset($data['node-dataset-field_resources'])) {
    $data['node-dataset-field_resources']['display']['teaser']['weight'] = 7; /* WAS: 0 */
    $data['node-dataset-field_resources']['label'] = 'Ресурсы'; /* WAS: 'Resources' */
    $data['node-dataset-field_resources']['widget']['weight'] = 23; /* WAS: 22 */
  }
  if (isset($data['node-dataset-field_spatial'])) {
    $data['node-dataset-field_spatial']['display']['teaser']['weight'] = 6; /* WAS: 0 */
    $data['node-dataset-field_spatial']['label'] = 'Пространственный (географический) охват'; /* WAS: 'Spatial / Geographical Coverage Area' */
  }
  if (isset($data['node-dataset-field_spatial_geographical_cover'])) {
    $data['node-dataset-field_spatial_geographical_cover']['display']['teaser']['weight'] = 9; /* WAS: 0 */
  }
  if (isset($data['node-dataset-field_tags'])) {
    $data['node-dataset-field_tags']['display']['teaser']['label'] = 'hidden'; /* WAS: 'above' */
    $data['node-dataset-field_tags']['display']['teaser']['weight'] = 5; /* WAS: 2 */
    $data['node-dataset-field_tags']['label'] = 'Тэги'; /* WAS: 'Tags' */
    $data['node-dataset-field_tags']['widget']['settings']['delimiter'] = ''; /* WAS: '' */
    $data['node-dataset-field_tags']['widget']['weight'] = 4; /* WAS: 2 */
  }
  if (isset($data['node-dataset-field_temporal_coverage'])) {
    $data['node-dataset-field_temporal_coverage']['description'] = 'Временной период который охватывает набор данных. Смотри <a href="http://www.w3.org/TR/vocab-dcat/#Property:dataset_temporal">ссылку</a> для подробной информации.'; /* WAS: 'The temporal period that the dataset covers. See DCAT <a href="http://www.w3.org/TR/vocab-dcat/#Property:dataset_temporal">temporal coverage</a> for more info.' */
    $data['node-dataset-field_temporal_coverage']['display']['teaser']['weight'] = 10; /* WAS: 0 */
    $data['node-dataset-field_temporal_coverage']['label'] = 'Временной охват'; /* WAS: 'Temporal Coverage' */
    $data['node-dataset-field_temporal_coverage']['widget']['weight'] = 16; /* WAS: 15 */
  }
  if (isset($data['node-resource-body'])) {
    $data['node-resource-body']['label'] = 'Описание'; /* WAS: 'Description' */
  }
  if (isset($data['node-resource-field_dataset_ref'])) {
    $data['node-resource-field_dataset_ref']['label'] = 'Набор данных'; /* WAS: 'Dataset' */
  }
  if (isset($data['node-resource-field_format'])) {
    $data['node-resource-field_format']['label'] = 'Формат'; /* WAS: 'Format' */
    $data['node-resource-field_format']['widget']['settings']['delimiter'] = ''; /* WAS: '' */
    $data['node-resource-field_format']['widget']['settings']['limit'] = 10; /* WAS: '' */
    $data['node-resource-field_format']['widget']['settings']['min_length'] = 0; /* WAS: '' */
    unset($data['node-resource-field_format']['widget']['settings']['apply_chosen']);
    unset($data['node-resource-field_format']['widget']['settings']['autocomplete_path']);
    unset($data['node-resource-field_format']['widget']['settings']['mode']);
  }
  if (isset($data['node-resource-field_link_remote_file'])) {
    $data['node-resource-field_link_remote_file']['settings']['file_extensions'] = 'csv html xls json xlsx doc rdf txt jpg png gif tiff pdf odf ods odt tsv geojson xml zip tif'; /* WAS: 'csv html xls json xlsx doc docx rdf txt jpg png gif tiff pdf odf ods odt tsv geojson xml zip' */
  }
  if (isset($data['node-resource-field_upload'])) {
    $data['node-resource-field_upload']['settings']['file_directory'] = 'resources'; /* WAS: '' */
    $data['node-resource-field_upload']['settings']['file_extensions'] = 'kml csv html xls json xlsx doc rdf txt jpg jpeg png gif tiff tif pdf odf ods odt tsv geojson xml zip'; /* WAS: 'csv html xls json xlsx doc docx rdf txt jpg png gif tiff pdf odf ods odt tsv geojson xml zip' */
  }
}

/**
 * Implements hook_taxonomy_default_vocabularies_alter().
 */
function opendata_dataset_content_types_taxonomy_default_vocabularies_alter(&$data) {
  if (isset($data['format'])) {
    $data['format']['i18n_mode'] = 0; /* WAS: '' */
    $data['format']['language'] = 'und'; /* WAS: '' */
    $data['format']['name'] = 'Формат'; /* WAS: 'Format' */
  }
  if (isset($data['tags'])) {
    $data['tags']['description'] = 'Тэги в свободной форме'; /* WAS: 'eg. economy, mental health, government' */
    $data['tags']['i18n_mode'] = 0; /* WAS: '' */
    $data['tags']['language'] = 'und'; /* WAS: '' */
    $data['tags']['name'] = 'Тэги'; /* WAS: 'Tags' */
  }
}

/**
 * Implements hook_strongarm_alter().
 */
function opendata_dataset_content_types_strongarm_alter(&$data) {
  if (isset($data['field_bundle_settings_node__dataset'])) {
    $data['field_bundle_settings_node__dataset']->value['extra_fields']['display']['identifier']['teaser'] = array(
      'weight' => 0,
      'visible' => TRUE,
    ); /* WAS: '' */
    $data['field_bundle_settings_node__dataset']->value['extra_fields']['display']['modified_date']['teaser'] = array(
      'weight' => 2,
      'visible' => TRUE,
    ); /* WAS: '' */
    $data['field_bundle_settings_node__dataset']->value['extra_fields']['display']['release_date']['teaser'] = array(
      'weight' => 3,
      'visible' => TRUE,
    ); /* WAS: '' */
    $data['field_bundle_settings_node__dataset']->value['extra_fields']['display']['resources']['teaser']['weight'] = 1; /* WAS: 0 */
    $data['field_bundle_settings_node__dataset']->value['extra_fields']['form']['metatags'] = array(
      'weight' => 9,
    ); /* WAS: '' */
  }
}
