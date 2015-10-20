<?php
$this->setAuthor ('Igor Kandyba');
$this->setDescription ('Install opendata_search feature.');

$this->setupModules(array(
  'feature_opendata_search',
));

features_revert_module('dkan_sitewide_search_db');

$this->finished();
