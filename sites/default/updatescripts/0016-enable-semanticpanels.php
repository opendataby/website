<?php
$this->setAuthor ('Yahor Malshewski');
$this->setDescription ('Install semantic_panels module');

$this->setupModules(array(
  'semantic_panels',
));

$this->unsetupModules(array(
  'feature_opendata_voting',
));

$this->finished();
