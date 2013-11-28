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
    $icon = $size . 'x' . $size;
    $attributes = array(
      'rel' => 'apple-touch-icon',
      'sizes' => $size . 'x' . $size,
      'href' => url('apple-touch-icon-' . $size . 'x' . $size . '.png', array('absolute' => TRUE)),
    );
    drupal_add_html_head_link($attributes);
  }

  $png = array('16', '32', '96', '160', '196');
  foreach ($png as $size) {
    $icon = $size . 'x' . $size;
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
 * Preprocess variables for page.tpl.php
 *
 * @see page.tpl.php
 */
function elstrap_preprocess_page(&$variables) {
  // Add information about the number of sidebars.
  if (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-4"';
  }
  elseif (!empty($variables['page']['sidebar_first']) || !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-8"';
  }
  else {
    $variables['content_column_class'] = NULL;
  }

  $content = $variables['page']['content'];
  $path = drupal_is_front_page() ? '<front>' : $_GET['q'];
  $links = language_negotiation_get_switch_links('language', $path);

  $vars = array(
    'links' => $links->links,
    'attributes' => array('class' => array('dropdown-menu')),
    'language' => $variables['language']->language,
  );

  $variables['language_menu'] = theme('links__locale_menu', $vars);

  if (!drupal_is_front_page()) {
    if (isset($content['system_main']['nodes']) || isset($content['system_main']['pager'])) {
      $variables['theme_hook_suggestions'][] = 'page__no_panel';
    }
    if (in_array('page__article', $variables['theme_hook_suggestions'])) {
      $variables['theme_hook_suggestions'][] = 'page__no_panel';
    }
    if (in_array('page__infographics', $variables['theme_hook_suggestions'])) {
      $variables['theme_hook_suggestions'][] = 'page__no_panel';
    }
  }
}

/**
 * Preprocess variables for block.tpl.php
 *
 * @see block.tpl.php
 */
function elstrap_preprocess_block(&$variables, $hook) {
  $block = $variables['block'];
  if ($block->module != 'system' && $block->delta != 'main') {
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

  $variables['submitted'] = t('<i class="fa fa-calendar"></i> !datetime &middot; <i class="fa fa-user"></i> !username', array('!username' => $variables['name'], '!datetime' => theme('html5_tools_time', array('date' => $variables['date'], 'isodate' => format_date($variables['created'], 'html5_tools_iso8601')))));
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
 * Preprocess variables for theme_image_formatter()
 *
 * @see theme_image_formatter()
 */
function elstrap_preprocess_image_formatter(&$variables) {
  $variables['item']['attributes']['class'][] = 'img-thumbnail';
  $variables['item']['attributes']['class'][] = 'img-responsive';
}
