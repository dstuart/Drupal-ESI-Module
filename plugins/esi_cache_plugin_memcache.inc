<?php
// $Id: esi_cache_plugin_memcache.inc$

class esi_cache_plugin_memcache implements Drupal_ESI_Cache_Plugin_Interface{
  
  function init(){
    
  }
  
  static function cache_is_default(){
    return FALSE;
  }
  
  static function cache_register(){
    return array(
             'name' => 'Memcache',
             'description' => 'Memcache blah blah blah'
           );
  }
  
  function cache_set($cache_name, $value){
    
  }
  
  function cache_get($cache_name){
    
  }
  
}