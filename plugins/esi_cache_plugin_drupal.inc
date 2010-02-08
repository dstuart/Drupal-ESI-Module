<?php
// $Id: esi_cache_plugin_drupal.inc$

/**
 * This implements the default esi caching class which uses Drupal and any applicable caching
 * mechanisims it has turned on
 * @author dstuart
 *
 */

class esi_cache_plugin_drupal implements Drupal_ESI_Cache_Plugin_Interface{
  
  function init(){
    
  }
  
  static function cache_is_default(){
    return TRUE;
  }
  
  static function cache_register(){
    return array(
             'name' => 'Drupal',
             'description' => 'Implements standard drupal esi calls using an Drupal caching structure enabled'
           );
  }
  
  function cache_set($cache_name, $value){
    
  }
  
  function cache_get($cache_name){
    
  }
  
}