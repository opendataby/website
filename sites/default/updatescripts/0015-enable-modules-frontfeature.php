<?php
$this->setAuthor ('Yahor Malshewski');
$this->setDescription ('Install feature_opendata_front feature and some modules.');

$this->setupModules(array(
  'views_slideshow',
  'views_slideshow_cycle',
  'vscc',
  'feature_opendata_front',
));


$this->finished();
