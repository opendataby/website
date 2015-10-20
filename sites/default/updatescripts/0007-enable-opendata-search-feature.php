<?php
$this->setAuthor ('Igor Kandyba');
$this->setDescription ('Install dkan_sitewide_roles_perms feature.');

$this->setupModules(array(
  'feature_opendata_roles_perms',
));

features_revert_module('dkan_sitewide_roles_perms');

$this->finished();
