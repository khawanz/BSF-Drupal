<?php
/**
 * @file
 * bsf_keuangan.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function bsf_keuangan_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'bsf_keuangan';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'BSF Keuangan';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Pembayaran Komponen';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create bsf_keuangan content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'counter' => 'counter',
    'field_bsf_komponen_nominal' => 'field_bsf_komponen_nominal',
    'field_bsf_pembayaran' => 'field_bsf_pembayaran',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'counter' => array(
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'field_bsf_komponen_nominal' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'field_bsf_pembayaran' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-right',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['totals_row_position'] = array(
    0 => 0,
    1 => 0,
    2 => '2',
  );
  /* Relationship: Field collection item: Entity with the Pembayaran Komponen (field_bsf_pembayaran_komponen) */
  $handler->display->display_options['relationships']['field_bsf_pembayaran_komponen_node']['id'] = 'field_bsf_pembayaran_komponen_node';
  $handler->display->display_options['relationships']['field_bsf_pembayaran_komponen_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_bsf_pembayaran_komponen_node']['field'] = 'field_bsf_pembayaran_komponen_node';
  /* Field: Global: View result counter */
  $handler->display->display_options['fields']['counter']['id'] = 'counter';
  $handler->display->display_options['fields']['counter']['table'] = 'views';
  $handler->display->display_options['fields']['counter']['field'] = 'counter';
  $handler->display->display_options['fields']['counter']['label'] = 'No.';
  $handler->display->display_options['fields']['counter']['counter_start'] = '1';
  /* Field: Field collection item: Komponen */
  $handler->display->display_options['fields']['field_bsf_komponen_nominal']['id'] = 'field_bsf_komponen_nominal';
  $handler->display->display_options['fields']['field_bsf_komponen_nominal']['table'] = 'field_data_field_bsf_komponen_nominal';
  $handler->display->display_options['fields']['field_bsf_komponen_nominal']['field'] = 'field_bsf_komponen_nominal';
  $handler->display->display_options['fields']['field_bsf_komponen_nominal']['settings'] = array(
    'link' => 0,
  );
  /* Field: Field collection item: Pembayaran */
  $handler->display->display_options['fields']['field_bsf_pembayaran']['id'] = 'field_bsf_pembayaran';
  $handler->display->display_options['fields']['field_bsf_pembayaran']['table'] = 'field_data_field_bsf_pembayaran';
  $handler->display->display_options['fields']['field_bsf_pembayaran']['field'] = 'field_bsf_pembayaran';
  $handler->display->display_options['fields']['field_bsf_pembayaran']['label'] = 'Pembayaran (Rupiah)';
  $handler->display->display_options['fields']['field_bsf_pembayaran']['settings'] = array(
    'thousand_separator' => '.',
    'decimal_separator' => ',',
    'scale' => '0',
    'prefix_suffix' => 0,
  );
  /* Sort criterion: Field collection item: Komponen (field_bsf_komponen_nominal) */
  $handler->display->display_options['sorts']['field_bsf_komponen_nominal_target_id']['id'] = 'field_bsf_komponen_nominal_target_id';
  $handler->display->display_options['sorts']['field_bsf_komponen_nominal_target_id']['table'] = 'field_data_field_bsf_komponen_nominal';
  $handler->display->display_options['sorts']['field_bsf_komponen_nominal_target_id']['field'] = 'field_bsf_komponen_nominal_target_id';
  /* Sort criterion: Field collection item: Field collection item ID */
  $handler->display->display_options['sorts']['item_id']['id'] = 'item_id';
  $handler->display->display_options['sorts']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['sorts']['item_id']['field'] = 'item_id';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_bsf_pembayaran_komponen_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'bsf_keuangan' => 'bsf_keuangan',
  );
  $handler->display->display_options['arguments']['nid']['validate_options']['access'] = TRUE;
  /* Filter criterion: Field collection item: Field name */
  $handler->display->display_options['filters']['field_name']['id'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['table'] = 'field_collection_item';
  $handler->display->display_options['filters']['field_name']['field'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['value'] = array(
    'field_bsf_pembayaran_komponen' => 'field_bsf_pembayaran_komponen',
  );

  /* Display: Block Pembayaran Komponen */
  $handler = $view->new_display('block', 'Block Pembayaran Komponen', 'block_1');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_bsf_pembayaran_komponen_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'bsf_keuangan' => 'bsf_keuangan',
  );
  $handler->display->display_options['arguments']['nid']['validate_options']['access'] = TRUE;

  /* Display: Block Approval Role Staff */
  $handler = $view->new_display('block', 'Block Approval Role Staff', 'block_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Staff Approval';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nothing' => 'nothing',
    'nothing_1' => 'nothing_1',
    'nothing_2' => 'nothing_2',
    'field_bsf_approval_krs_1' => 'nothing',
    'field_bsf_approval_uts_1' => 'nothing',
    'field_bsf_approval_uas_1' => 'nothing',
    'field_bsf_approval_krs' => 'nothing_1',
    'field_bsf_approval_uts' => 'nothing_1',
    'field_bsf_approval_uas' => 'nothing_1',
    'field_bsf_approval_krs_message' => 'nothing_2',
    'field_bsf_approval_uts_message' => 'nothing_2',
    'field_bsf_approval_uas_message' => 'nothing_2',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nothing' => array(
      'align' => '',
      'separator' => '<br/>',
      'empty_column' => 0,
    ),
    'nothing_1' => array(
      'align' => '',
      'separator' => '<br/>',
      'empty_column' => 0,
    ),
    'nothing_2' => array(
      'align' => '',
      'separator' => '<br/>',
      'empty_column' => 0,
    ),
    'field_bsf_approval_krs_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_uts_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_uas_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_krs' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_uts' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_uas' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_krs_message' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_uts_message' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_uas_message' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Field collection item: Entity with the Approval Role Staff (field_bsf_approval_role_staff) */
  $handler->display->display_options['relationships']['field_bsf_approval_role_staff_node']['id'] = 'field_bsf_approval_role_staff_node';
  $handler->display->display_options['relationships']['field_bsf_approval_role_staff_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_bsf_approval_role_staff_node']['field'] = 'field_bsf_approval_role_staff_node';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Aplikasi';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'Status';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['label'] = 'Catatan';
  /* Field: Field collection item: KRS Approval */
  $handler->display->display_options['fields']['field_bsf_approval_krs_1']['id'] = 'field_bsf_approval_krs_1';
  $handler->display->display_options['fields']['field_bsf_approval_krs_1']['table'] = 'field_data_field_bsf_approval_krs';
  $handler->display->display_options['fields']['field_bsf_approval_krs_1']['field'] = 'field_bsf_approval_krs';
  $handler->display->display_options['fields']['field_bsf_approval_krs_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_bsf_approval_krs_1']['alter']['text'] = 'KRS';
  /* Field: Field collection item: UTS Approval */
  $handler->display->display_options['fields']['field_bsf_approval_uts_1']['id'] = 'field_bsf_approval_uts_1';
  $handler->display->display_options['fields']['field_bsf_approval_uts_1']['table'] = 'field_data_field_bsf_approval_uts';
  $handler->display->display_options['fields']['field_bsf_approval_uts_1']['field'] = 'field_bsf_approval_uts';
  $handler->display->display_options['fields']['field_bsf_approval_uts_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_bsf_approval_uts_1']['alter']['text'] = 'UTS';
  /* Field: Field collection item: UAS Approval */
  $handler->display->display_options['fields']['field_bsf_approval_uas_1']['id'] = 'field_bsf_approval_uas_1';
  $handler->display->display_options['fields']['field_bsf_approval_uas_1']['table'] = 'field_data_field_bsf_approval_uas';
  $handler->display->display_options['fields']['field_bsf_approval_uas_1']['field'] = 'field_bsf_approval_uas';
  $handler->display->display_options['fields']['field_bsf_approval_uas_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_bsf_approval_uas_1']['alter']['text'] = 'UAS';
  /* Field: Field collection item: KRS Approval */
  $handler->display->display_options['fields']['field_bsf_approval_krs']['id'] = 'field_bsf_approval_krs';
  $handler->display->display_options['fields']['field_bsf_approval_krs']['table'] = 'field_data_field_bsf_approval_krs';
  $handler->display->display_options['fields']['field_bsf_approval_krs']['field'] = 'field_bsf_approval_krs';
  $handler->display->display_options['fields']['field_bsf_approval_krs']['label'] = 'KRS';
  /* Field: Field collection item: UTS Approval */
  $handler->display->display_options['fields']['field_bsf_approval_uts']['id'] = 'field_bsf_approval_uts';
  $handler->display->display_options['fields']['field_bsf_approval_uts']['table'] = 'field_data_field_bsf_approval_uts';
  $handler->display->display_options['fields']['field_bsf_approval_uts']['field'] = 'field_bsf_approval_uts';
  $handler->display->display_options['fields']['field_bsf_approval_uts']['label'] = 'UTS';
  /* Field: Field collection item: UAS Approval */
  $handler->display->display_options['fields']['field_bsf_approval_uas']['id'] = 'field_bsf_approval_uas';
  $handler->display->display_options['fields']['field_bsf_approval_uas']['table'] = 'field_data_field_bsf_approval_uas';
  $handler->display->display_options['fields']['field_bsf_approval_uas']['field'] = 'field_bsf_approval_uas';
  $handler->display->display_options['fields']['field_bsf_approval_uas']['label'] = 'UAS';
  /* Field: Field collection item: KRS Approval Message */
  $handler->display->display_options['fields']['field_bsf_approval_krs_message']['id'] = 'field_bsf_approval_krs_message';
  $handler->display->display_options['fields']['field_bsf_approval_krs_message']['table'] = 'field_data_field_bsf_approval_krs_message';
  $handler->display->display_options['fields']['field_bsf_approval_krs_message']['field'] = 'field_bsf_approval_krs_message';
  $handler->display->display_options['fields']['field_bsf_approval_krs_message']['label'] = 'KRS Message';
  $handler->display->display_options['fields']['field_bsf_approval_krs_message']['empty'] = '-';
  $handler->display->display_options['fields']['field_bsf_approval_krs_message']['hide_alter_empty'] = FALSE;
  /* Field: Field collection item: UTS Approval Message */
  $handler->display->display_options['fields']['field_bsf_approval_uts_message']['id'] = 'field_bsf_approval_uts_message';
  $handler->display->display_options['fields']['field_bsf_approval_uts_message']['table'] = 'field_data_field_bsf_approval_uts_message';
  $handler->display->display_options['fields']['field_bsf_approval_uts_message']['field'] = 'field_bsf_approval_uts_message';
  $handler->display->display_options['fields']['field_bsf_approval_uts_message']['label'] = 'UTS Message';
  $handler->display->display_options['fields']['field_bsf_approval_uts_message']['empty'] = '-';
  $handler->display->display_options['fields']['field_bsf_approval_uts_message']['hide_alter_empty'] = FALSE;
  /* Field: Field collection item: UAS Approval Message */
  $handler->display->display_options['fields']['field_bsf_approval_uas_message']['id'] = 'field_bsf_approval_uas_message';
  $handler->display->display_options['fields']['field_bsf_approval_uas_message']['table'] = 'field_data_field_bsf_approval_uas_message';
  $handler->display->display_options['fields']['field_bsf_approval_uas_message']['field'] = 'field_bsf_approval_uas_message';
  $handler->display->display_options['fields']['field_bsf_approval_uas_message']['label'] = 'UAS Message';
  $handler->display->display_options['fields']['field_bsf_approval_uas_message']['empty'] = '-';
  $handler->display->display_options['fields']['field_bsf_approval_uas_message']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_bsf_approval_role_staff_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'bsf_keuangan' => 'bsf_keuangan',
  );
  $handler->display->display_options['arguments']['nid']['validate_options']['access'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Field collection item: Field name */
  $handler->display->display_options['filters']['field_name']['id'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['table'] = 'field_collection_item';
  $handler->display->display_options['filters']['field_name']['field'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['value'] = array(
    'field_bsf_approval_role_staff' => 'field_bsf_approval_role_staff',
  );

  /* Display: Block Approval Role Manager */
  $handler = $view->new_display('block', 'Block Approval Role Manager', 'block_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Manager Approval';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nothing' => 'nothing',
    'nothing_1' => 'nothing_1',
    'nothing_2' => 'nothing_2',
    'field_bsf_approval_krs_1' => 'nothing',
    'field_bsf_approval_uts_1' => 'nothing',
    'field_bsf_approval_uas_1' => 'nothing',
    'field_bsf_approval_krs' => 'nothing_1',
    'field_bsf_approval_uts' => 'nothing_1',
    'field_bsf_approval_uas' => 'nothing_1',
    'field_bsf_approval_krs_message' => 'nothing_2',
    'field_bsf_approval_uts_message' => 'nothing_2',
    'field_bsf_approval_uas_message' => 'nothing_2',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nothing' => array(
      'align' => '',
      'separator' => '<br/>',
      'empty_column' => 0,
    ),
    'nothing_1' => array(
      'align' => '',
      'separator' => '<br/>',
      'empty_column' => 0,
    ),
    'nothing_2' => array(
      'align' => '',
      'separator' => '<br/>',
      'empty_column' => 0,
    ),
    'field_bsf_approval_krs_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_uts_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_uas_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_krs' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_uts' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_uas' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_krs_message' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_uts_message' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_bsf_approval_uas_message' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Field collection item: Entity with the Approval Role Manager (field_bsf_approval_role_manager) */
  $handler->display->display_options['relationships']['field_bsf_approval_role_manager_node']['id'] = 'field_bsf_approval_role_manager_node';
  $handler->display->display_options['relationships']['field_bsf_approval_role_manager_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_bsf_approval_role_manager_node']['field'] = 'field_bsf_approval_role_manager_node';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Aplikasi';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'Status';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['label'] = 'Catatan';
  /* Field: Field collection item: KRS Approval */
  $handler->display->display_options['fields']['field_bsf_approval_krs_1']['id'] = 'field_bsf_approval_krs_1';
  $handler->display->display_options['fields']['field_bsf_approval_krs_1']['table'] = 'field_data_field_bsf_approval_krs';
  $handler->display->display_options['fields']['field_bsf_approval_krs_1']['field'] = 'field_bsf_approval_krs';
  $handler->display->display_options['fields']['field_bsf_approval_krs_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_bsf_approval_krs_1']['alter']['text'] = 'KRS';
  /* Field: Field collection item: UTS Approval */
  $handler->display->display_options['fields']['field_bsf_approval_uts_1']['id'] = 'field_bsf_approval_uts_1';
  $handler->display->display_options['fields']['field_bsf_approval_uts_1']['table'] = 'field_data_field_bsf_approval_uts';
  $handler->display->display_options['fields']['field_bsf_approval_uts_1']['field'] = 'field_bsf_approval_uts';
  $handler->display->display_options['fields']['field_bsf_approval_uts_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_bsf_approval_uts_1']['alter']['text'] = 'UTS';
  /* Field: Field collection item: UAS Approval */
  $handler->display->display_options['fields']['field_bsf_approval_uas_1']['id'] = 'field_bsf_approval_uas_1';
  $handler->display->display_options['fields']['field_bsf_approval_uas_1']['table'] = 'field_data_field_bsf_approval_uas';
  $handler->display->display_options['fields']['field_bsf_approval_uas_1']['field'] = 'field_bsf_approval_uas';
  $handler->display->display_options['fields']['field_bsf_approval_uas_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_bsf_approval_uas_1']['alter']['text'] = 'UAS';
  /* Field: Field collection item: KRS Approval */
  $handler->display->display_options['fields']['field_bsf_approval_krs']['id'] = 'field_bsf_approval_krs';
  $handler->display->display_options['fields']['field_bsf_approval_krs']['table'] = 'field_data_field_bsf_approval_krs';
  $handler->display->display_options['fields']['field_bsf_approval_krs']['field'] = 'field_bsf_approval_krs';
  $handler->display->display_options['fields']['field_bsf_approval_krs']['label'] = 'KRS';
  /* Field: Field collection item: UTS Approval */
  $handler->display->display_options['fields']['field_bsf_approval_uts']['id'] = 'field_bsf_approval_uts';
  $handler->display->display_options['fields']['field_bsf_approval_uts']['table'] = 'field_data_field_bsf_approval_uts';
  $handler->display->display_options['fields']['field_bsf_approval_uts']['field'] = 'field_bsf_approval_uts';
  $handler->display->display_options['fields']['field_bsf_approval_uts']['label'] = 'UTS';
  /* Field: Field collection item: UAS Approval */
  $handler->display->display_options['fields']['field_bsf_approval_uas']['id'] = 'field_bsf_approval_uas';
  $handler->display->display_options['fields']['field_bsf_approval_uas']['table'] = 'field_data_field_bsf_approval_uas';
  $handler->display->display_options['fields']['field_bsf_approval_uas']['field'] = 'field_bsf_approval_uas';
  $handler->display->display_options['fields']['field_bsf_approval_uas']['label'] = 'UAS';
  /* Field: Field collection item: KRS Approval Message */
  $handler->display->display_options['fields']['field_bsf_approval_krs_message']['id'] = 'field_bsf_approval_krs_message';
  $handler->display->display_options['fields']['field_bsf_approval_krs_message']['table'] = 'field_data_field_bsf_approval_krs_message';
  $handler->display->display_options['fields']['field_bsf_approval_krs_message']['field'] = 'field_bsf_approval_krs_message';
  $handler->display->display_options['fields']['field_bsf_approval_krs_message']['label'] = 'KRS Message';
  $handler->display->display_options['fields']['field_bsf_approval_krs_message']['empty'] = '-';
  $handler->display->display_options['fields']['field_bsf_approval_krs_message']['hide_alter_empty'] = FALSE;
  /* Field: Field collection item: UTS Approval Message */
  $handler->display->display_options['fields']['field_bsf_approval_uts_message']['id'] = 'field_bsf_approval_uts_message';
  $handler->display->display_options['fields']['field_bsf_approval_uts_message']['table'] = 'field_data_field_bsf_approval_uts_message';
  $handler->display->display_options['fields']['field_bsf_approval_uts_message']['field'] = 'field_bsf_approval_uts_message';
  $handler->display->display_options['fields']['field_bsf_approval_uts_message']['label'] = 'UTS Message';
  $handler->display->display_options['fields']['field_bsf_approval_uts_message']['empty'] = '-';
  $handler->display->display_options['fields']['field_bsf_approval_uts_message']['hide_alter_empty'] = FALSE;
  /* Field: Field collection item: UAS Approval Message */
  $handler->display->display_options['fields']['field_bsf_approval_uas_message']['id'] = 'field_bsf_approval_uas_message';
  $handler->display->display_options['fields']['field_bsf_approval_uas_message']['table'] = 'field_data_field_bsf_approval_uas_message';
  $handler->display->display_options['fields']['field_bsf_approval_uas_message']['field'] = 'field_bsf_approval_uas_message';
  $handler->display->display_options['fields']['field_bsf_approval_uas_message']['label'] = 'UAS Message';
  $handler->display->display_options['fields']['field_bsf_approval_uas_message']['empty'] = '-';
  $handler->display->display_options['fields']['field_bsf_approval_uas_message']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_bsf_approval_role_manager_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'bsf_keuangan' => 'bsf_keuangan',
  );
  $handler->display->display_options['arguments']['nid']['validate_options']['access'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Field collection item: Field name */
  $handler->display->display_options['filters']['field_name']['id'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['table'] = 'field_collection_item';
  $handler->display->display_options['filters']['field_name']['field'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['value'] = array(
    'field_bsf_approval_role_manager' => 'field_bsf_approval_role_manager',
  );
  $export['bsf_keuangan'] = $view;

  $view = new view();
  $view->name = 'bsf_keuangan_semester';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'BSF Keuangan - Semester';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Keuangan Semester';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create bsf_keuangan content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'views_aggregator';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_bsf_semester_akademik' => 'field_bsf_semester_akademik',
    'field_bsf_pembayaran' => 'field_bsf_pembayaran',
    'view_node' => 'view_node',
    'edit_node' => 'edit_node',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_bsf_semester_akademik' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'field_bsf_pembayaran' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-right',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 1,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'view_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
    'nothing' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
      'has_aggr' => 0,
      'aggr' => array(
        'views_aggregator_first' => 'views_aggregator_first',
      ),
      'aggr_par' => '',
      'has_aggr_column' => 0,
      'aggr_column' => 'views_aggregator_sum',
      'aggr_par_column' => '',
    ),
  );
  $handler->display->display_options['style_options']['totals_per_page'] = '1';
  $handler->display->display_options['style_options']['totals_row_position'] = array(
    0 => 0,
    1 => 0,
    2 => '2',
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_bsf_komponen_target_id']['id'] = 'field_bsf_komponen_target_id';
  $handler->display->display_options['relationships']['field_bsf_komponen_target_id']['table'] = 'field_data_field_bsf_komponen';
  $handler->display->display_options['relationships']['field_bsf_komponen_target_id']['field'] = 'field_bsf_komponen_target_id';
  /* Relationship: Content: Pembayaran Komponen (field_bsf_pembayaran_komponen) */
  $handler->display->display_options['relationships']['field_bsf_pembayaran_komponen_value']['id'] = 'field_bsf_pembayaran_komponen_value';
  $handler->display->display_options['relationships']['field_bsf_pembayaran_komponen_value']['table'] = 'field_data_field_bsf_pembayaran_komponen';
  $handler->display->display_options['relationships']['field_bsf_pembayaran_komponen_value']['field'] = 'field_bsf_pembayaran_komponen_value';
  $handler->display->display_options['relationships']['field_bsf_pembayaran_komponen_value']['delta'] = '-1';
  /* Field: Content: Semester Akademik */
  $handler->display->display_options['fields']['field_bsf_semester_akademik']['id'] = 'field_bsf_semester_akademik';
  $handler->display->display_options['fields']['field_bsf_semester_akademik']['table'] = 'field_data_field_bsf_semester_akademik';
  $handler->display->display_options['fields']['field_bsf_semester_akademik']['field'] = 'field_bsf_semester_akademik';
  $handler->display->display_options['fields']['field_bsf_semester_akademik']['settings'] = array(
    'link' => 0,
  );
  /* Field: SUM(Field collection item: Pembayaran) */
  $handler->display->display_options['fields']['field_bsf_pembayaran']['id'] = 'field_bsf_pembayaran';
  $handler->display->display_options['fields']['field_bsf_pembayaran']['table'] = 'field_data_field_bsf_pembayaran';
  $handler->display->display_options['fields']['field_bsf_pembayaran']['field'] = 'field_bsf_pembayaran';
  $handler->display->display_options['fields']['field_bsf_pembayaran']['relationship'] = 'field_bsf_pembayaran_komponen_value';
  $handler->display->display_options['fields']['field_bsf_pembayaran']['group_type'] = 'sum';
  $handler->display->display_options['fields']['field_bsf_pembayaran']['label'] = 'Pembayaran (Rupiah)';
  $handler->display->display_options['fields']['field_bsf_pembayaran']['settings'] = array(
    'thousand_separator' => '.',
    'decimal_separator' => ',',
    'scale' => '0',
    'prefix_suffix' => 0,
  );
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = 'View link';
  $handler->display->display_options['fields']['view_node']['exclude'] = TRUE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['exclude'] = TRUE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Action';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[view_node] | [edit_node]';
  /* Sort criterion: Content: Semester Akademik (field_bsf_semester_akademik) */
  $handler->display->display_options['sorts']['field_bsf_semester_akademik_target_id']['id'] = 'field_bsf_semester_akademik_target_id';
  $handler->display->display_options['sorts']['field_bsf_semester_akademik_target_id']['table'] = 'field_data_field_bsf_semester_akademik';
  $handler->display->display_options['sorts']['field_bsf_semester_akademik_target_id']['field'] = 'field_bsf_semester_akademik_target_id';
  $handler->display->display_options['sorts']['field_bsf_semester_akademik_target_id']['order'] = 'DESC';
  /* Contextual filter: Content: Mahasiswa (field_bsf_mahasiswa) */
  $handler->display->display_options['arguments']['field_bsf_mahasiswa_target_id']['id'] = 'field_bsf_mahasiswa_target_id';
  $handler->display->display_options['arguments']['field_bsf_mahasiswa_target_id']['table'] = 'field_data_field_bsf_mahasiswa';
  $handler->display->display_options['arguments']['field_bsf_mahasiswa_target_id']['field'] = 'field_bsf_mahasiswa_target_id';
  $handler->display->display_options['arguments']['field_bsf_mahasiswa_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_bsf_mahasiswa_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_bsf_mahasiswa_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_bsf_mahasiswa_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_bsf_mahasiswa_target_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'bsf_keuangan' => 'bsf_keuangan',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $export['bsf_keuangan_semester'] = $view;

  return $export;
}
