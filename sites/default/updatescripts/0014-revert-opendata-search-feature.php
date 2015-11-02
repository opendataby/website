<?php
$this->setAuthor ('Igor Kandyba');
$this->setDescription ('Revert opendata_search features.');

features_revert_module('dkan_sitewide_search_db');
features_revert_module('feature_opendata_search');

$this->finished();
