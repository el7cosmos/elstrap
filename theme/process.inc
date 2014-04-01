<?php
/**
 * @file
 * process.inc
 */

/**
 * Process variables for region.tpl.php
 *
 * @see region.tpl.php
 */
function elstrap_process_region(&$variables) {
  if ($variables['region'] == 'footer') {
    $key = array_search('container', $variables['attributes_array']['class']);
    unset($variables['attributes_array']['class'][$key]);
    $variables['attributes_array']['class'][] = 'text-center';
    $variables['attributes'] = drupal_attributes($variables['attributes_array']);
  }
}

/**
 * Process variables for theme_html5_tools_time()
 *
 * @see theme_html5_tools_time()
 */
function elstrap_process_html5_tools_time(&$variables) {
  $variables['pubdate'] = FALSE;
}
