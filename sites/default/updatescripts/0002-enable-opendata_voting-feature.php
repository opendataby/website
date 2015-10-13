<?php
$this->setAuthor ('Igor Kandyba');
$this->setDescription ('Install opendata_voting feature.');

$this->setupModules(array(
  'feature_opendata_voting',
));

$this->finished();
