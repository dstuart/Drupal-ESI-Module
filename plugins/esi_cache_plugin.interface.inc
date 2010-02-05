<?php
// $Id: esi_cache_plugin.interface.inc$

/**
 * The interface for all esi cache plugin objects.
 */
interface Drupal_ESI_Cache_Plugin_Interface {
  /**
   * Sets the cache using a key value pairing
   *
   * @param string $cache_name
   * the name of the cache
   *
   * @param string $value
   * The value of the cache
   */
  function cache_set($cache_name, $value);
  
  /**
   * Remove a filter from the query
   *
   * @param string $field
   * the facet field to remove
   *
   * @param string $value
   * The facet value to remove
   * This value can be NULL
   */
  function cache_get($cache_name);
  
  /**
   * Some from of initialise
   */
  
  /**
   * Registry of plugins in the system
   */
  static function cache_register();
  
    /**
   * Flag for default esi cache plugin
   * @return bool
   */
  static function cache_is_default();
}

