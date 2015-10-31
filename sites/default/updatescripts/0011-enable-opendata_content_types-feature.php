<?php
$this->setAuthor ('Igor Kandyba');
$this->setDescription ('Install opendata_content_types feature.');

$this->setupModules(array(
  'opendata_dataset_content_types',
));

features_revert_module('dkan_dataset_content_types');

$this->finished();
