<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


function input_pembayaran_print(){
    global $base_path;
    require_once drupal_get_path('module', 'input_display').'/forms/konversi_rupiah_terbilang.inc';
    
   $prodi_node = node_load(arg(2));
   $angkatan_nid = arg(3);
   $sta_node = node_load(arg(4));
   
//   $query_komponen = new EntityFieldQuery();
//    $query_komponen->entityCondition('entity_type', 'node')
//      ->entityCondition('bundle', 'bsf_komponen_nominal')
//      ->propertyCondition('status', 1)
//      ->fieldCondition('field_bsf_angkatan','target_id',$angkatan_nid,'=');  
//      
//    $result = $query_komponen->execute();
//    foreach(element_children($result['node']) as $komponen_nid){
//        $komp_node = node_load($komponen_nid);
//        $komp_array[$komponen_nid] = $komp_node->title;
//    }
     $query_mhs = new EntityFieldQuery();
    $query_mhs->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'bsf_mahasiswa')
      ->propertyCondition('status', 1)
      ->fieldCondition('field_bsf_angkatan','target_id',$angkatan_nid,'=')
      ->fieldCondition('field_bsf_program_studi','target_id',$prodi_node->nid,'=');
      //->fieldCondition('field_bsf_program_kuliah','target_id',$prokul,'=');

    $result = $query_mhs->execute();
    
      $html .= '<html><head><title>Print Pembayaran</title>';
      $html .= display_pembayaran_get_style_print();
      $html .= '</head><body>';
    $path_jpg = $base_path.drupal_get_path('module', 'input_display').'/images/univbakrie.jpg';
    foreach(element_children($result['node']) as $mhs_nid){
        $mhs_node = node_load($mhs_nid);
        $mhs_nama = $mhs_node->field_bsf_nama['und'][0]['value'];
        $mhs_nim = $mhs_node->field_bsf_nim['und'][0]['value'];
        $html .= "<table border=0><tr><td width=230px><img width=220 src='$path_jpg'></td>"
                . "<td width=300px><strong>$prodi_node->title</strong></td>"
                . "<td width=190px><table><tr><td width=100px id=receiptbox1>RECEIPT</td><td width=30px id=receiptbox2>&nbsp; </td></tr></table></td></tr></table>".
               "<table border=0><tr><td width=200px>Sudah terima dari</td><td width=300px id=singleline>: $mhs_nama</td><td id=singleline width=220px>NIM:$mhs_nim</td></tr>".
               "<tr><td width=200px>Untuk Pembayaran</td><td width=300px id=singleline>: </td><td width=220px id=singleline>Semester:$sta_node->title</td></tr></table><br/>";
     
        $query_keuangan = new EntityFieldQuery();
        $query_keuangan->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'bsf_keuangan')
          ->propertyCondition('status', 1)
          ->fieldCondition('field_bsf_mahasiswa','target_id',$mhs_nid,'=')
          ->fieldCondition('field_bsf_semester_akademik','target_id',$sta_node->nid,'=');
        $result = $query_keuangan->execute();
        
        $komp_nominal_array = array();
        $komp_array_detil = array();
        $komp_array = array();
        if($result){
                
            $keuangan_nid = array_keys($result['node']);
            $keuangan_node = node_load($keuangan_nid[0]);

            $items = field_get_items('node', $keuangan_node, 'field_bsf_pembayaran_komponen');                
            foreach ($items as $item) {

                $fc = field_collection_field_get_entity($item);
                $komp_nominal_id = $fc->field_bsf_komponen_nominal['und'][0]['target_id'];
                $komp_node = node_load($komp_nominal_id);
                $komp_parent_node = node_load($komp_node->field_bsf_komponen['und'][0]['target_id']);
                $komp_array_detil[$komp_nominal_id][] = $fc->field_bsf_pembayaran['und'][0]['value'];
                $komp_nominal_array[$komp_nominal_id] = array_sum($komp_array_detil[$komp_nominal_id]);
                $komp_array[$komp_nominal_id] = $komp_parent_node->title;
            }
        }
           $html .= '<table border=0>';
           $no = 1;
           $total_pembayaran = 0;
           foreach($komp_array as $komp_nid => $komp_nama){

               $komp_value = array_key_exists($komp_nid, $komp_nominal_array)? $komp_nominal_array[$komp_nid]:0;
               $komp_value_format = number_format($komp_value, 0, ',', '.');
               $total_pembayaran += $komp_value;
               $html .= "<tr><td width=20px>".$no++."</td><td width=350px>$komp_nama</td><td width=300px id=singleline>Rp. $komp_value_format,-</td></tr>";
           }
       
           for($i = $no; $i <= 8; $i++){
                $html .= "<tr><td>".$no++."</td><td id=singleline>&nbsp;</td><td width=300px id=singleline>Rp.</td></tr>";
            }
            
           $total_pembayaran_format = number_format($total_pembayaran, 0, ',', '.');
           $terbilang = ucfirst(terbilang($total_pembayaran));
           $tanggal = date('d F Y');
          $html .= "<tr><td width=20px></td><td width=400px>TOTAL PEMBAYARAN : </td><td width=300px id=doubleline>Rp. $total_pembayaran_format</td></tr></table><br/>"
           . "<table border=0><tr><td width=720px>Terbilang :</td></tr><tr><td id=singleline> $terbilang rupiah<br/></td></tr></table><br/>"
           . '<table border=0><tr><td width=240px><table><tr><td width=30px height=30px id=box>&nbsp; </td><td>CASH</td></tr></table></td>'
           . '<td width=240px><table><tr><td width=30px height=30px id=box>&nbsp; </td><td>Transfer</td></tr></table></td>'
           . '<td width=240px><table><tr><td width=30px height=30px id=box>&nbsp; </td><td>Cheque</td></tr></table></td>'
           . '</table>'
           . "<table border=0><tr><td width=5px> </td><td width=355px>Bank Transfer :</td><td width=360px id=singleline>Jakarta, $tanggal</td></tr>"
           . '<tr><td width=5px valign=top>1</td><td>Permata Syariah cab Setiabudi Jakarta<br/>'
           . 'A/C : 0971 - 008 - 008<br/> a/n : Yayasan Pendidikan Bakrie</td><td></td></tr>'
           . '<tr><td width=5px valign=top>2</td><td>BCA Rasuna Epicentrum Jakarta<br/>'
           . 'A/C : 505 - 502 - 64 64<br/> a/n : Yayasan Pendidikan Bakrie</td><td></td></tr>'
           . '</table><br/>'
          . '<p id = footer></p>';

    }
        
    
    
   
    $html .= '</body></html>';
    print $html;

}

function laporan_pembayaran_print(){
    global $base_path;
    require_once drupal_get_path('module', 'input_display').'/forms/konversi_rupiah_terbilang.inc';
    
//   $prodi_nid = arg(2);
//   $angkatan_nid = arg(3);
   $sta_node = node_load(arg(2));
//   $tanggal_dari = arg(5);
//   $tanggal_sampai = arg(6);
    
//     $query_nominal = new EntityFieldQuery();
//        $query_nominal->entityCondition('entity_type', 'node')
//          ->entityCondition('bundle', 'bsf_keuangan')
//          ->propertyCondition('status', 1)
//          ->propertyCondition('changed', $tanggal_dari, '>=')
//          ->propertyCondition('changed', $tanggal_sampai, '<=')
//          ->fieldCondition('field_bsf_semester_akademik','target_id',$sta_nid,'=');
//        $result = $query_nominal->execute();
        $html = '';
//        if($result){       
            $laporan = variable_get('laporan_pembayaran');
            $keuangan_array = $laporan['input']['selected'];

            foreach($keuangan_array as $key => $keuangan_nid){
//            foreach(element_children($result['node']) as $keuangan_nid){
                $keuangan_node = node_load($keuangan_nid);
                $mhs_node = node_load($keuangan_node->field_bsf_mahasiswa['und'][0]['target_id']);
                
                $mhs_prodi = $mhs_node->field_bsf_program_studi['und'][0]['target_id'];
//                $mhs_angkatan = $mhs_node->field_bsf_angkatan['und'][0]['target_id'];
//               if(($angkatan_nid == $mhs_angkatan AND $prodi_nid == $mhs_prodi)
//                        OR ($prodi_nid == $mhs_prodi AND $angkatan_nid == 'all')
//                        OR ($prodi_nid == 'all' AND $angkatan_nid == $mhs_angkatan)
//                        OR ($prodi_nid == 'all' AND $angkatan_nid == 'all')){
                    
                    $items = field_get_items('node', $keuangan_node, 'field_bsf_pembayaran_komponen');
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
                    
                    $html .= '<html><head><title>Print Pembayaran</title>';
                    $html .= display_pembayaran_get_style_print();
                    $html .= '</head><body>';
                    $path_jpg = $base_path.drupal_get_path('module', 'input_display').'/images/univbakrie.jpg';
                    $path_jpg = 'sites/default/files/univbakrie.jpg';
                    
                    $mhs_nama = $mhs_node->field_bsf_nama['und'][0]['value'];
                    $mhs_nim = $mhs_node->field_bsf_nim['und'][0]['value'];
                    $prodi_node = node_load($mhs_prodi);
                    
                    //**************** HEADER **************\\
                    $html .= "<table id=tbheader-margin><tr><td width=200px><img width=150 src='$path_jpg'></td>"
                            . "<td width=230px><strong>$prodi_node->title</strong></td>"
                            . "<td width=140px><table><tr><td width=100px id=receiptbox1>RECEIPT</td><td width=30px id=receiptbox2>&nbsp; </td></tr></table></td></tr></table>";
                    
                     //**************** NAMA MAHASISWA **************\\
                    $html .= "<table id=tb-margin>"
                            . "<tr><td width=150px>Sudah terima dari</td><td width=250px id=singleline>: $mhs_nama</td><td id=singleline width=170px>NIM:$mhs_nim</td></tr>"
                            . "<tr><td>Untuk Pembayaran</td><td id=singleline>: </td><td id=singleline>Semester:$sta_node->title</td></tr></table><br/>";
                    
                     //**************** KOMPONEN PEMBAYARAN **************\\
                    $html .= '<table id=tb-margin>';
                    $no = 1;
                    $total_pembayaran = 0;
                    foreach($komp_array as $komp_nid => $komp_nama){

                        $komp_value = $komp_values[$komp_nid];
                        $komp_value_format = number_format($komp_value, 0, ',', '.');
                        $total_pembayaran += $komp_value;
                        $html .= "<tr><td width=20px>".$no++."</td><td width=300px>$komp_nama</td><td width=250px id=singleline>Rp. $komp_value_format,-</td></tr>";
                    }
                    for($i = $no; $i <= 8; $i++){
                        $html .= "<tr><td>".$no++."</td><td id=singleline>&nbsp;</td><td id=singleline>Rp.</td></tr>";
                    }
                    
                    
                    $total_pembayaran_format = number_format($total_pembayaran, 0, ',', '.');
                    $terbilang = ucfirst(terbilang($total_pembayaran));
                    $tanggal = date('d F Y');
                   $html .= "<tr><td></td><td>TOTAL PEMBAYARAN : </td><td id=doubleline>Rp. $total_pembayaran_format</td></tr>"
                         . "</table><br/>";
                   
                   //***************** TERBILANG **********************\\
                    $html .= "<table id=tb-margin>"
                            . "<tr><td width=570px>Terbilang :</td></tr>"
                            . "<tr><td id=singleline>$terbilang rupiah<br/></td></tr>"
                            . "</table><br/>";
                    
                    //***************** CASH, Transfer, Cheque ***********\\
                     $html .= '<table id=tb-margin>'
                             . '<tr>'
                                . '<td width=180px><table><tr><td id=box>&nbsp; </td><td>CASH</td></tr></table></td>'
                                . '<td width=180px><table><tr><td id=box>&nbsp; </td><td>Transfer</td></tr></table></td>'
                                . '<td width=180px><table><tr><td id=box>&nbsp; </td><td>Cheque</td></tr></table></td>'
                             . '</tr>'
                         . '</table>';
                             
                     //**************** Bank Dan TTD ***************\\
                      $html .= "<table id=tb-margin>"
                              . "<tr><td width=5px> </td><td width=305px>Bank Transfer :</td><td width=260px id=singleline>Jakarta, $tanggal</td></tr>"
                              . '<tr><td valign=top>1</td>'
                                  . '<td>Permata Syariah cab Setiabudi Jakarta<br/>'
                                       . 'A/C : 0971 - 008 - 008<br/> a/n : Yayasan Pendidikan Bakrie</td><td></td></tr>'
                             . '<tr><td width=5px valign=top>2</td>'
                                 . '<td>BCA Rasuna Epicentrum Jakarta<br/>'
                                       . 'A/C : 505 - 502 - 64 64<br/> a/n : Yayasan Pendidikan Bakrie</td><td></td></tr>'
                             . '</table>';
//                } 
                   //$html .= "<p id=footer></p>";
            }
//        }
  
 $html .= '</body></html>';
 //print $html;

  require_once libraries_get_path('dompdf').'/dompdf_config.inc.php';
  //$html = variable_get('cetak_pembayaran');
    $dompdf = new DOMPDF();
    $dompdf->load_html($html);
    //$dompdf->set_paper(DEFAULT_PDF_PAPER_SIZE, 'A4');
    $dompdf->render();
    $dompdf->stream("pembayaran-$tanggal.pdf");
}

function display_pembayaran_get_style_print(){
    $style = "<style>"
            . "@page { "
            . "margin-top: 25px; "
            . "margin-right: 30px;"
            . "margin-left: 30px;"
            . "margin-bottom: 0px; }"
            . "@media screen,print{"
            . "body{font: 9pt futura;}"
            . "#tbheader-margin{border:0; margin-top:8px; margin-left:50px;margin-right:50px}"
            . "#tb-margin{border:0; margin-left:50px;margin-right:50px}"
            . "#receiptbox1{ background-color: grey;
                font-weight: bold;
                color: white;
                text-align: center}"
            . "#receiptbox2{ background-color: green;}"
            . "#doubleline{ border-bottom: double}"
            . "#singleline{ border-bottom: 1px solid}"
            . "#box{ border: 2px solid; width:20px; height:20px}"
            //. "#footer {page-break-after:always;}"
            . "}"
            . "</style>";
    
    return $style;
}