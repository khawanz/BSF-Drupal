<?php
/**
 * @file
 * bsf_keuangan.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bsf_keuangan_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_views_api().
 */
function bsf_keuangan_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function bsf_keuangan_node_info() {
  $items = array(
    'bsf_keuangan' => array(
      'name' => t('10. Keuangan'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('YYSS - NIM'),
      'help' => '',
    ),
    'bsf_mahasiswa' => array(
      'name' => t('(system) 07. Mahasiswa'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('NIM - Nama'),
      'help' => '',
    ),
  );
  return $items;
}
