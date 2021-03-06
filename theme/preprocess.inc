<?php
/**
 * @file
 * preprocess.inc
 */

/**
 * Preprocess variables for html.tpl.php
 *
 * @see html.tpl.php
 */
function elstrap_preprocess_html(&$variables) {
  if (!drupal_get_title() && variable_get('site_slogan', '')) {
    $variables['head_title_array']['slogan'] = filter_xss(variable_get('site_slogan', ''));
  }
  $variables['head_title'] = implode(' &middot; ', $variables['head_title_array']);

  $apple = array('57', '60', '72', '76', '114', '120', '144', '152');
  foreach ($apple as $size) {
    $attributes = array(
      'rel' => 'apple-touch-icon',
      'sizes' => $size . 'x' . $size,
      'href' => url('apple-touch-icon-' . $size . 'x' . $size . '.png', array('absolute' => TRUE)),
    );
    drupal_add_html_head_link($attributes);
  }

  $png = array('16', '32', '96', '160', '196');
  foreach ($png as $size) {
    $attributes = array(
      'rel' => 'icon',
      'type' => 'image/png',
      'sizes' => $size . 'x' . $size,
      'href' => url('favicon-' . $size . 'x' . $size . '.png', array('absolute' => TRUE)),
    );
    drupal_add_html_head_link($attributes);
  }

  drupal_add_html_head(array('#tag' => 'meta', '#attributes' => array('name' => 'msapplication-TileColor', 'content' => '#428bca')), 'msapplication_tilecolor');
  drupal_add_html_head(array('#tag' => 'meta', '#attributes' => array('name' => 'msapplication-TileImage', 'content' => url('mstile-144x144.png', array('absolute' => TRUE)))), 'msapplication_tileimage');

  drupal_add_css('http://fonts.googleapis.com/css?family=Source+Sans+Pro:400,700,400italic,700italic|Source+Code+Pro:400,700', array('type' => 'external'));

  if (drupal_is_front_page()) {
    // $variables['attributes_array']['data-spy'] = 'scroll';
    // $variables['attributes_array']['data-target='] = '#navbar';

    // drupal_add_css(path_to_theme() . '/css/front.css');
    // drupal_add_js(path_to_theme() . '/bootstrap/js/scrollspy.js', array('type' => 'file', 'scope' => 'header', 'group' => JS_THEME));
    // drupal_add_js(path_to_theme() . '/js/jquery.stellar.js', $footer);
    // drupal_add_js(path_to_theme() . '/js/elstrap.front.js', $footer);
  }
}

/**
 * Preprocess variables for region.tpl.php
 *
 * @see region.tpl.php
 */
function elstrap_preprocess_region(&$variables, $hook) {
  switch ($variables['region']) {
    case 'navigation':
      global $language;

      $path = drupal_is_front_page() ? '<front>' : $_GET['q'];
      $links = language_negotiation_get_switch_links('language', $path);
      $vars = array(
        'links' => $links->links,
        'attributes' => array('class' => array('dropdown-menu')),
        'language' => $language->language,
      );
      $variables['language_native'] = $language->native;
      $variables['language_menu'] = theme('links__locale_menu', $vars);
      break;

    case 'content':
      $variables['panel'] = !isset($GLOBALS['pager_total']);
      break;
  }
}

/**
 * Preprocess variables for block.tpl.php
 *
 * @see block.tpl.php
 */
function elstrap_preprocess_block(&$variables, $hook) {
  $block = $variables['block'];

  if ($block->region == 'footer') {
    $variables['theme_hook_suggestions'][] = 'block__no_wrapper';
  }
  elseif ($block->module != 'system' && $block->delta != 'main') {
    $variables['classes_array'][] = 'panel';
    $variables['classes_array'][] = 'panel-default';
    $variables['classes_array'][] = 'clearfix';
    $variables['title_attributes_array']['class'][] = 'panel-title';
  }

  if ($block->module == 'adsense_managed') {
    $variables['classes_array'][] = 'text-center';
  }
}

/**
 * Preprocess variables for node.tpl.php
 *
 * @see node.tpl.php
 */
function elstrap_preprocess_node(&$variables) {
  $variables['classes_array'][] = 'panel';
  $variables['classes_array'][] = 'panel-' . elstrap_state_variable($variables['node']->nid);

  $variables['title_attributes_array']['class'][] = 'panel-title';
  if ($variables['teaser']) {
    $variables['title_attributes_array']['class'][] = 'pull-left';
  }

  $variables['submitted'] = t('<span class="fa fa-calendar"></span> !datetime &middot; <span class="fa fa-user"></span> !username', array('!username' => $variables['name'], '!datetime' => theme('html5_tools_time', array('date' => $variables['date'], 'isodate' => format_date($variables['created'], 'html5_tools_iso8601')))));
}

/**
 * Preprocess variables for theme_html_tag()
 *
 * @see theme_html_tag()
 */
function elstrap_preprocess_html_tag(&$variables) {
  $element = $variables['element'];
  if (($element['#tag'] == 'style' || $element['#tag'] == 'link') && !empty($element['#attributes']['type']) && $element['#attributes']['type'] == 'text/css') {
    unset($variables['element']['#attributes']['type']);
  }
}

/**
 * Preprocess variables for theme_html_tag()
 *
 * @see theme_html_tag()
 */
function elstrap_preprocess_html_tag__site_slogan(&$variables) {
  $variables['element']['#attributes']['class'][] = 'text-center';
  $variables['element']['#attributes']['class'][] = 'text-primary';
}

/**
 * Prerocess variables for theme_username()
 *
 * @see theme_username()
 */
function elstrap_preprocess_username(&$variables) {
  if (isset($variables['attributes_array']['xml:lang'])) {
    $variables['attributes_array']['lang'] = $variables['attributes_array']['xml:lang'];
  }
}

/**
 * Preprocess variables for theme_field()
 *
 * @see theme_field()
 */
function elstrap_preprocess_field(&$variables, $hook) {
  $element = $variables['element'];

  switch ($element['#field_name']) {
    case 'field_image':
      $variables['classes_array'][] = 'text-center';
      break;

    case 'field_sauce':
      $variables['classes_array'][] = 'alert';
      $variables['classes_array'][] = 'alert-info';
      break;
  }
}

/**
 * Preprocess variables for theme_bootstrap_modal().
 *
 * @see: theme_bootstrap_modal()
 */
function elstrap_preprocess_bootstrap_modal(&$variables) {
  if (!is_null($variables['size'])) {
    $variables['attributes']['class'][] = 'bs-modal-sm';
  }
}

/**
 * Preprocess variables for theme_pagespeed_insight_rule()
 *
 * @see theme_pagespeed_insight_rule()
 */
function elstrap_preprocess_pagespeed_insight_rule(&$variables) {
  if (!$variables['rule']['ruleImpact']) {
    $variables['state'] = 'success';
  }
  elseif ($variables['rule']['ruleImpact'] < 5) {
    $variables['state'] = 'warning';
  }
  else {
    $variables['state'] = 'danger';
  }

  $variables['id'] = drupal_html_id($variables['rule']['localizedRuleName']);
}
