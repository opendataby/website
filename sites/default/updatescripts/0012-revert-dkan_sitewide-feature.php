<?php
$this->setAuthor ('Igor Kandyba');
$this->setDescription ('Revert dkan_sitewide feature.');

features_revert_module('dkan_sitewide');

$this->finished();
