<?php
/**
 * @file
 * otsa_full_member_import.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function otsa_full_member_import_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'full_member_import';
  $feeds_importer->config = array(
    'name' => 'Full Member Import',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'direct' => FALSE,
        'allowed_extensions' => 'txt csv tsv xml opml',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsUserProcessor',
      'config' => array(
        'roles' => array(
          6 => '6',
          10 => '10',
          3 => 0,
          4 => 0,
          5 => 0,
          7 => 0,
          8 => 0,
          9 => 0,
          11 => 0,
        ),
        'update_existing' => 1,
        'status' => '1',
        'mappings' => array(
          0 => array(
            'source' => 'name',
            'target' => 'name',
            'unique' => 0,
          ),
          1 => array(
            'source' => 'mail',
            'target' => 'mail',
            'unique' => 1,
          ),
          2 => array(
            'source' => 'created',
            'target' => 'created',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'LastName',
            'target' => 'field_name_last',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'FirstName',
            'target' => 'field_name_first',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'Middle',
            'target' => 'field_name_middle',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'Honorific',
            'target' => 'field_name_honorific',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'LocationName',
            'target' => 'locations:name',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'Address1',
            'target' => 'locations:street',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'Address2',
            'target' => 'locations:additional',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'City',
            'target' => 'locations:city',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'ST',
            'target' => 'locations:province',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'CODE',
            'target' => 'locations:postal_code',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'Country',
            'target' => 'locations:country',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'PrimaryPhone',
            'target' => 'locations:phone',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'FAX',
            'target' => 'locations:fax',
            'unique' => FALSE,
          ),
          16 => array(
            'source' => 'URLTitle',
            'target' => 'field_member_webs:title',
            'unique' => FALSE,
          ),
          17 => array(
            'source' => 'URL',
            'target' => 'field_member_webs:url',
            'unique' => FALSE,
          ),
        ),
        'defuse_mail' => 0,
        'input_format' => 'plain_text',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['full_member_import'] = $feeds_importer;

  return $export;
}
