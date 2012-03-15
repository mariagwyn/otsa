<?php
/**
 * @file
 * otsa_full_member_import.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function otsa_full_member_import_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
}
