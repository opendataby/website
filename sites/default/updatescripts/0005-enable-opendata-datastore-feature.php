<?php
$this->setAuthor ('Igor Kandyba');
$this->setDescription ('Install opendata_datastore feature.');

$this->setupModules(array(
  'feature_opendata_datastore',
));

$this->finished();
