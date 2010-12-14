<?php
// $Id: esi.inc,v 1.2 2010/11/17 11:37:25 manarth Exp $
/**
 * @file
 *   Helper functions for the ESI module.
 */

/**
 * Get the current seed key.
 */
function _esi__get_seed_key() {
  $seed = variable_get('esi_seed_key', FALSE);
  if (!$seed) {
    $seed = _esi__rotate_seed_key();
  }
  return $seed;
}

/**
 * Rotate the seed key.
 */
function _esi__rotate_seed_key() {
  $seed = _esi__get_random_seed();
  variable_set('esi_seed_key', $seed);
  variable_set('esi_seed_key_last_changed', time());
  return $seed;
}

/**
 * Get a random 32-character string
 */
function _esi__get_random_seed() {
  $seed = '';
  for ($i=0; $i<32; $i++) {
    // get a random character from the printable ASCII character set: 32-176
    $seed += chr(mt_rand(32, 176));
  }
  return $seed;
}



/**
 * Get the hash for a set of roles.
 *
 * @param array $rids
 *   An array of role-ids
 */
function _esi__get_roles_hash($rids) {
  $seed = _esi__get_seed_key();
  $hash = implode(':', $rids);
  $hash = md5($seed . md5($hash));
  return $hash;
}



/**
 * Get the themed HTML for a particular block
 *
 * @param String $theme
 *   The name of the theme: e.g. "garland"
 * @param String $region
 *   The name of the region the block is in: e.g. "left"
 * @param String $module
 * @param String $delta
 */
function _esi__get_block($theme, $region, $module, $delta) {
  global $theme_key;
  $theme_key = $theme;
  init_theme();

  $blocks = block_list($region);
  return $blocks["{$module}_{$delta}"];
}

/**
 * Get / Set the config for a particular block.
 */
function _esi__block_settings($module, $delta, $config = NULL) {
  // TODO: replace with something more suited to in-code config than variables.

  $key = "{$module}_{$delta}";
  $global = variable_get('esi_block_config', array());

  if ($config) {
    $global[$key] = $config;
    variable_set('esi_block_config', $global);
  }
  elseif (array_key_exists($key, $global)) {
    $config = $global[$key];
  }
  else {
    $config = new stdClass;
    $config->enabled = ESI__BLOCK_CONFIG_DEFAULT__IS_ENABLED;
    $config->ttl     = ESI__BLOCK_CONFIG_DEFAULT__TTL;
  }

  return $config;
}



/**
 * Get a list of possible ttl choices.
 */
function _esi__ttl_options($current_ttl) {
  $options = array(
    '5'     => t('@count seconds', array('@count' => 5)),
    '30'    => t('@count seconds', array('@count' => 30)),
    '60'    => t('1 minute'),
    '300'   => t('@count minutes', array('@count' => 5)),
    '1800'  => t('@count minutes', array('@count' => 30)),
    '3600'  => t('1 hour'),
    '10800' => t('@count hours', array('@count' => 3)),
    '21600' => t('@count hours', array('@count' => 6)),
    '43200' => t('@count hours', array('@count' => 12)),
    '86400' => t('1 day'),
  );
  // if the given ttl isn't one of our options, add the current ttl as a custom option.
  if (!array_key_exists($current_ttl, $options)) {
    $options[$current_ttl] = format_plural($current_ttl, 'Custom: @count second', 'Custom: @count seconds');
  }
  return $options;
}

