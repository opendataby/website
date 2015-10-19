<?php
$this->setAuthor ('Igor Kandyba');
$this->setDescription ('Install opendata_dataset feature.');

$this->setupModules(array(
  'feature_opendata_dataset',
));

features_revert_module('dkan_dataset');

$this->finished();
