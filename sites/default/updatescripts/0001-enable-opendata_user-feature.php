<?php
$this->setAuthor ('Igor Kandyba');
$this->setDescription ('Install opendata_user feature.');

$this->setupModules(array(
  'feature_opendata_user',
));

$this->finished();
