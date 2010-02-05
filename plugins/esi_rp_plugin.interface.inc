<?php
// $Id: esi_rp_plugin.interface.inc$

/**
 * The interface for all esi reverse proxy plugin objects.
 */
interface Drupal_ESI_Reverse_Proxy_Plugin_Interface {
  
  /**
   * Some from of initialise
   */
  
  /**
   * Some from of settings
   */
  
  /**
   * TODO: Does this live here or with the reverse proxy module?? 
   *          Inital thoughts are we need this self contained as it would be nice to not have to load module to do the discovery
   *          also in some cases hooking into the reserve proxy isnt done via a module?
   * Registry of plugins in the system
   * @return array RP plugin registry data
   */
  static function rp_register();
  
  /**
   * Provides any extra setting information for the plugin
   * 
   * @param $settings
   * @return array
   */  
  function rp_settings($settings);
  
  /**
   * Flag for default esi reverse proxy plugin
   * @return bool
   */
  static function rp_is_default();
}

