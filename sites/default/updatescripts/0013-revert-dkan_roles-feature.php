<?php
$this->setAuthor ('Igor Kandyba');
$this->setDescription ('Revert dkan_roles feature.');

$this->setupModules(array(
  'dkan_data_story_storyteller_role',
));

features_revert_module('feature_opendata_roles_perms');
features_revert_module('dkan_sitewide_roles_perms');

$this->unsetupModules(array(
  'dkan_sitewide_demo_front',
));

$this->finished();
