<?php
// $Id: esi.theme.inc,v 1.2 2010/11/17 11:37:25 manarth Exp $
/**
 * @file
 *   Theme handlers for the ESI module.
 */

/**
 * Replacement for core theme function: thene_blocks
 */
function esi__theme_blocks($region) {
  $output = '';
  // load our helper file.
  require_once(dirname(__FILE__) . '/esi.inc');

  if ($list = block_list($region)) {
    foreach ($list as $key => $block) {
      // if ESI's enabled on the block, add an ESI tag instead of block content.
      $esi_config = _esi__block_settings($block->module, $block->delta);
      $output .= $esi_config->enabled
        ? theme('esi_tag', $block)
        : theme('block', $block);
    }
  }

  // Add any content assigned to this region through drupal_set_content() calls.
  $output .= drupal_get_content($region);

  return $output;
}


/**
 * Create the ESI-tag for a particular block.
 */
function theme_esi_tag($block) {
  global $theme_key, $base_url;

  $bid = "{$theme_key}:{$block->region}:{$block->module}:{$block->delta}";
  $src = $base_url . "/esi/block/{$bid}";

  $params = array();

  // if the block uses per-page cacheing, add the page param to the URL.
  if ($block->cache & BLOCK_CACHE_PER_PAGE) {
    $src .= '/' . base64_encode($_GET['q']);
  }

  // Finally, if the cache-mode is PER-USER or PER-ROLE, advise the proxy.
  // Ideally, the proxy will remove this parameter.
  if ($block->cache & BLOCK_CACHE_PER_USER || $block->cache & BLOCK_CACHE_PER_ROLE) {
    $src .= '/CACHE=' . ($block->cache & BLOCK_CACHE_PER_USER ? 'USER' : 'ROLE');
  }

  $output = '<esi:include src="' . $src . '" />';
  return $output;
}
