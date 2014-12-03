<?php
/**
 * @file
 * bsf_keuangan.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function bsf_keuangan_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'bsf_keuangan_node_view';
  $context->description = '';
  $context->tag = 'BSF Keuangan';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'bsf_keuangan' => 'bsf_keuangan',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-bsf_keuangan-block_1' => array(
          'module' => 'views',
          'delta' => 'bsf_keuangan-block_1',
          'region' => 'content',
          'weight' => '1',
        ),
        'views-bsf_keuangan-block_2' => array(
          'module' => 'views',
          'delta' => 'bsf_keuangan-block_2',
          'region' => 'content',
          'weight' => '2',
        ),
        'views-bsf_keuangan-block_3' => array(
          'module' => 'views',
          'delta' => 'bsf_keuangan-block_3',
          'region' => 'content',
          'weight' => '3',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('BSF Keuangan');
  $export['bsf_keuangan_node_view'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'bsf_mahasiswa_node_view';
  $context->description = '';
  $context->tag = 'BSF Keuangan';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'bsf_mahasiswa' => 'bsf_mahasiswa',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-bsf_keuangan_semester-block_1' => array(
          'module' => 'views',
          'delta' => 'bsf_keuangan_semester-block_1',
          'region' => 'content',
          'weight' => '1',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('BSF Keuangan');
  $export['bsf_mahasiswa_node_view'] = $context;

  return $export;
}
