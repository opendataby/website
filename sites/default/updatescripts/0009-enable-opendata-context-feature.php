<?php
$this->setAuthor ('Igor Kandyba');
$this->setDescription ('Install opendata_context feature.');

$this->setupModules(array(
  'feature_opendata_context',
));

features_revert_module('dkan_sitewide_context');

$this->finished();
