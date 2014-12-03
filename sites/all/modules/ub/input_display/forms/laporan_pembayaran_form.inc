<?php

function laporan_pembayaran_form($form, &$form_state){
    $form = array();
    
    require_once drupal_get_path('module', 'input_display').'/forms/input_pembayaran_form.inc';
    
    $laporan_pembayaran = variable_get('laporan_pembayaran');
    
    $form['node'] = array(
            '#tree' => TRUE,
          );
   $form['filter'] = array(
       '#title' => t('Filter'),
        '#type' => 'fieldset',
       '#collapsible' => TRUE,
       '#collapsed' => empty($laporan_pembayaran)? FALSE:TRUE,
    );
    
//    $semester_array = node_load_multiple(array(), array('type' => 'bsf_semester_akademik'));
//    usort($semester_array, "cmp");
//    $sta = array();
//    foreach($semester_array as $semester_node){
//        $sta[$semester_node->nid] = $semester_node->title;
//        $default_sta = $semester_node->nid;
//    }
//    
//    $form['filter']['semester'] = array(
//        '#type' => 'select',
//        '#title' => t('Semester Tahun Akademik'),
//        '#options' => $sta,
//        '#default_value' => empty($laporan_pembayaran['input']['semester'])? $default_sta : $laporan_pembayaran['input']['semester'],
//    );
   
   $form['filter']['semester'] = array(
        '#type' => 'textfield',
        '#title' => t('Semester Tahun Akademik'), 
       '#description' => t('Ketikkan sebagian kata lalu tunggu beberapa saat'),
        '#autocomplete_path' => 'input-pembayaran/ajax-semester-callback',
        '#size' => 25,
        '#default_value' => $laporan_pembayaran['input']['semester']
    );
    
    $prodi_array = node_load_multiple(array(), array('type' => 'bsf_program_studi'));
    $ps = array();
    $ps['all'] = 'ALL';
    foreach($prodi_array as $prodi_node){
        $ps[$prodi_node->nid] = $prodi_node->title;      
    }    
    $default_ps = 'all';
    
    $form['filter']['prodi'] = array(
        '#type' => 'select',
        '#title' => t('Program Studi'),
        '#options' => $ps,
        '#default_value' => empty($laporan_pembayaran['input']['prodi'])? $default_ps : $laporan_pembayaran['input']['prodi'],
//         '#prefix' => '<div class="container-inline">',
//        '#suffix' => '</div></br>'
    );
   
    $angkatan_array = node_load_multiple(array(), array('type' => 'bsf_angkatan'));
    $angk = array();
    $angk['all'] = 'ALL';
    foreach($angkatan_array as $angkatan_node){
        $angk[$angkatan_node->nid] = $angkatan_node->title;      
    }    
    arsort($angk);
    $default_angk = 'all';
    
    $form['filter']['angkatan'] = array(
        '#type' => 'select',
        '#title' => t('Angkatan'),
        '#options' => $angk,
        '#default_value' => empty($laporan_pembayaran['input']['angkatan'])? $default_angk : $laporan_pembayaran['input']['angkatan'],
//         '#prefix' => '<div class="container-inline">',
//        '#suffix' => '</div>'
    );
    
    //default_value untuk tipe 'date_popup' harus berformat 'Y-m-d'
    $default_tanggal_dari = empty($laporan_pembayaran['input']['tanggal_dari']['date'])? 
            date('Y-m-d'): date('Y-m-d',strtotime($laporan_pembayaran['input']['tanggal_dari']['date']));
    $form['filter']['tanggal_dari'] = array(
        //'#title' => t('Dari:'),
        '#type' => 'date_popup',
        //'#description' => t('Please select the date of booking'),
        //'#required' => TRUE,
        '#date_format' => 'd M Y',
        '#date_year_range' => '-1:+1',      
        '#default_value' => $default_tanggal_dari,
        '#prefix' => '<div class="container-inline"><b>Dari:</b>',
        '#suffix' => '</div>',
         '#date_label_position' => 'within'
      );
    
    $default_tanggal_sampai = empty($laporan_pembayaran['input']['tanggal_sampai']['date'])? 
            date('Y-m-d'): date('Y-m-d',strtotime($laporan_pembayaran['input']['tanggal_sampai']['date']));
     $form['filter']['tanggal_sampai'] = array(
        //'#title' => t('Sampai:'),
        '#type' => 'date_popup',
        //'#description' => t('Please select the date of booking'),
        //'#required' => TRUE,
        '#date_format' => 'd M Y',
        '#date_year_range' => '-1:+1',    
        '#default_value' =>$default_tanggal_sampai,
          '#date_label_position' => 'within',
         '#prefix' => '<div class="container-inline"><b>Sampai:</b>',
        '#suffix' => '</div>',

      );

    $form['filter']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Filter'),
    );
 
    if(!empty($laporan_pembayaran['input'])){
        $angkatan = $laporan_pembayaran['input']['angkatan'];

        $prodi = $laporan_pembayaran['input']['prodi'];

        $query_semester = new EntityFieldQuery();
        $query_semester->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'bsf_semester_akademik')
          ->propertyCondition('status', 1)
          ->propertyCondition('title', $laporan_pembayaran['input']['semester'],'CONTAINS');
        $result_semester = $query_semester->execute();
        $sta = array_values($result_semester['node']);
        $sta_nid = $sta[0]->nid;
        
        //hidden value dari nid semester
        $form['node']['semester_nid'] = array(
                '#type' => 'hidden',
                '#value' => $sta_nid,
                //'#weight' => 1,
            );
        
        $tggl_dari = $laporan_pembayaran['input']['tanggal_dari']['date'];
        $tggl_sampai = $laporan_pembayaran['input']['tanggal_sampai']['date'];
        $tanggal_dari_timestamp = strtotime($laporan_pembayaran['input']['tanggal_dari']['date'].' 00:00');
        $tanggal_sampai_timestamp = strtotime($laporan_pembayaran['input']['tanggal_sampai']['date'].' 23:59');
               
        $query_nominal = new EntityFieldQuery();
        $query_nominal->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'bsf_keuangan')
          ->propertyCondition('status', 1)
          ->propertyCondition('changed', $tanggal_dari_timestamp, '>=')
          ->propertyCondition('changed', $tanggal_sampai_timestamp, '<=')
          ->fieldCondition('field_bsf_semester_akademik','target_id',$sta_nid,'=');
        $result = $query_nominal->execute();

        if($result){
            foreach(element_children($result['node']) as $keuangan_nid){
                $keuangan_node = node_load($keuangan_nid);
                $mhs_node = node_load($keuangan_node->field_bsf_mahasiswa['und'][0]['target_id']);
                
                $mhs_prodi = $mhs_node->field_bsf_program_studi['und'][0]['target_id'];
                $mhs_angkatan = $mhs_node->field_bsf_angkatan['und'][0]['target_id'];
                if(($angkatan == $mhs_angkatan AND $prodi == $mhs_prodi)
                        OR ($prodi == $mhs_prodi AND $angkatan == 'all')
                        OR ($prodi == 'all' AND $angkatan == $mhs_angkatan)
                        OR ($prodi == 'all' AND $angkatan == 'all')){
                    $form['node']['nim'][$keuangan_nid] = array(
                        '#type' => 'value',
                        '#value' => $mhs_node->field_bsf_nim['und'][0]['value'],
                    );
                    
                    $form['node']['nama'][$keuangan_nid] = array(
                        '#type' => 'value',
                        '#value' => $mhs_node->field_bsf_nama['und'][0]['value'],
                    );
                    
                    $prodi_node = node_load($mhs_node->field_bsf_program_studi['und'][0]['target_id']);
                    $form['node']['prodi'][$keuangan_nid] = array(
                        '#type' => 'value',
                        '#value' => $prodi_node->title,
                    );
                    
                    $angkatan_node = node_load($mhs_node->field_bsf_angkatan['und'][0]['target_id']);
                    $form['node']['angkatan'][$keuangan_nid] = array(
                        '#type' => 'value',
                        '#value' => $angkatan_node->title,
                    );
                    
                     $pembiayaan_node = node_load($mhs_node->field_bsf_pembiayaan['und'][0]['target_id']);
                     $form['node']['biaya'][$keuangan_nid] = array(
                         '#type' => 'value',
                         '#value' => $pembiayaan_node->title,
                          // '#weight' => 1,
                     );
                     
                     $form['node']['changed'][$keuangan_nid] = array(
                         '#type' => 'value',
                         '#value' => format_date($keuangan_node->changed, 'custom', 'd M Y H:i'),
                          // '#weight' => 1,
                     );
                     
                     $total = 0;
                      $items_komponen = field_get_items('node', $keuangan_node, 'field_bsf_pembayaran_komponen');                
                    foreach ($items_komponen as $item) {

                        $fc = field_collection_field_get_entity($item);
                        $komp_nominal_id = $fc->field_bsf_komponen_nominal['und'][0]['target_id'];
                        $total += $fc->field_bsf_pembayaran['und'][0]['value'];
                    }
                    $total = number_format($total, 0, '.', ',');
                    
                     $form['node']['total'][$keuangan_nid] = array(
                         '#type' => 'value',
                         '#value' => l($total,"node/$keuangan_nid"),
                     );
                     
                     $form['node']['tanggal_dari'] = array(
                         '#type' => 'hidden',
                         '#value' => $tanggal_dari_timestamp
                     );
                     $form['node']['tanggal_sampai'] = array(
                         '#type' => 'hidden',
                         '#value' => $tanggal_sampai_timestamp
                     );
                }
            }     
            asort($form['node']['nama']);
                        
        }
            
       
    
//******* BUILD TABLE ***********\\    
        $header = array(
            array('data' => t('No.'),),
            array('data' => t('NIM')),
            array('data' => t('Nama')),
            array('data' => t('Program Studi')),
            array('data' => t('Angkatan')),
            array('data' => t('Pembiayaan')),
            array('data' => t('Tanggal Input/Update')),
            array('data' => t('Total (Rp.)')),
        );
         $rows = array();
        if(isset($form['node']['nama'])){          
            $no = 1;

            foreach(element_children($form['node']['nama']) as $keuangan_nid){
                $row = array();      
                $row[] = array('data' => $no++);
                $row[] = array('data' => $form['node']['nim'][$keuangan_nid]['#value']);
                $row[] = array('data' => $form['node']['nama'][$keuangan_nid]['#value']);
                $row[] = array('data' => $form['node']['prodi'][$keuangan_nid]['#value']);
                $row[] = array('data' => $form['node']['angkatan'][$keuangan_nid]['#value']);
                $row[] = array('data' => $form['node']['biaya'][$keuangan_nid]['#value']);
                 $row[] = array('data' => $form['node']['changed'][$keuangan_nid]['#value']);
                $row[] = array('data' => $form['node']['total'][$keuangan_nid]['#value']);
                $rows[$keuangan_nid] = $row;
            }
            
              $form['to_pdf'] = array(
                    '#type' => 'submit',
                    '#value' => t('Print to PDF'),
                    '#weight' => 15,                   
                );
              
               $form['to_excel'] = array(
                    '#type' => 'submit',
                    '#value' => t('Export to Excel'),
                    '#weight' => 15
                );
        }
        $form['title'] = array(
            '#type' => 'fieldset',
            '#title' => t("Mahasiswa yang Telah Bayar [$tggl_dari - $tggl_sampai]"),
            '#collapsible' => FALSE,
        );
        $form['selected'] = array(
            '#type' => 'tableselect',
            '#header' => $header,
            '#options' => $rows,
            '#empty' => t('No DATA.'),
            '#weight' => 10
          );
    }  
//******** END of TABLE ***********\\
   
    variable_del('laporan_pembayaran');
    return $form;
}

function theme_laporan_pembayaran_form(&$variables){
    
    $form = $variables['form'];
    $output = '';
//    $header = array(
//        array('data' => t('No.'),),
//        array('data' => t('NIM')),
//        array('data' => t('Nama')),
//        array('data' => t('Program Studi')),
//        array('data' => t('Angkatan')),
//        array('data' => t('Pembiayaan')),
//        array('data' => t('Tanggal Input/Update')),
//        array('data' => t('')),
//    );
//    
//    if(isset($form['node']['nama'])){
//        $rows = array();
//        $no = 1;
//
//        foreach(element_children($form['node']['nama']) as $keuangan_nid){
//            $row = array();      
//            $row[] = array('data' => $no++);
//            $row[] = array('data' => $form['node']['nim'][$keuangan_nid]['#value']);
//            $row[] = array('data' => $form['node']['nama'][$keuangan_nid]['#value']);
//            $row[] = array('data' => $form['node']['prodi'][$keuangan_nid]['#value']);
//            $row[] = array('data' => $form['node']['angkatan'][$keuangan_nid]['#value']);
//            $row[] = array('data' => $form['node']['biaya'][$keuangan_nid]['#value']);
//             $row[] = array('data' => $form['node']['changed'][$keuangan_nid]['#value']);
//            $row[] = array('data' => $form['node']['detil'][$keuangan_nid]['#value']);
//            $rows[] = $row;
//        }
//    $output .= drupal_render($form['filter']);
//    $output .= theme('table',
//                array(
//                    'header' => $header,
//                    'rows' => $rows,
//                    'empty' => 'No data is available',)
//            ); 
//    }
//       
    $output .= drupal_render_children($form);
    return $output;
}

function laporan_pembayaran_form_submit($form,&$form_state){
   
        variable_set('laporan_pembayaran', $form_state);
             
        if($form_state['input']['op'] == 'Print to PDF'){
            $sta_nid = $form_state['input']['node']['semester_nid'];
    
            if(isset($form_state['input']['selected'])){
                drupal_goto("laporan-pembayaran/print/$sta_nid");
            }
            else{
                 form_set_error('selected', 'Anda belum memilih mahasiswa');
            }
            
        }

        if($form_state['input']['op'] == 'Export to Excel'){
            if(isset($form_state['input']['selected'])){
                    laporan_pembayaran_generate_excel();
                }
                else{
                     form_set_error('selected', 'Anda belum memilih mahasiswa');
                }
            
        }    
    
    
}

function laporan_pembayaran_generate_excel(){
    global $user;
    $profile = user_load($user->uid);
    $laporan = variable_get('laporan_pembayaran');
    
    $tanggal_dari = $laporan['input']['tanggal_dari']['date'];
    $tanggal_sampai = $laporan['input']['tanggal_sampai']['date'];
    $semester = $laporan['input']['semester'];
    // Produce excel file..
  include_once libraries_get_path('phpexcel') . '/Classes/PHPExcel.php';

  $fname_date = 'laporan-pembayaran';
  
  $fname_ext = "xlsx";

  $output_path = variable_get('file_public_path', conf_path() . '/files')
      . "/" . $fname_date . "_" . $user->uid . "." . $fname_ext;
  // uid pada nama file untuk mengantisipasi multi user yg mendownlod pada waktu bersamaan
  // Create new PHPExcel object
  $objPHPExcel = new PHPExcel();

  $objPHPExcel->getProperties()->setCreator($profile->name)
      ->setLastModifiedBy($profile->name)
      ->setTitle("Laporan Pembayaran Mahasiswa [$tanggal_dari - $tanggal_sampai]")
      ->setSubject("Laporan Pembayaran Mahasiswa")
      ->setDescription("Laporan Pembayaran Mahasiswa $tanggal_dari - $tanggal_sampai")
      ->setKeywords("Laporan Pembayaran Mahasiswa")
      ->setCategory("Laporan Pembayaran");
  
  
  $styleThinBlackBorderOutlineWithColor = array(
    'borders' => array(
      'outline' => array(
        'style' => PHPExcel_Style_Border::BORDER_THIN,
        'color' => array('argb' => 'FF000000'),
      ),
    ),
    'fill' => array(
        'type' => PHPExcel_Style_Fill::FILL_SOLID,
        'color' => array('rgb' => 'D3D3D3'),
      ),
  );
  
  $styleNoBorderlineWithColor = array(
    'fill' => array(
        'type' => PHPExcel_Style_Fill::FILL_SOLID,
        'color' => array('rgb' => 'EEEEEE'),
      ),
  );
  
  $styleThinBlackBorderOutline = array(
    'borders' => array(
      'outline' => array(
        'style' => PHPExcel_Style_Border::BORDER_THIN,
        'color' => array('argb' => 'FF000000'),
      ),
    ),  
  );
  
  $styleThinBlackBorderOutline2 = array(
    'borders' => array(
      'outline' => array(
        'style' => PHPExcel_Style_Border::BORDER_DOUBLE,
        'color' => array('argb' => 'FF000000'),
      ),
    ),
  );
  
  // SHEET 0
  $objPHPExcel->setActiveSheetIndex(0);
  
  // SET WIDTH
  $objPHPExcel->getActiveSheet()->getColumnDimension('A')->setWidth(5); //No.
  $objPHPExcel->getActiveSheet()->getColumnDimension('B')->setAutoSize(true); //NIM
  $objPHPExcel->getActiveSheet()->getColumnDimension('C')->setAutoSize(true); //Nama
  $objPHPExcel->getActiveSheet()->getColumnDimension('D')->setAutoSize(true); //Program Studi
  $objPHPExcel->getActiveSheet()->getColumnDimension('E')->setWidth(20); //Pembiayaan
  $objPHPExcel->getActiveSheet()->getColumnDimension('F')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('G')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('H')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('I')->setAutoSize(true);
  $objPHPExcel->getActiveSheet()->getColumnDimension('J')->setAutoSize(true);
  
  //************* TITLE *************//
  $objPHPExcel->getActiveSheet()->setCellValue('A1', "LAPORAN PEMBAYARAN MAHASISWA [$tanggal_dari - $tanggal_sampai]");
  $objPHPExcel->getActiveSheet()->getStyle('A1')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('A1')->getFont()->setBold(true);
  $objPHPExcel->getActiveSheet()->mergeCells('A1:G1');
  
  $objPHPExcel->getActiveSheet()->setCellValue('A2', $semester);
  $objPHPExcel->getActiveSheet()->getStyle('A2')->getFont()->setSize(12);
  $objPHPExcel->getActiveSheet()->getStyle('A2')->getFont()->setBold(true);
  //************** END OF TITLE *********//
     
  $keuangan_array = $laporan['input']['selected'];
  $angkatan_array = array();
  
  $i = 0;
  foreach($keuangan_array as $keuangan_nid){
      $keuangan_node = node_load($keuangan_nid);
      $mhs_node = node_load($keuangan_node->field_bsf_mahasiswa['und'][0]['target_id']);
      $prodi_node = node_load($mhs_node->field_bsf_program_studi['und'][0]['target_id']);
      $pembiayaan_node = node_load($mhs_node->field_bsf_pembiayaan['und'][0]['target_id']);
      
      $angkatan_node = node_load($mhs_node->field_bsf_angkatan['und'][0]['target_id']);
      $angkatan_array[$angkatan_node->nid][$i]['keuangan_node'] = $keuangan_node;
      $angkatan_array[$angkatan_node->nid][$i]['mhs_nim'] = $mhs_node->field_bsf_nim['und'][0]['value'];
      $angkatan_array[$angkatan_node->nid][$i]['mhs_nama'] = $mhs_node->field_bsf_nama['und'][0]['value'];
      $angkatan_array[$angkatan_node->nid][$i]['mhs_prodi'] = $prodi_node->title;
      $angkatan_array[$angkatan_node->nid][$i++]['mhs_pembiayaan'] = $pembiayaan_node->title;
  }

  $huruf = array('A','B','C','D','E','F','G','H','I','J','K','L');
  
  $row = 4;
  foreach($angkatan_array as $angkatan_nid => $keuangan_array){

     $angkatan_node = node_load($angkatan_nid);
          
    $objPHPExcel->getActiveSheet()->setCellValue('A'.$row, 'ANGKATAN '.$angkatan_node->title);
    $objPHPExcel->getActiveSheet()->getStyle('A'.$row)->getFont()->setSize(12);
    $objPHPExcel->getActiveSheet()->getStyle('A'.$row)->getFont()->setBold(true);
    
    $row++;
   
    $query_komp = new EntityFieldQuery();
    $query_komp->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'bsf_komponen_nominal')
      ->propertyCondition('status', 1)
      ->fieldCondition('field_bsf_angkatan','target_id',$angkatan_nid,'=');

    $result_komp = $query_komp->execute();
    $komponen_array = array(); //variable yg menyimpan komponen nominal untuk looping default_value komponnen nominal

    if(isset($result_komp['node'])){
        foreach(element_children($result_komp['node']) as $komp_nid){
            $komp_node = node_load($komp_nid);
            $komponen_array[$komp_nid] = $komp_node->title;
        }
        $jumlah_komponen = count($komponen_array);
    }
    
//******************* HEADER *************//
    $objPHPExcel->getActiveSheet()->setCellValue('A'.$row, 'No.');
    $objPHPExcel->getActiveSheet()->getStyle('A'.$row)->getFont()->setSize(12);
    $objPHPExcel->getActiveSheet()->getStyle('A'.$row)->getFont()->setBold(true);
    $objPHPExcel->getActiveSheet()->mergeCells("A".$row.":A".($row+1));
    $objPHPExcel->getActiveSheet()->getStyle('A'.$row.':A'.($row+1))->getAlignment()
          ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER)
          ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);

    $objPHPExcel->getActiveSheet()->getStyle('A'.$row.':A'.($row+1))->applyFromArray($styleThinBlackBorderOutlineWithColor);

    $objPHPExcel->getActiveSheet()->setCellValue('B'.$row, 'NIM');
    $objPHPExcel->getActiveSheet()->getStyle('B'.$row)->getFont()->setSize(12);
    $objPHPExcel->getActiveSheet()->getStyle('B'.$row)->getFont()->setBold(true);
    $objPHPExcel->getActiveSheet()->mergeCells("B".$row.":B".($row+1));
    $objPHPExcel->getActiveSheet()->getStyle("B".$row.":B".($row+1))->getAlignment()
          ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER)
          ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    $objPHPExcel->getActiveSheet()->getStyle('B'.$row.':B'.($row+1))->applyFromArray($styleThinBlackBorderOutlineWithColor);

    $objPHPExcel->getActiveSheet()->setCellValue('C'.$row, 'Nama');
    $objPHPExcel->getActiveSheet()->getStyle('C'.$row)->getFont()->setSize(12);
    $objPHPExcel->getActiveSheet()->getStyle('C'.$row)->getFont()->setBold(true);
    $objPHPExcel->getActiveSheet()->mergeCells("C".$row.":C".($row+1));
    $objPHPExcel->getActiveSheet()->getStyle("C".$row.":C".($row+1))->getAlignment()
          ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER)
          ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    $objPHPExcel->getActiveSheet()->getStyle('C'.$row.':C'.($row+1))->applyFromArray($styleThinBlackBorderOutlineWithColor);

   $objPHPExcel->getActiveSheet()->setCellValue('D'.$row, 'Program Studi');
    $objPHPExcel->getActiveSheet()->getStyle('D'.$row)->getFont()->setSize(12);
    $objPHPExcel->getActiveSheet()->getStyle('D'.$row)->getFont()->setBold(true);
    $objPHPExcel->getActiveSheet()->mergeCells("D".$row.":D".($row+1));
    $objPHPExcel->getActiveSheet()->getStyle("D".$row.":D".($row+1))->getAlignment()
          ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER)
          ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    $objPHPExcel->getActiveSheet()->getStyle('D'.$row.':D'.($row+1))->applyFromArray($styleThinBlackBorderOutlineWithColor);
    
     $objPHPExcel->getActiveSheet()->setCellValue('E'.$row, 'Pembiayaan');
    $objPHPExcel->getActiveSheet()->getStyle('E'.$row)->getFont()->setSize(12);
    $objPHPExcel->getActiveSheet()->getStyle('E'.$row)->getFont()->setBold(true);
    $objPHPExcel->getActiveSheet()->mergeCells("E".$row.":E".($row+1));
    $objPHPExcel->getActiveSheet()->getStyle("E".$row.":E".($row+1))->getAlignment()
          ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER)
          ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    $objPHPExcel->getActiveSheet()->getStyle('E'.$row.':E'.($row+1))->applyFromArray($styleThinBlackBorderOutlineWithColor);

    $column_komp = $huruf[4+$jumlah_komponen]; // '5' diambil dari huruf F (huruf abjad ke-x -1)
    $objPHPExcel->getActiveSheet()->setCellValue('F'.$row, 'Biaya');
    $objPHPExcel->getActiveSheet()->getStyle('F'.$row)->getFont()->setSize(12);
    $objPHPExcel->getActiveSheet()->getStyle('F'.$row)->getFont()->setBold(true);
    $objPHPExcel->getActiveSheet()->mergeCells("F$row:$column_komp".$row);
    $objPHPExcel->getActiveSheet()->getStyle("F$row:$column_komp".$row)->getAlignment()
          ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER)
          ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    $objPHPExcel->getActiveSheet()->getStyle("F$row:$column_komp".$row)->applyFromArray($styleThinBlackBorderOutlineWithColor);
    
    $komponen_row = $row;
    $komponen_row++;
    
     //******************** KOMPONEN BIAYA **************//  
    $e = 5;
    foreach($komponen_array as $komp_nid => $komp_title){
        $column_komp = $huruf[5+$jumlah_komponen]; // '5' diambil dari huruf F (huruf abjad ke-x -1)
        $objPHPExcel->getActiveSheet()->setCellValue($huruf[$e].$komponen_row, $komp_title);
        $objPHPExcel->getActiveSheet()->getStyle($huruf[$e].$komponen_row)->getFont()->setSize(12);
        $objPHPExcel->getActiveSheet()->getStyle($huruf[$e].$komponen_row)->getFont()->setBold(true);
        $objPHPExcel->getActiveSheet()->getStyle($huruf[$e].$komponen_row)->getAlignment()
              ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER)
              ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
        $objPHPExcel->getActiveSheet()->getStyle($huruf[$e].$komponen_row)->applyFromArray($styleThinBlackBorderOutlineWithColor);
        
        $e++;
    }
    
    //******************** TOTAL **************//
    $objPHPExcel->getActiveSheet()->setCellValue($huruf[$e].$row, 'Total');
    $objPHPExcel->getActiveSheet()->getStyle($huruf[$e].$row)->getFont()->setSize(12);
    $objPHPExcel->getActiveSheet()->getStyle($huruf[$e].$row)->getFont()->setBold(true);
    $objPHPExcel->getActiveSheet()->mergeCells("$huruf[$e]$row:$column_komp".($row+1));
    $objPHPExcel->getActiveSheet()->getStyle("$huruf[$e]$row:$column_komp".($row+1))->getAlignment()
          ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER)
          ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
    $objPHPExcel->getActiveSheet()->getStyle("$huruf[$e]$row:$column_komp".($row+1))->applyFromArray($styleThinBlackBorderOutlineWithColor);
       
    $row++;
    $row++;
//******************* END OF HEADER **********   
      
    $no = 1;
    foreach($keuangan_array as $data){
     
        // content of Number
        $objPHPExcel->getActiveSheet()->setCellValue('A'.$row, $no++);
        $objPHPExcel->getActiveSheet()->getStyle('A'.$row)->getFont()->setSize(12);              
//        $objPHPExcel->getActiveSheet()->getStyle('A'.$row.':A'.($row+1))->getAlignment()
//              ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER)
//              ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
        
        
        $objPHPExcel->getActiveSheet()->setCellValue('B'.$row, $data['mhs_nim']);
        $objPHPExcel->getActiveSheet()->getStyle('B'.$row)->getFont()->setSize(12);              
//        $objPHPExcel->getActiveSheet()->getStyle("B".$row.":B".($row+1))->getAlignment()
//              ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER)
//              ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);       

        $objPHPExcel->getActiveSheet()->setCellValue('C'.$row, $data['mhs_nama']);
        $objPHPExcel->getActiveSheet()->getStyle('C'.$row)->getFont()->setSize(12);  
//        $objPHPExcel->getActiveSheet()->getStyle("C".$row.":C".($row+1))->getAlignment()
//              ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER)
//              ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
       

       $objPHPExcel->getActiveSheet()->setCellValue('D'.$row, $data['mhs_prodi']);
        $objPHPExcel->getActiveSheet()->getStyle('D'.$row)->getFont()->setSize(12);
//        $objPHPExcel->getActiveSheet()->getStyle("D".$row.":D".($row+1))->getAlignment()
//              ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER)
//              ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
        

         $objPHPExcel->getActiveSheet()->setCellValue('E'.$row, $data['mhs_pembiayaan']);
        $objPHPExcel->getActiveSheet()->getStyle('E'.$row)->getFont()->setSize(12);
//        $objPHPExcel->getActiveSheet()->getStyle("E".$row.":E".($row+1))->getAlignment()
//              ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER)
//              ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
        
//
//        $column_komp = $huruf[4+$jumlah_komponen]; // '5' diambil dari huruf F (huruf abjad ke-x -1)
//        $objPHPExcel->getActiveSheet()->setCellValue('F'.$row, 'Biaya');
//        $objPHPExcel->getActiveSheet()->getStyle('F'.$row)->getFont()->setSize(12);   
//        $objPHPExcel->getActiveSheet()->getStyle("F$row:$column_komp".$row)->getAlignment()
//              ->setHorizontal(PHPExcel_Style_Alignment::HORIZONTAL_CENTER)
//              ->setVertical(PHPExcel_Style_Alignment::VERTICAL_CENTER);
        
        
        
        $items = field_get_items('node', $data['keuangan_node'], 'field_bsf_pembayaran_komponen');
        $komp_array = array();
        $komp_values = array();
        $komp_values_detil = array();       
        foreach ($items as $item) {          
            $fc = field_collection_field_get_entity($item);
            $komp_nid = $fc->field_bsf_komponen_nominal[LANGUAGE_NONE][0]['target_id'];
            $komp_node = node_load($komp_nid);
            $komp_parent_node = node_load($komp_node->field_bsf_komponen['und'][0]['target_id']);

            $komp_array[$komp_nid] = $komp_parent_node->title;

            $komp_values_detil[$komp_nid][] = $fc->field_bsf_pembayaran['und'][0]['value'];
            $komp_values[$komp_nid] = array_sum($komp_values_detil[$komp_nid]);
                                  
 
        }
        
        $total = 0;       
        $e = 5;
        foreach($komp_values as $nominal){
           // $column_komp = $huruf[5+$jumlah_komponen]; // '5' diambil dari huruf F (huruf abjad ke-x -1)
            $objPHPExcel->getActiveSheet()->setCellValue($huruf[$e].$row, $nominal);
            $objPHPExcel->getActiveSheet()->getStyle($huruf[$e].$row)->getFont()->setSize(12);           
            
            $total += $nominal; 
            
            $e++;
        }
        
        //******************** TOTAL **************//
        $objPHPExcel->getActiveSheet()->setCellValue($huruf[$e].$row, $total);
        $objPHPExcel->getActiveSheet()->getStyle($huruf[$e].$row)->getFont()->setSize(12);
        $objPHPExcel->getActiveSheet()->getStyle($huruf[$e].$row)->getFont()->setBold(true);
    

        $row++;
        
        
        
               
    }  
    $row = $row + 3;
  }

 
  // END OF TITLE

  

  // CONTENT
  // END OF CONTENT
  
  // Naming worksheet 1
  $objPHPExcel->getActiveSheet()->setTitle('LAPORAN PEMBAYARAN');

  // Set active sheet index to the first sheet, so Excel opens this as the first sheet
  $objPHPExcel->setActiveSheetIndex(0);

  $objWriter = PHPExcel_IOFactory::createWriter($objPHPExcel, 'Excel2007');
  $objWriter->save($output_path);

  //dpm($output_path, 'output_path');


  header('Content-Description: File Transfer');
  header('Content-Type: application/octet-stream');
  header('Content-Disposition: attachment; filename=' . $fname_date . "." . $fname_ext);
  header('Content-Transfer-Encoding: binary');
  header('Expires: 0');
  header('Cache-Control: must-revalidate');
  header('Pragma: public');
  header('Content-Length: ' . filesize($output_path));
  ob_clean();
  flush();
  readfile($output_path);

  unlink($output_path);

  exit;
}