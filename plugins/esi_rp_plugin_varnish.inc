<?php
// $Id: esi.rp_plugin_varnish.inc$

class esi_rp_plugin_varnish implements Drupal_ESI_Reverse_Proxy_Plugin_Interface{
  
  static function rp_is_default(){
    return TRUE;
  }
  
  function init(){
    
  }
  
  static function rp_register(){
    return array(
             'name'        => 'Varnish',
             'description' => 'Varish is bla de blah'
           );
  }

  function rp_settings($settings){
    return $settings;
  }
}