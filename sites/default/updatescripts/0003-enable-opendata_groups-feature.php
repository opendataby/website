<?php
$this->setAuthor ('Igor Kandyba');
$this->setDescription ('Install opendata_groups feature.');

$this->setupModules(array(
  'feature_opendata_groups',
));

$this->finished();
