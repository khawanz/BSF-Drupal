<?php

// Class for accessing BIG MSSQL data
Class BigAccess {
    protected static $host = '192.168.1.15';
    protected static $user = 'bigadmin';
    protected static $pass = '12920.b16';
    
    static function query($sql) {
        $con = mssql_connect(self::$host,self::$user,self::$pass) or die('Could not connect to the server!');
        
        $rows = array();
        $result = mssql_query($sql, $con);
        
        while ($row = mssql_fetch_object($result)) {
            $rows[] = $row;
        }
        
        return $rows;
    }
    
    // $last_id: fetch data from $last_id,
    // sometimes it is needed because drupal has saved previous values
    static function getDepartments($last_id = NULL, $is_serialized = NULL) {
        //$sql = "SELECT * FROM bsm_course_categories";
        $sql = "SELECT cat.id AS cat_id, cat.name AS cat_name, cat.description AS cat_description, sx.kode AS sx_kode, sx.deskripsi AS sx_deskripsi FROM bsm_course_categories cat 
                INNER JOIN bsm_kd_jenjang_strata_program_studi sx ON cat.kode_jenjang = sx.kode";
        
        if($last_id > 0) {
            $sql .= " WHERE cat.id > {$last_id}";
        }
        
        $sql .= " ORDER BY cat.id";
        
        $rows = self::query($sql);
        $data = $is_serialized ? serialize($rows) : $rows;
        
        return $data;
    }
    
    // $last_id: fetch data from $last_id,
    // sometimes it is needed because drupal has saved previous values
    static function getPrograms($last_id = NULL, $is_serialized = NULL) {
        //$sql = "SELECT * FROM bsm_program_kuliah";
        $sql = "SELECT pk.id_program_kuliah AS pk_id_program_kuliah, pk.nama_program AS pk_nama_program, cat.id AS cat_id, cat.name AS cat_name, sx.kode AS sx_kode, sx.deskripsi AS sx_deskripsi
                FROM bsm_program_kuliah pk
                INNER JOIN bsm_course_categories cat ON pk.category=cat.id
                INNER JOIN bsm_kd_jenjang_strata_program_studi sx ON cat.kode_jenjang=sx.kode";
        
        if($last_id > 0) {
            $sql .= " WHERE pk.id_program_kuliah > {$last_id}";
        }
        
        $sql .= " ORDER BY pk.id_program_kuliah";
        
        $rows = self::query($sql);
        $data = $is_serialized ? serialize($rows) : $rows;
        
        return $data;
    }
    
    // $last_id: fetch data from $last_id,
    // sometimes it is needed because drupal has saved previous values
    static function getClasses($last_id = NULL, $is_serialized = NULL) {
        $sql = "SELECT * FROM bsm_kelompok_mahasiswa";
        
        if($last_id > 0) {
            $sql .= " WHERE id_kelompok_mahasiswa > {$last_id}";
        }
        
        $sql .= " ORDER BY id_kelompok_mahasiswa";
        
        $rows = self::query($sql);
        $data = $is_serialized ? serialize($rows) : $rows;
        
        return $data;
    }
    
    // $last_id: fetch data from $last_id,
    // sometimes it is needed because drupal has saved previous values
    static function getStudentTypes($last_id = NULL, $is_serialized = NULL) {
        $sql = "SELECT * FROM bsm_tipe_mahasiswa";
        
        if($last_id > 0) {
            $sql .= " WHERE id > {$last_id}";
        }
        
        $sql .= " ORDER BY id";
        
        $rows = self::query($sql);
        $data = $is_serialized ? serialize($rows) : $rows;
        
        return $data;
    }
    
    // $last_id: fetch data from $last_id,
    // sometimes it is needed because drupal has saved previous values
    static function getStudents($last_id = NULL, $is_serialized = NULL) {
        // scat.course_category: 1, 2, 16, 17, 18, 22, 23, 24, 25, 26
        $sql = "SELECT	m.pn_uid AS m_pn_uid, m.nim AS m_nim, m.nama AS m_nama, 
                        m.kelompok_mahasiswa AS m_kelompok_mahasiswa, m.tipe_mahasiswa AS m_tipe_mahasiswa,
                        scat.course_category AS scat_course_category, scat.program_kuliah AS scat_program_kuliah
                FROM bsm_mahasiswa m
                INNER JOIN bsm_student_categories scat ON m.pn_uid=scat.users
                WHERE m.status_mahasiswa IN ('A', 'C', 'N')"; // AND scat.course_category=1";
        
        if($last_id > 0) {
            $sql .= " AND m.pn_uid > {$last_id}";
        }
        
        $sql .= " ORDER BY m.pn_uid";
        
        $rows = self::query($sql);
        $data = $is_serialized ? serialize($rows) : $rows;
        
        return $data;
    }
    
    // $last_tahun_ajaran: fetch data from $last_tahun_ajaran,
    // sometimes it is needed because drupal has saved previous values
    static function getSemesterYears($last_tahun_ajaran = NULL, $is_serialized = NULL) {
        $sql = "SELECT DISTINCT sta.tahun_ajaran AS sta_tahun_ajaran
                FROM bsm_semester_tahun_ajaran sta";
        
        if($last_tahun_ajaran > 0) {
            $sql .= " WHERE sta.tahun_ajaran > {$last_tahun_ajaran}";
        }

        $rows = self::query($sql);
        $data = $is_serialized ? serialize($rows) : $rows;
        
        return $data;
    }
}