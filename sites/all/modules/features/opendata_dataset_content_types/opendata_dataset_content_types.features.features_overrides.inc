<?php
/**
 * @file
 * opendata_dataset_content_types.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function opendata_dataset_content_types_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_base
  $overrides["field_base.field_author.cardinality"] = -1;
  $overrides["field_base.field_frequency.settings|allowed_values|0"] = 'Ежедневно';
  $overrides["field_base.field_frequency.settings|allowed_values|1"] = 'Непрерывно';
  $overrides["field_base.field_frequency.settings|allowed_values|2"] = 'Нерегулярно';
  $overrides["field_base.field_frequency.settings|allowed_values|3"] = 'Раз в год';
  $overrides["field_base.field_frequency.settings|allowed_values|4"] = 'Раз в месяц';
  $overrides["field_base.field_frequency.settings|allowed_values|5"] = 'Раз в неделю';
  $overrides["field_base.field_public_access_level.settings|allowed_values|private"] = 'Частный';
  $overrides["field_base.field_public_access_level.settings|allowed_values|public"] = 'Публичный';
  $overrides["field_base.field_public_access_level.settings|allowed_values|restricted"] = 'Ограниченный';
  $overrides["field_base.field_tags.settings|options_list_callback"] = 'i18n_taxonomy_allowed_values';

  // Exported overrides for: field_group
  $overrides["field_group.group_additional|node|dataset|form.data|weight"] = 2;
  $overrides["field_group.group_link_api|node|resource|form.data|weight"] = 14;
  $overrides["field_group.group_link_file|node|resource|form.data|weight"] = 13;
  $overrides["field_group.group_primary|node|dataset|form.data|children|3"] = 'field_geo';
  $overrides["field_group.group_primary|node|dataset|form.data|children|4"] = 'field_spec_projects';
  $overrides["field_group.group_primary|node|dataset|form.data|children|5"] = 'title';

  // Exported overrides for: field_instance
  $overrides["field_instance.node-dataset-body.display|teaser|weight"] = 4;
  $overrides["field_instance.node-dataset-body.label"] = 'Описание';
  $overrides["field_instance.node-dataset-body.widget|weight"] = 2;
  $overrides["field_instance.node-dataset-field_additional_info.display|default|settings|style"] = 'inline';
  $overrides["field_instance.node-dataset-field_additional_info.display|default|settings|table"]["DELETED"] = TRUE;
  $overrides["field_instance.node-dataset-field_additional_info.display|default|type"] = 'double_field_unformatted_list';
  $overrides["field_instance.node-dataset-field_additional_info.display|teaser|weight"] = 13;
  $overrides["field_instance.node-dataset-field_additional_info.label"] = 'Дополнительная информация';
  $overrides["field_instance.node-dataset-field_additional_info.widget|weight"] = 22;
  $overrides["field_instance.node-dataset-field_author.default_value|0"] = array(
    'value' => 'http://',
  );
  $overrides["field_instance.node-dataset-field_author.description"] = 'Источник информации';
  $overrides["field_instance.node-dataset-field_author.display|teaser|weight"] = 22;
  $overrides["field_instance.node-dataset-field_author.label"] = 'Источник';
  $overrides["field_instance.node-dataset-field_author.widget|settings|size"] = 120;
  $overrides["field_instance.node-dataset-field_contact_email.display|teaser|weight"] = 15;
  $overrides["field_instance.node-dataset-field_contact_email.label"] = 'Контактный Email';
  $overrides["field_instance.node-dataset-field_contact_email.widget|weight"] = 20;
  $overrides["field_instance.node-dataset-field_contact_name.display|teaser|weight"] = 19;
  $overrides["field_instance.node-dataset-field_contact_name.label"] = 'Контактное имя';
  $overrides["field_instance.node-dataset-field_contact_name.widget|weight"] = 19;
  $overrides["field_instance.node-dataset-field_data_dictionary.display|teaser|weight"] = 16;
  $overrides["field_instance.node-dataset-field_data_dictionary.widget|weight"] = 18;
  $overrides["field_instance.node-dataset-field_frequency.description"] = 'Частота, с которой публикуется набор данных. Смотрите <a href="http://www.w3.org/TR/vocab-dcat/#Property:dataset_frequency">Ссылку</a> для информации.';
  $overrides["field_instance.node-dataset-field_frequency.display|teaser|weight"] = 17;
  $overrides["field_instance.node-dataset-field_frequency.label"] = 'Частота';
  $overrides["field_instance.node-dataset-field_granularity.display|teaser|weight"] = 18;
  $overrides["field_instance.node-dataset-field_granularity.label"] = 'Гранулярность';
  $overrides["field_instance.node-dataset-field_granularity.widget|weight"] = 17;
  $overrides["field_instance.node-dataset-field_license.description"] = 'Определение лицензий и дополнительная информация могут быть найдены на сайте <a href="http://opendefinition.org">opendefinition.org</a>';
  $overrides["field_instance.node-dataset-field_license.display|teaser|weight"] = 21;
  $overrides["field_instance.node-dataset-field_license.label"] = 'Лицензия';
  $overrides["field_instance.node-dataset-field_license.widget|settings|available_options"] = 'cc-by|Creative Commons Attribution
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
      uk-ogl|UK Open Government Licence (OGL)';
  $overrides["field_instance.node-dataset-field_license.widget|weight"] = 6;
  $overrides["field_instance.node-dataset-field_public_access_level.display|teaser|weight"] = 14;
  $overrides["field_instance.node-dataset-field_public_access_level.label"] = 'Уровень доступа';
  $overrides["field_instance.node-dataset-field_public_access_level.widget|weight"] = 21;
  $overrides["field_instance.node-dataset-field_related_content.description"] = 'Внутренняя или внешняя ссылка которая обеспечивает дополнительную информацию по набору данных.';
  $overrides["field_instance.node-dataset-field_related_content.display|teaser|weight"] = 8;
  $overrides["field_instance.node-dataset-field_related_content.label"] = 'Похожие материалы';
  $overrides["field_instance.node-dataset-field_related_content.widget|weight"] = 24;
  $overrides["field_instance.node-dataset-field_resources.display|teaser|weight"] = 7;
  $overrides["field_instance.node-dataset-field_resources.label"] = 'Ресурсы';
  $overrides["field_instance.node-dataset-field_resources.widget|weight"] = 23;
  $overrides["field_instance.node-dataset-field_spatial.display|teaser|weight"] = 6;
  $overrides["field_instance.node-dataset-field_spatial.label"] = 'Пространственный (географический) охват';
  $overrides["field_instance.node-dataset-field_spatial_geographical_cover.display|teaser|weight"] = 9;
  $overrides["field_instance.node-dataset-field_tags.display|teaser|label"] = 'hidden';
  $overrides["field_instance.node-dataset-field_tags.display|teaser|weight"] = 5;
  $overrides["field_instance.node-dataset-field_tags.label"] = 'Тэги';
  $overrides["field_instance.node-dataset-field_tags.widget|settings|delimiter"] = '';
  $overrides["field_instance.node-dataset-field_tags.widget|weight"] = 4;
  $overrides["field_instance.node-dataset-field_temporal_coverage.description"] = 'Временной период который охватывает набор данных. Смотри <a href="http://www.w3.org/TR/vocab-dcat/#Property:dataset_temporal">ссылку</a> для подробной информации.';
  $overrides["field_instance.node-dataset-field_temporal_coverage.display|teaser|weight"] = 10;
  $overrides["field_instance.node-dataset-field_temporal_coverage.label"] = 'Временной охват';
  $overrides["field_instance.node-dataset-field_temporal_coverage.widget|weight"] = 16;
  $overrides["field_instance.node-resource-body.label"] = 'Описание';
  $overrides["field_instance.node-resource-field_dataset_ref.label"] = 'Набор данных';
  $overrides["field_instance.node-resource-field_format.label"] = 'Формат';
  $overrides["field_instance.node-resource-field_format.widget|settings|apply_chosen"]["DELETED"] = TRUE;
  $overrides["field_instance.node-resource-field_format.widget|settings|autocomplete_path"]["DELETED"] = TRUE;
  $overrides["field_instance.node-resource-field_format.widget|settings|delimiter"] = '';
  $overrides["field_instance.node-resource-field_format.widget|settings|limit"] = 10;
  $overrides["field_instance.node-resource-field_format.widget|settings|min_length"] = 0;
  $overrides["field_instance.node-resource-field_format.widget|settings|mode"]["DELETED"] = TRUE;
  $overrides["field_instance.node-resource-field_link_remote_file.settings|file_extensions"] = 'csv html xls json xlsx doc rdf txt jpg png gif tiff pdf odf ods odt tsv geojson xml zip tif';
  $overrides["field_instance.node-resource-field_upload.settings|file_directory"] = 'resources';
  $overrides["field_instance.node-resource-field_upload.settings|file_extensions"] = 'kml csv html xls json xlsx doc rdf txt jpg jpeg png gif tiff tif pdf odf ods odt tsv geojson xml zip';

  // Exported overrides for: node

  // Exported overrides for: taxonomy
  $overrides["taxonomy.format.i18n_mode"] = 0;
  $overrides["taxonomy.format.language"] = 'und';
  $overrides["taxonomy.format.name"] = 'Формат';
  $overrides["taxonomy.tags.description"] = 'Тэги в свободной форме';
  $overrides["taxonomy.tags.i18n_mode"] = 0;
  $overrides["taxonomy.tags.language"] = 'und';
  $overrides["taxonomy.tags.name"] = 'Тэги';

  // Exported overrides for: variable
  $overrides["variable.field_bundle_settings_node__dataset.value|extra_fields|display|identifier|teaser"] = array(
    'weight' => 0,
    'visible' => TRUE,
  );
  $overrides["variable.field_bundle_settings_node__dataset.value|extra_fields|display|modified_date|teaser"] = array(
    'weight' => 2,
    'visible' => TRUE,
  );
  $overrides["variable.field_bundle_settings_node__dataset.value|extra_fields|display|release_date|teaser"] = array(
    'weight' => 3,
    'visible' => TRUE,
  );
  $overrides["variable.field_bundle_settings_node__dataset.value|extra_fields|display|resources|teaser|weight"] = 1;
  $overrides["variable.field_bundle_settings_node__dataset.value|extra_fields|form|metatags"] = array(
    'weight' => 9,
  );

 return $overrides;
}
