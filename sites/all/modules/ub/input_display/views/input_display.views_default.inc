<?php
/**
 * Implements hook_views_default_views().
 */
function input_display_views_default_views() {
$export = array();

$view = new view();
$view->name = 'view_laporan_pembayaran';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'node';
$view->human_name = 'View Laporan Pembayaran';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Laporan Pembayaran';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['pager']['options']['items_per_page'] = '0';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'counter' => 'counter',
  'field_bsf_nim' => 'field_bsf_nim',
  'field_bsf_nama' => 'field_bsf_nama',
  'title' => 'title',
  'title_1' => 'title_1',
  'field_bsf_pembayaran_komponen' => 'field_bsf_pembayaran_komponen',
  'field_bsf_approval_role_staff' => 'field_bsf_approval_role_staff',
  'changed' => 'changed',
);
$handler->display->display_options['style_options']['default'] = 'changed';
$handler->display->display_options['style_options']['info'] = array(
  'counter' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'field_bsf_nim' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'field_bsf_nama' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'title' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'title_1' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'field_bsf_pembayaran_komponen' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'field_bsf_approval_role_staff' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'changed' => array(
    'sortable' => 1,
    'default_sort_order' => 'desc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* Relationship: Entity Reference: Referenced Entity */
$handler->display->display_options['relationships']['field_bsf_mahasiswa_target_id']['id'] = 'field_bsf_mahasiswa_target_id';
$handler->display->display_options['relationships']['field_bsf_mahasiswa_target_id']['table'] = 'field_data_field_bsf_mahasiswa';
$handler->display->display_options['relationships']['field_bsf_mahasiswa_target_id']['field'] = 'field_bsf_mahasiswa_target_id';
/* Relationship: Entity Reference: Referenced Entity */
$handler->display->display_options['relationships']['field_bsf_program_studi_target_id']['id'] = 'field_bsf_program_studi_target_id';
$handler->display->display_options['relationships']['field_bsf_program_studi_target_id']['table'] = 'field_data_field_bsf_program_studi';
$handler->display->display_options['relationships']['field_bsf_program_studi_target_id']['field'] = 'field_bsf_program_studi_target_id';
$handler->display->display_options['relationships']['field_bsf_program_studi_target_id']['relationship'] = 'field_bsf_mahasiswa_target_id';
/* Relationship: Entity Reference: Referenced Entity */
$handler->display->display_options['relationships']['field_bsf_angkatan_target_id']['id'] = 'field_bsf_angkatan_target_id';
$handler->display->display_options['relationships']['field_bsf_angkatan_target_id']['table'] = 'field_data_field_bsf_angkatan';
$handler->display->display_options['relationships']['field_bsf_angkatan_target_id']['field'] = 'field_bsf_angkatan_target_id';
$handler->display->display_options['relationships']['field_bsf_angkatan_target_id']['relationship'] = 'field_bsf_mahasiswa_target_id';
/* Field: Global: View result counter */
$handler->display->display_options['fields']['counter']['id'] = 'counter';
$handler->display->display_options['fields']['counter']['table'] = 'views';
$handler->display->display_options['fields']['counter']['field'] = 'counter';
$handler->display->display_options['fields']['counter']['label'] = 'No.';
$handler->display->display_options['fields']['counter']['counter_start'] = '1';
/* Field: Content: NIM */
$handler->display->display_options['fields']['field_bsf_nim']['id'] = 'field_bsf_nim';
$handler->display->display_options['fields']['field_bsf_nim']['table'] = 'field_data_field_bsf_nim';
$handler->display->display_options['fields']['field_bsf_nim']['field'] = 'field_bsf_nim';
$handler->display->display_options['fields']['field_bsf_nim']['relationship'] = 'field_bsf_mahasiswa_target_id';
/* Field: Content: Nama */
$handler->display->display_options['fields']['field_bsf_nama']['id'] = 'field_bsf_nama';
$handler->display->display_options['fields']['field_bsf_nama']['table'] = 'field_data_field_bsf_nama';
$handler->display->display_options['fields']['field_bsf_nama']['field'] = 'field_bsf_nama';
$handler->display->display_options['fields']['field_bsf_nama']['relationship'] = 'field_bsf_mahasiswa_target_id';
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['relationship'] = 'field_bsf_program_studi_target_id';
$handler->display->display_options['fields']['title']['label'] = 'Program Studi';
$handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title_1']['id'] = 'title_1';
$handler->display->display_options['fields']['title_1']['table'] = 'node';
$handler->display->display_options['fields']['title_1']['field'] = 'title';
$handler->display->display_options['fields']['title_1']['relationship'] = 'field_bsf_angkatan_target_id';
$handler->display->display_options['fields']['title_1']['label'] = 'Angkatan';
$handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
/* Field: Content: Pembayaran Komponen */
$handler->display->display_options['fields']['field_bsf_pembayaran_komponen']['id'] = 'field_bsf_pembayaran_komponen';
$handler->display->display_options['fields']['field_bsf_pembayaran_komponen']['table'] = 'field_data_field_bsf_pembayaran_komponen';
$handler->display->display_options['fields']['field_bsf_pembayaran_komponen']['field'] = 'field_bsf_pembayaran_komponen';
$handler->display->display_options['fields']['field_bsf_pembayaran_komponen']['settings'] = array(
  'edit' => '',
  'delete' => '',
  'add' => '',
  'description' => 1,
  'view_mode' => 'full',
);
$handler->display->display_options['fields']['field_bsf_pembayaran_komponen']['delta_offset'] = '0';
/* Field: Content: Approval Role Staff */
$handler->display->display_options['fields']['field_bsf_approval_role_staff']['id'] = 'field_bsf_approval_role_staff';
$handler->display->display_options['fields']['field_bsf_approval_role_staff']['table'] = 'field_data_field_bsf_approval_role_staff';
$handler->display->display_options['fields']['field_bsf_approval_role_staff']['field'] = 'field_bsf_approval_role_staff';
$handler->display->display_options['fields']['field_bsf_approval_role_staff']['label'] = 'Approval';
$handler->display->display_options['fields']['field_bsf_approval_role_staff']['settings'] = array(
  'edit' => '',
  'delete' => '',
  'add' => '',
  'description' => 1,
  'view_mode' => 'full',
);
/* Field: Content: Updated date */
$handler->display->display_options['fields']['changed']['id'] = 'changed';
$handler->display->display_options['fields']['changed']['table'] = 'node';
$handler->display->display_options['fields']['changed']['field'] = 'changed';
$handler->display->display_options['fields']['changed']['label'] = 'Tanggal Input / Perubahan';
$handler->display->display_options['fields']['changed']['date_format'] = 'custom';
$handler->display->display_options['fields']['changed']['custom_date_format'] = 'd F Y  G:i';
/* Sort criterion: Content: Post date */
$handler->display->display_options['sorts']['created']['id'] = 'created';
$handler->display->display_options['sorts']['created']['table'] = 'node';
$handler->display->display_options['sorts']['created']['field'] = 'created';
$handler->display->display_options['sorts']['created']['order'] = 'DESC';
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
$handler->display->display_options['filters']['type']['group'] = 1;
/* Filter criterion: Content: Updated date */
$handler->display->display_options['filters']['changed']['id'] = 'changed';
$handler->display->display_options['filters']['changed']['table'] = 'node';
$handler->display->display_options['filters']['changed']['field'] = 'changed';
$handler->display->display_options['filters']['changed']['operator'] = '>=';
$handler->display->display_options['filters']['changed']['group'] = 1;
$handler->display->display_options['filters']['changed']['exposed'] = TRUE;
$handler->display->display_options['filters']['changed']['expose']['operator_id'] = 'changed_op';
$handler->display->display_options['filters']['changed']['expose']['label'] = 'Dari';
$handler->display->display_options['filters']['changed']['expose']['description'] = 'Format: tahun-bulan-hari. Contoh: 2014-01-31';
$handler->display->display_options['filters']['changed']['expose']['operator'] = 'changed_op';
$handler->display->display_options['filters']['changed']['expose']['identifier'] = 'changed';
$handler->display->display_options['filters']['changed']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
);
/* Filter criterion: Content: Updated date */
$handler->display->display_options['filters']['changed_1']['id'] = 'changed_1';
$handler->display->display_options['filters']['changed_1']['table'] = 'node';
$handler->display->display_options['filters']['changed_1']['field'] = 'changed';
$handler->display->display_options['filters']['changed_1']['operator'] = '<=';
$handler->display->display_options['filters']['changed_1']['group'] = 1;
$handler->display->display_options['filters']['changed_1']['exposed'] = TRUE;
$handler->display->display_options['filters']['changed_1']['expose']['operator_id'] = 'changed_1_op';
$handler->display->display_options['filters']['changed_1']['expose']['label'] = 'Sampai';
$handler->display->display_options['filters']['changed_1']['expose']['description'] = 'Format: tahun-bulan-hari. Contoh: 2014-01-31';
$handler->display->display_options['filters']['changed_1']['expose']['operator'] = 'changed_1_op';
$handler->display->display_options['filters']['changed_1']['expose']['identifier'] = 'changed_1';
$handler->display->display_options['filters']['changed_1']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
);
/* Filter criterion: Content: Title */
$handler->display->display_options['filters']['title']['id'] = 'title';
$handler->display->display_options['filters']['title']['table'] = 'node';
$handler->display->display_options['filters']['title']['field'] = 'title';
$handler->display->display_options['filters']['title']['relationship'] = 'field_bsf_program_studi_target_id';
$handler->display->display_options['filters']['title']['operator'] = 'contains';
$handler->display->display_options['filters']['title']['group'] = 1;
$handler->display->display_options['filters']['title']['exposed'] = TRUE;
$handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['label'] = 'Program Studi';
$handler->display->display_options['filters']['title']['expose']['description'] = 'Ketikkan sebagian program studi yang ingin ditampilkan';
$handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
$handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
);

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'laporan-pembayaran';
$export['view_laporan_pembayaran'] = $view;

return $export;

}