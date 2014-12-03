<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


//function cmp($a, $b){
//    if ($a->field_bsf_tahun['und'][0]['value'] == $b->field_bsf_tahun['und'][0]['value']) {
//        return 0;
//    }
//    return ($a->field_bsf_tahun['und'][0]['value'] < $b->field_bsf_tahun['und'][0]['value']) ? -1 : 1;
//}

function input_pembayaran_semester_callback($string = ""){
    $matches = array();
  if ($string) {
   $query = new EntityFieldQuery();
   $query->entityCondition('entity_type', 'node')
           ->entityCondition('bundle', 'bsf_semester_akademik')
           ->propertyCondition('status', 1)
           ->propertyCondition('title', $string , 'CONTAINS');
   $result = $query->execute();

    foreach(element_children($result['node']) as $semester_nid){
        $semester_node = node_load($semester_nid);
        $matches[$semester_node->title] = $semester_node->title . "($semester_node->nid)";
        
    }
  }

  drupal_json_output($matches);
}

function input_pembayaran_form($form, &$form_state){
    global $user;
    $input_pembayaran = variable_get('input_pembayaran');
    
    $form = array();
 
    $form['mhs'] = array(
            '#tree' => TRUE,
          );
   $form['filter'] = array(
       '#title' => t('Filter'),
        '#type' => 'fieldset',
       '#collapsible' => TRUE,
       '#collapsed' => empty($input_pembayaran)? FALSE:TRUE,
    );
   
//    $semester_array = node_load_multiple(array(), array('type' => 'bsf_semester_akademik'));
//    usort($semester_array, "cmp");
//    $sta = array();
//    foreach($semester_array as $semester_node){
//        $sta[$semester_node->nid] = $semester_node->title;
//        $default_sta = $semester_node->nid;
//    }
    
//    $form['filter']['semester'] = array(
//        '#type' => 'select',
//        '#title' => t('Semester Tahun Akademik'),
//        '#options' => $sta,
//        '#default_value' => empty($input_pembayaran['input']['semester'])? $default_sta : $input_pembayaran['input']['semester']
//    );
    
    $form['filter']['semester'] = array(
        '#type' => 'textfield',
        '#title' => t('Semester Tahun Akademik'),  
        '#description' => t('Ketikkan sebagian kata lalu tunggu beberapa saat'),
        '#autocomplete_path' => 'input-pembayaran/ajax-semester-callback',
        '#size' => 25,
        '#default_value' => $input_pembayaran['input']['semester']
    );
            
    $prodi_array = node_load_multiple(array(), array('type' => 'bsf_program_studi'));
    $ps = array();
    foreach($prodi_array as $prodi_node){
        $ps[$prodi_node->nid] = $prodi_node->title;
        $default_ps = $prodi_node->nid;
    }
    
    $def_value_ps = isset($form_state['values']['prodi']) ? $form_state['values']['prodi'] : $default_ps;
    $form['filter']['prodi'] = array(
        '#type' => 'select',
        '#title' => t('Program Studi'),
        '#options' => $ps,
        '#default_value' => $def_value_ps,
//        '#ajax' => array(
//            'callback' => '_ajax_get_prokul_selected',
//            'wrapper' => 'prodi-div'
//        ),
    );
//    
//    $def_value_pk = isset($form_state['values']['prokul']) ? $form_state['values']['prokul'] : $input_pembayaran['input']['prokul'];
//    $prokul_node = node_load($def_value_pk);
//    $form['filter']['prokul'] = array(
//        '#type' => 'select',
//        '#title' => t('Program Kuliah'),
//        '#prefix' => '<div id="prodi-div">',
//        '#suffix' => '</div>',
//        '#options' => input_pembayaran_get_prokul($def_value_ps),
//        '#default_value' => $def_value_pk
//    );
   
    $angkatan_array = node_load_multiple(array(), array('type' => 'bsf_angkatan'));
    $angk = array();
    foreach($angkatan_array as $angkatan_node){
        $angk[$angkatan_node->nid] = $angkatan_node->title;
        $default_angk = $angkatan_node->nid;
    }
    arsort($angk);
    $form['filter']['angkatan'] = array(
        '#type' => 'select',
        '#title' => t('Angkatan'),
        '#options' => $angk,
        '#default_value' => empty($input_pembayaran['input']['angkatan'])? $default_angk : $input_pembayaran['input']['angkatan']
    );
    $form['filter']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Filter'),
    );
    
    if(!empty($input_pembayaran['input'])){
        $angkatan = $input_pembayaran['input']['angkatan'];
        $angkatan_node = node_load($angkatan);
        $prodi = $input_pembayaran['input']['prodi'];
        $prodi_node = node_load($prodi);

        //$prokul = $input_pembayaran['input']['prokul'];
        
        $query_semester = new EntityFieldQuery();
        $query_semester->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'bsf_semester_akademik')
          ->propertyCondition('status', 1)
          ->propertyCondition('title', $input_pembayaran['input']['semester'],'CONTAINS');
        $result_semester = $query_semester->execute();
        $sta = array_values($result_semester['node']);
        $sta_nid = $sta[0]->nid;
        $sta_node = node_load($sta_nid);
        
        //hidden value dari nid semester
        $form['mhs']['semester_nid'] = array(
                '#type' => 'hidden',
                '#value' => $sta_nid,
                //'#weight' => 1,
            );
     
        $query_komp = new EntityFieldQuery();
        $query_komp->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'bsf_komponen_nominal')
          ->propertyCondition('status', 1)
          ->fieldCondition('field_bsf_angkatan','target_id',$angkatan,'=');

        $result_komp = $query_komp->execute();
        $komponen_array = array(); //variable yg menyimpan komponen nominal untuk looping default_value komponnen nominal
       
        if(isset($result_komp['node'])){
            foreach(element_children($result_komp['node']) as $komp_nid){
                $komp_node = node_load($komp_nid);
                $komponen_array[$komp_nid] = $komp_node->title;
                
                $komponen_node = node_load($komp_node->field_bsf_komponen['und'][0]['target_id']);
                 $form['mhs']['nama_komponen'][$komp_nid] = array(
                        '#type' => 'value',
                        //'#default_value' => empty($check[$mhs_node->nid])? '':$check[$mhs_node->nid],
                        '#value' => $komponen_node->title,
                    );
            }
        }
        
        
        $query_mhs = new EntityFieldQuery();
        $query_mhs->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'bsf_mahasiswa')
          ->propertyCondition('status', 1)
          ->fieldCondition('field_bsf_angkatan','target_id',$angkatan,'=')
          //->fieldCondition('field_bsf_program_kuliah','target_id',$def_value_pk,'=');
          ->fieldCondition('field_bsf_program_studi','target_id',$prodi,'=');

        $result = $query_mhs->execute();
        if(empty($result)){
            drupal_set_message('Tidak ada data Mahasiswa!', 'Error');
            return $form;
        }
        else{
            $form['deskripsi']['title'] = array(
                '#type' => 'item',
                //'#markup' => '<u><b>'.$prokul_node->title.' '.$angkatan_node->title.' '.$sta_node->title.'</b></u>'
                '#markup' => '<u><b>'.$prodi_node->title.' '.$angkatan_node->title.' '.$sta_node->title.'</b></u>'
            );
    //         $form['deskripsi']['angkatan'] = array(
    //            '#type' => 'item',
    //            '#markup' => 'Angkatan: <b>'.$angkatan_node->title.'</b>'
    //        );
    //         $form['deskripsi']['semester'] = array(
    //            '#type' => 'item',
    //            '#markup' => 'Semester Tahun Akademik: <b>'.$sta_node->title.'</b>'
    //        );
        }
        
        foreach(element_children($result['node']) as $mhs_nid){           
            
            $mhs_node = node_load($mhs_nid);
            $form['mhs']['nim'][$mhs_node->nid] = array(
                '#type' => 'value',
                '#value' => $mhs_node->field_bsf_nim['und'][0]['value'],
                //'#weight' => 1,
            );
            
            $form['mhs']['nim_title'][$mhs_node->nid] = array(
                '#type' => 'hidden',
                '#value' => $mhs_node->field_bsf_nim['und'][0]['value'],
                //'#weight' => 1,
            );
            
             $form['mhs']['nama'][$mhs_node->nid] = array(
                '#type' => 'value',
                '#value' => $mhs_node->field_bsf_nama['und'][0]['value'],
                //'#weight' => 1,
            );

            $pembiayaan_node = node_load($mhs_node->field_bsf_pembiayaan['und'][0]['target_id']);
             $form['mhs']['biaya'][$mhs_node->nid] = array(
                '#type' => 'value',
                '#value' => $pembiayaan_node->title,
               // '#weight' => 1,
            );        

       //** Set DEFAULT VALUE for Kompononen Nominal
            $query_nominal = new EntityFieldQuery();
            $query_nominal->entityCondition('entity_type', 'node')
              ->entityCondition('bundle', 'bsf_keuangan')
              ->propertyCondition('status', 1)
              ->fieldCondition('field_bsf_mahasiswa','target_id',$mhs_nid,'=')
              ->fieldCondition('field_bsf_semester_akademik','target_id',$sta_nid,'=');
            $result = $query_nominal->execute();
            
            $komp_array = array();
            $komp_array_detil = array();  
            $approval_staff = array();
            $approval_manager = array();
            $keuangan_nid = NULL;
            $cicilan = array();
            if($result){
                
                $keuangan_nid = array_keys($result['node']);
                $keuangan_node = node_load($keuangan_nid[0]);
                         
                $items_komponen = field_get_items('node', $keuangan_node, 'field_bsf_pembayaran_komponen');                
                foreach ($items_komponen as $item) {
                    
                    $fc = field_collection_field_get_entity($item);
                    $komp_nominal_id = $fc->field_bsf_komponen_nominal['und'][0]['target_id'];
                    $komp_array_detil[$komp_nominal_id][] = $fc->field_bsf_pembayaran['und'][0]['value'];
                    $komp_array[$komp_nominal_id] = array_sum($komp_array_detil[$komp_nominal_id]);
                    if(count($komp_array_detil[$komp_nominal_id])>1){
                        $cicilan[] = $komp_nominal_id;
                    }
                 
                }
                
                 $items_staff = field_get_items('node', $keuangan_node, 'field_bsf_approval_role_staff');                
                    
                $fc = field_collection_field_get_entity($items_staff[0]);
                $approval_staff['krs'] = $fc->field_bsf_approval_krs['und'][0]['value'];
                $approval_staff['uts'] = $fc->field_bsf_approval_uts['und'][0]['value'];
                $approval_staff['uas'] = $fc->field_bsf_approval_uas['und'][0]['value'];
                 

                
                $items_manager = field_get_items('node', $keuangan_node, 'field_bsf_approval_role_manager');                
                    
                $fc = field_collection_field_get_entity($items_manager[0]);
                $approval_manager['krs'] = $fc->field_bsf_approval_krs['und'][0]['value'];
                $approval_manager['uts'] = $fc->field_bsf_approval_uts['und'][0]['value'];
                $approval_manager['uas'] = $fc->field_bsf_approval_uas['und'][0]['value'];       
            }
            
            $form['mhs']['keuangan_nid'][$mhs_node->nid] = array(
                '#type' => 'hidden',
//                '#value' => $keuangan_node,
                '#value' => $keuangan_nid[0],
                //'#weight' => 1,
            );
    //** End of Set DEFAULT VALUE for Kompononen Nominal
            
            if(!empty($komponen_array)){
                $total_komponen = 0;
                foreach($komponen_array as $komp_nid => $komp_nama){
               
                    $komp_default = array_key_exists($komp_nid, $komp_array)? $komp_array[$komp_nid]:'';
                    $total_komponen += $komp_default;
                    $form['mhs']['nominal'][$mhs_node->nid][$komp_nid] = array(
                        '#type' => 'textfield',
                        '#size' => 5,
                        '#default_value' => $komp_default,   
                        '#value' => $komp_default,
                    );
                    
                    $is_cicilan = empty($cicilan)? FALSE:in_array($komp_nid, $cicilan);
                    
                    //set field komponen nominal = readonly untuk role manager
                    if($is_cicilan){
                        $komp_default = empty($komp_default)? '':number_format($komp_default, 0, ',', '.');
                        $form['mhs']['nominal'][$mhs_node->nid][$komp_nid]['#disabled'] = TRUE;
                        $form['mhs']['nominal'][$mhs_node->nid][$komp_nid]['#value'] = $komp_default;
                        $form['mhs']['nominal'][$mhs_node->nid][$komp_nid]['#default_value'] = $komp_default;  
//                            '#value' => number_format($komp_default, 0, ',', '.'),
//                            '#default_value' => number_format($komp_default, 0, ',', '.'),
//                            '#disabled' => TRUE,
//                        );
                        $form['mhs']['nominal'][$mhs_node->nid][$komp_nid]['#attributes'] = array(
                            'readonly'=>'readonly',
                            'style'=>'background: none repeat scroll 0 0 #EAEAEA;'
                        );
                                                
                    }
                    
                    if(in_array('BSF Manager', $user->roles) OR in_array('BSF Admin', $user->roles)
                            OR (user_access('access approval-krs-uts-uas manager') AND $user->uid != 1)){
                        $form['mhs']['nominal'][$mhs_node->nid][$komp_nid]['#type'] = 'hidden';
                    }
                }

            }
            
            $total = number_format($total_komponen,0,',','.');
            $target_link = array('attributes' => array('target' => '_blank'));
            $link = (in_array('BSF Staff',$user->roles) OR user_access('access approval-krs-uts-uas staff'))?
                    "node/$keuangan_nid[0]/edit":"node/$keuangan_nid[0]";
             $form['mhs']['total'][$mhs_node->nid] = array(
                    '#type' => 'item',
                    '#markup' => empty($total)? 0 : l($total,$link,$target_link),
             );
                       
            if(in_array('BSF Staff', $user->roles) or user_access('access approval-krs-uts-uas staff')){
               
                $form['mhs']['staff_krs_approval'][$mhs_node->nid] = array(
                    '#type' => 'checkbox',
                    '#default_value' => isset($approval_staff['krs'])?$approval_staff['krs']:0,
                );
                 $form['mhs']['staff_uts_approval'][$mhs_node->nid] = array(
                    '#type' => 'checkbox',
                     '#default_value' => isset($approval_staff['uts'])?$approval_staff['uts']:0,
                  );
                 $form['mhs']['staff_uas_approval'][$mhs_node->nid] = array(
                    '#type' => 'checkbox',
                     '#default_value' => isset($approval_staff['uas'])?$approval_staff['uas']:0,
                  );
            }
            
            if(in_array('BSF Manager', $user->roles) or user_access('access approval-krs-uts-uas manager')){
               
                $form['mhs']['manager_krs_approval'][$mhs_node->nid] = array(
                    '#type' => 'checkbox',
                    '#default_value' => isset($approval_manager['krs'])?$approval_manager['krs']:0,
                );
                 $form['mhs']['manager_uts_approval'][$mhs_node->nid] = array(
                    '#type' => 'checkbox',
                     '#default_value' => isset($approval_manager['uts'])?$approval_manager['uts']:0,
                  );
                 $form['mhs']['manager_uas_approval'][$mhs_node->nid] = array(
                    '#type' => 'checkbox',
                     '#default_value' => isset($approval_manager['uas'])?$approval_manager['uts']:0,
                  );
            }
            
            if(in_array('BSF Admin', $user->roles) or user_access('access approval-krs-uts-uas admin')){
               
                $form['mhs']['admin_krs_approval'][$mhs_node->nid] = array(
                    '#type' => 'checkbox',
                    '#default_value' => isset($approval_manager['krs'])?$approval_manager['krs']:0,
                );
                 $form['mhs']['admin_uts_approval'][$mhs_node->nid] = array(
                    '#type' => 'checkbox',
                     '#default_value' => isset($approval_manager['uts'])?$approval_manager['uts']:0,
                  );
                 $form['mhs']['admin_uas_approval'][$mhs_node->nid] = array(
                    '#type' => 'checkbox',
                     '#default_value' => isset($approval_manager['uas'])?$approval_manager['uts']:0,
                  );
            }
             
        }
        
        $form['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Submit'),           
        );

        if(in_array('BSF Admin', $user->roles)){
            $form['submit']['#attributes'] = array('onclick' => 
                 'if(!confirm("Approval yang anda masukkan (check ataupun tidak) '
                 . 'akan mengganti approval staff dan manager. Anda Yakin?")){return false;}');
        }
        $form['print'] = array(
            '#type' => 'submit',
            '#value' => t('Print All')
        );

        asort($form['mhs']['nama']);      

    }
    
//    variable_del('input_pembayaran');   
    return $form;
}

//function _ajax_get_prokul_selected($form,$form_state){
//    return $form['filter']['prokul'];
//}

function input_pembayaran_get_prokul($prodi_nid = null){
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'bsf_program_kuliah')
            ->propertyCondition('status', 1)
            ->fieldCondition('field_bsf_program_studi','target_id',$prodi_nid,'=');
    $result = $query->execute();
    if($result){
        $prokul_array = array();
        foreach(element_children($result['node']) as $prokul_nid){
            $prokul_node = node_load($prokul_nid);
            $prokul_array[$prokul_nid] = $prokul_node->title;
        }
        
        return $prokul_array;
    }
    
    return array();
}

function theme_input_pembayaran_form(&$variables){
    global $user;
    $form = $variables['form'];
  
    $header = array(
        array('data' => t('No.'),),
        array('data' => t('NIM')),
        array('data' => t('Nama')),
        array('data' => t('Pembiayaan')),
 
        );
    
    if(isset($form['mhs']['nama_komponen'])
            AND (in_array('BSF Staff', $user->roles)
                    OR user_access('access approval-krs-uts-uas staff'))){
        foreach(element_children($form['mhs']['nama_komponen']) as $komp_nid){
            $header[] = $form['mhs']['nama_komponen'][$komp_nid]['#value'];
        } 
    }
    
    $header[] = array('data' => t('Total (Rp.)'));
    
    if(in_array('BSF Staff', $user->roles) OR user_access('access approval-krs-uts-uas staff')){
        $header[] = "<a href=# title='Persetujuan KRS untuk Role Staff'>KRS</a>";
        $header[] = "<a href=# title='Persetujuan UTS untuk Role Staff'>UTS</a>";
        $header[] = "<a href=# title='Persetujuan UAS untuk Role Staff'>UAS</a>";  
    }
    if(in_array('BSF Manager', $user->roles) OR user_access('access approval-krs-uts-uas manager')){
        $header[] = "<a href=# title='Persetujuan KRS untuk Role Manager'>KRS</a>";
        $header[] = "<a href=# title='Persetujuan UTS untuk Role Manager'>UTS</a>";
        $header[] = "<a href=# title='Persetujuan UAS untuk Role Manager'>UAS</a>";
    }   
     if(in_array('BSF Admin', $user->roles) OR user_access('access approval-krs-uts-uas admin')){
        $header[] = "<a href=# title='Persetujuan KRS untuk Role Admin'>KRS</a>";
        $header[] = "<a href=# title='Persetujuan UTS untuk Role Admin'>UTS</a>";
        $header[] = "<a href=# title='Persetujuan UAS untuk Role Admin'>UAS</a>";
    }   
    $output = '<div id=test>Form Verifikasi Pembayaran</div>';
    $output .= drupal_render($form['filter']);
//   
    if(isset($form['mhs']['nama'])){
        $rows = array();
        $no = 1;
        
        foreach(element_children($form['mhs']['nama']) as $mhs_nid){
            
            $row = array();      
            $row[] = array('data' => $no++);
            $row[] = array('data' => $form['mhs']['nim'][$mhs_nid]['#value']);
            
            $target_link = array('attributes' => array('target' => '_blank', 'align' => 'right'));
            $row[] = array('data' => l($form['mhs']['nama'][$mhs_nid]['#value'],"node/$mhs_nid",$target_link));         
            $row[] = array('data' => $form['mhs']['biaya'][$mhs_nid]['#value']);         
            
            if(isset($form['mhs']['nominal'])
                      AND (in_array('BSF Staff', $user->roles)
                    OR user_access('access approval-krs-uts-uas staff'))){
                foreach(element_children($form['mhs']['nominal'][$mhs_nid]) as $komp_nid){              
                    $row[] = array('data' => drupal_render($form['mhs']['nominal'][$mhs_nid][$komp_nid]),'align' => 'right');
                }
            }
            
            $row[] = array('data' => drupal_render($form['mhs']['total'][$mhs_nid]),'align' => 'right');
            
            if(in_array('BSF Staff', $user->roles) OR user_access('access approval-krs-uts-uas staff')){
                $row[] = array('data' => drupal_render($form['mhs']['staff_krs_approval'][$mhs_nid]));
                $row[] = array('data' => drupal_render($form['mhs']['staff_uts_approval'][$mhs_nid]));
                $row[] = array('data' => drupal_render($form['mhs']['staff_uas_approval'][$mhs_nid]));
            }
            if(in_array('BSF Manager', $user->roles) OR user_access('access approval-krs-uts-uas manager')){
               
                $row[] = array('data' => drupal_render($form['mhs']['manager_krs_approval'][$mhs_nid]));
                $row[] = array('data' => drupal_render($form['mhs']['manager_uts_approval'][$mhs_nid]));
                $row[] = array('data' => drupal_render($form['mhs']['manager_uas_approval'][$mhs_nid]));
            }
            
            if(in_array('BSF Admin', $user->roles) OR user_access('access approval-krs-uts-uas admin')){
               
                $row[] = array('data' => drupal_render($form['mhs']['admin_krs_approval'][$mhs_nid]));
                $row[] = array('data' => drupal_render($form['mhs']['admin_uts_approval'][$mhs_nid]));
                $row[] = array('data' => drupal_render($form['mhs']['admin_uas_approval'][$mhs_nid]));
            }
            $rows[] = $row;
        }                 
              
        $output .= drupal_render($form['deskripsi']);
        
        $output .= theme('table',
                    array(
                        'header' => $header,
                        'rows' => $rows,
                        'empty' => 'No data is available',)
                ); 
    }   
  
//  
    $output .= drupal_render_children($form);
    return $output;
}


function input_pembayaran_form_submit($form, &$form_state){
    
    variable_set('input_pembayaran', $form_state);  
    
    $input = isset($form_state['input']['mhs'])?$form_state['input']['mhs']:NULL;
    $sta_nid = $form_state['values']['mhs']['semester_nid'];
    
    $submit = $form_state['input']['op'];
    switch ($submit) {
//        case 'Filter':
//            variable_set('input_pembayaran', $form_state);          
//            break;
        case 'Submit':
                       
            $sta_node = node_load($sta_nid);
            $sta_title = substr($sta_node->field_bsf_tahun['und'][0]['value'],2,2).'0'.$sta_node->field_bsf_semester['und'][0]['value'];
//            if($input['check']){
            
            $count = 0;
                foreach(element_children($input['nominal']) as $mhs_nid){ 
                    $approval = array(
                        'staff_krs_approval' => isset($input['staff_krs_approval'][$mhs_nid])? $input['staff_krs_approval'][$mhs_nid]:'0',
                        'staff_uts_approval' => isset($input['staff_uts_approval'][$mhs_nid])? $input['staff_uts_approval'][$mhs_nid]:'0',
                        'staff_uas_approval' => isset($input['staff_uas_approval'][$mhs_nid])? $input['staff_uas_approval'][$mhs_nid]:'0',
                        'manager_krs_approval' => isset($input['manager_krs_approval'][$mhs_nid])? $input['manager_krs_approval'][$mhs_nid]:'0',
                        'manager_uts_approval' => isset($input['manager_uts_approval'][$mhs_nid])? $input['manager_uts_approval'][$mhs_nid]:'0',
                        'manager_uas_approval' => isset($input['manager_uas_approval'][$mhs_nid])? $input['manager_uas_approval'][$mhs_nid]:'0',
                        'admin_krs_approval' => isset($input['admin_krs_approval'][$mhs_nid])? $input['admin_krs_approval'][$mhs_nid]:'0',
                        'admin_uts_approval' => isset($input['admin_uts_approval'][$mhs_nid])? $input['admin_uts_approval'][$mhs_nid]:'0',
                        'admin_uas_approval' => isset($input['admin_uas_approval'][$mhs_nid])? $input['admin_uas_approval'][$mhs_nid]:'0',
                    );
                    
                    $sum1 = array_sum($input['nominal'][$mhs_nid]);
                    $sum2 = array_sum($approval);
                    
                    if($sum1 != 0 OR $sum2 != 0){
                        
                        $title = $sta_title . ' - ' . $input['nim_title'][$mhs_nid];
                        $komponen_nominal = empty($input['nominal'][$mhs_nid])? NULL:$input['nominal'][$mhs_nid];
                        $keuangan_nid = $input['keuangan_nid'][$mhs_nid];
                        _create_keuangan_node($title, $keuangan_nid, $mhs_nid, $sta_nid,$komponen_nominal, $approval);
                        $count++;
                    }
                                                            
                }
//            }
            drupal_set_message("Sukses Mengupdate");
            break;
        case 'Print All':
            $angkatan = $form_state['values']['angkatan'];
            $prodi = $form_state['values']['prodi'];
            drupal_goto("input-pembayaran/print/$prodi/$angkatan/$sta_nid");
            break;
        default:
            break;
    }
    
     $form_state['rebuild'] = TRUE;
}

function _create_keuangan_node($title, $keuangan_nid, $mhs_nid, $sta_nid, $komponens = array(), $approval = array()){
    global $user;
    
    //jika yang login admin maka value dari staf dan manager approval di replace
    if(in_array('BSF Admin', $user->roles)){
        $approval['staff_krs_approval'] = $approval['admin_krs_approval']; 
        $approval['staff_uts_approval'] = $approval['admin_uts_approval'];
        $approval['staff_uas_approval'] = $approval['admin_uas_approval'];
        $approval['manager_krs_approval'] = $approval['admin_krs_approval'];
        $approval['manager_uts_approval'] = $approval['admin_uts_approval'];
        $approval['manager_uas_approval'] = $approval['admin_uas_approval'];
    }
    
    if(empty($keuangan_nid)){
        // Create node     
        $keuangan = new stdClass();
        $keuangan->type = 'bsf_keuangan';
        node_object_prepare($keuangan);
        $keuangan->title = $title;
        $keuangan->status = 1;
        $keuangan->uid = $user->uid;
        $keuangan->language = LANGUAGE_NONE;
        $keuangan->field_bsf_mahasiswa['und'][0]['target_id'] = $mhs_nid;
        $keuangan->field_bsf_semester_akademik['und'][0]['target_id'] = $sta_nid;
//        node_save($keuangan); 
        
        // Create and save field collection 'Pembayaran Komponen' for node   
        foreach(element_children($komponens) as $komp_nid){
            $komponens[$komp_nid] = empty($komponens[$komp_nid])? 0 : $komponens[$komp_nid];
            if(isset($komponens[$komp_nid])){

                $field_collection_item = entity_create('field_collection_item', array('field_name' => 'field_bsf_pembayaran_komponen'));            
                $field_collection_item->setHostEntity('node', $keuangan,LANGUAGE_NONE,true);
                $field_collection_item->field_bsf_komponen_nominal[LANGUAGE_NONE][]['target_id'] = $komp_nid;
                $field_collection_item->field_bsf_pembayaran[LANGUAGE_NONE][]['value'] = $komponens[$komp_nid];
//                $field_collection_item->save();

            }
        }

        // Create and save field collection 'Approval Role Staff' for node
        $field_collection_item = entity_create('field_collection_item', array('field_name' => 'field_bsf_approval_role_staff'));            
        $field_collection_item->setHostEntity('node', $keuangan,LANGUAGE_NONE,true);
        $field_collection_item->field_bsf_approval_krs[LANGUAGE_NONE][]['value'] = $approval['staff_krs_approval'];
        $field_collection_item->field_bsf_approval_uts[LANGUAGE_NONE][]['value'] = $approval['staff_uts_approval'];
        $field_collection_item->field_bsf_approval_uas[LANGUAGE_NONE][]['value'] = $approval['staff_uas_approval'];
//        $field_collection_item->save();

        // Create and save field collection 'Approval Role Manager' for node
        $field_collection_item = entity_create('field_collection_item', array('field_name' => 'field_bsf_approval_role_manager'));            
        $field_collection_item->setHostEntity('node', $keuangan,LANGUAGE_NONE,true);
        $field_collection_item->field_bsf_approval_krs[LANGUAGE_NONE][]['value'] = $approval['manager_krs_approval'];
        $field_collection_item->field_bsf_approval_uts[LANGUAGE_NONE][]['value'] = $approval['manager_uts_approval'];
        $field_collection_item->field_bsf_approval_uas[LANGUAGE_NONE][]['value'] = $approval['manager_uas_approval'];
        node_submit($keuangan);
        $field_collection_item->save();
    }
    else{
        $keuangan = node_load($keuangan_nid); 
        $keuangan->revision = 1;
           
        $items = field_get_items('node', $keuangan, 'field_bsf_pembayaran_komponen');                
        $item_array = array();
        foreach ($items as $item) {          
            $fc = field_collection_field_get_entity($item);
            $komp_nid = $fc->field_bsf_komponen_nominal[LANGUAGE_NONE][0]['target_id'];
            $item_array[$komp_nid] = $item['value']; //variable untuk menyimpan item yang ada di node keuangan
//            $fc->field_bsf_pembayaran[LANGUAGE_NONE][0]['value'] = $komponens[$komp_nid];
            //$fc->save();

        }
  
        $items_node_array = array();
        foreach(element_children($komponens) as $komp_nid){
                $item_array[$komp_nid] = isset($item_array[$komp_nid])?(int)$item_array[$komp_nid]:null;
                $field_collection_item = entity_load('field_collection_item', array($item_array[$komp_nid])); // Load that field collection item.               
                if(empty($field_collection_item)){
                    $field_collection_item = entity_create('field_collection_item', array('field_name' => 'field_bsf_pembayaran_komponen'));            
                    $field_collection_item->setHostEntity('node', $keuangan,LANGUAGE_NONE,true);
                    $field_collection_item->field_bsf_komponen_nominal[LANGUAGE_NONE][]['target_id'] = $komp_nid;
                    $field_collection_item->field_bsf_pembayaran[LANGUAGE_NONE][]['value'] = $komponens[$komp_nid];
                }
                else{
//                    $komp_nid = $field_collection_item[$item_array[$komp_nid]]->field_bsf_komponen_nominal[LANGUAGE_NONE][0]['target_id'];
                    $items_node_array[$komp_nid] = $field_collection_item[$item_array[$komp_nid]]->field_bsf_pembayaran[LANGUAGE_NONE][0]['value'];
                    $field_collection_item[$item_array[$komp_nid]]->field_bsf_pembayaran[LANGUAGE_NONE][0]['value'] = $komponens[$komp_nid];
                    $item_array[$komp_nid] = $komponens[$komp_nid];
                }
                
    
        }

        $approvals_node = array();
        // Update and save field collection 'Approval Role Staff' for node
        $item_value = (int)$keuangan->field_bsf_approval_role_staff[LANGUAGE_NONE][0]['value']; // Get field collection item value.       
        $field_collection_item = entity_load('field_collection_item', array($item_value)); // Load that field collection item.               
        
        //set $approvals_node untuk mengetahui apakah ada yang berubah
        $approvals_node['staff_krs_approval'] = $field_collection_item[$item_value]->field_bsf_approval_krs[LANGUAGE_NONE][0]['value'];
        $approvals_node['staff_uts_approval'] = $field_collection_item[$item_value]->field_bsf_approval_uts[LANGUAGE_NONE][0]['value'];
        $approvals_node['staff_uas_approval'] = $field_collection_item[$item_value]->field_bsf_approval_uas[LANGUAGE_NONE][0]['value'];
        $field_collection_item[$item_value]->field_bsf_approval_krs[LANGUAGE_NONE][0]['value'] = $approval['staff_krs_approval'];
        $field_collection_item[$item_value]->field_bsf_approval_uts[LANGUAGE_NONE][0]['value'] = $approval['staff_uts_approval'];
        $field_collection_item[$item_value]->field_bsf_approval_uas[LANGUAGE_NONE][0]['value'] = $approval['staff_uas_approval'];
        //$field_collection_item[$item_value]->save();

        // Update and save field collection 'Approval Role Manager' for node
        $item_value = (int)$keuangan->field_bsf_approval_role_manager[LANGUAGE_NONE][0]['value']; // Get field collection item value.       
        $field_collection_item = entity_load('field_collection_item', array($item_value)); // Load that field collection item.               
        $approvals_node['manager_krs_approval'] = $field_collection_item[$item_value]->field_bsf_approval_krs[LANGUAGE_NONE][0]['value'];
        $approvals_node['manager_uts_approval'] = $field_collection_item[$item_value]->field_bsf_approval_uts[LANGUAGE_NONE][0]['value'];
        $approvals_node['manager_uas_approval'] = $field_collection_item[$item_value]->field_bsf_approval_uas[LANGUAGE_NONE][0]['value'];
        $field_collection_item[$item_value]->field_bsf_approval_krs[LANGUAGE_NONE][0]['value'] = $approval['manager_krs_approval'];
        $field_collection_item[$item_value]->field_bsf_approval_uts[LANGUAGE_NONE][0]['value'] = $approval['manager_uts_approval'];
        $field_collection_item[$item_value]->field_bsf_approval_uas[LANGUAGE_NONE][0]['value'] = $approval['manager_uas_approval'];
        
        //Jika ada yang diupdate maka save
        if($komponens != $items_node_array OR $approval != $approvals_node){
            $field_collection_item[$item_value]->save();
        }
        
    }
         
}
