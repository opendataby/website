<?php
$this->setAuthor ('Igor Kandyba');
$this->setDescription ('Install opendata_sitewide feature.');

$this->setupModules(array(
  'opendata_sitewide',
));

features_revert_module('dkan_sitewide');

$this->finished();
