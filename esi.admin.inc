<?php
// $Id: esi.admin.inc$


/**
 * @file
 *   Administrative pages for the ESI.
 */

function esi_settings() {
  $form = array();
  $form['esi_service_path'] = array(
    '#type' => 'textfield',
    '#title' => t('ESI service path'),
    '#default_value' => variable_get('esi_service_path', drupal_get_path('module', 'esi').'/esi.php'),
    '#description' => t('The path to the ESI service controller.'),
  );
  // Add grouping for rp plugin
  $form['esi_rp'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reverse Proxy Settings'),
    '#collapsed' => FALSE,
    '#collapsible' => FALSE,
  );
  $options = esi_get_rp_plugins();
  $form['esi_rp']['esi_rp_plugins'] = array(
    '#type' => 'select',
    '#title' => t('Reverse proxy'),
    '#default_value' => variable_get('esi_rp_plugin', 'default'),
    '#options' => $options,
    '#description' => t('The currently defined reverse proxy to use with ESI.'),
  );
  $form = esi_settings_extra('default', $form);
  
  // Add grouping for cache plugin
  $form['esi_cache'] = array(
    '#type' => 'fieldset',
    '#title' => t('Reverse Proxy Settings'),
    '#collapsed' => FALSE,
    '#collapsible' => FALSE,
  ); 
  $options = drupal_map_assoc(esi_get_cache_plugins());
  $form['esi_cache']['esi_cache_plugins'] = array(
    '#type' => 'select',
    '#title' => t('Caching plugin'),
    '#default_value' => variable_get('esi_cache_plugin', 'default'),
    '#options' => $options,
    '#description' => t('The currently defined cache plugin.'),
  );
  
  $form = esi_settings_extra('default', $form);
  return system_settings_form($form);
}