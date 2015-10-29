<?php
$this->setAuthor ('Igor Kandyba');
$this->setDescription ('Revert open_data_schema_map_dkan');

features_revert(array('open_data_schema_map_dkan' => array('open_data_schema_apis')));

$this->finished();
