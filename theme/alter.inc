<?php

/**
 * @file
 * alter.inc
 *
 * Contains various implementations of hook_*_alter().
 */

/**
 * Implements hook_js_alter().
 */
function elstrap_js_alter(&$javascript) {
  if (isset($javascript['sites/all/themes/bootstrap/js/misc/ajax.js'])) {
    $javascript['sites/all/themes/bootstrap/js/misc/ajax.js']['data'] = path_to_theme() . '/js/misc/ajax.js';
  }
}

/**
 * Implements hook_theme_registry_alter().
 */
function elstrap_theme_registry_alter(&$theme_registry) {
  $theme_registry['bootstrap_modal']['variables']['size'] = NULL;
}

/**
 * Implements hook_page_alter().
 */
function elstrap_page_alter(&$page) {
  global $language;
  $path = drupal_is_front_page() ? '<front>' : current_path();
  $abs_path = url($path, array('absolute' => TRUE));
  $title = drupal_get_title();

  $fb_share_options = array(
    'query' => array(
      'u' => $abs_path,
    ),
  );
  $body['fb_share'] = array(
    '#type' => 'link',
    '#title' => '<span class="fa fa-facebook"></span> Facebook',
    '#href' => url('https://www.facebook.com/sharer/sharer.php', $fb_share_options),
    '#options' => array(
      'html' => TRUE,
      'attributes' => array(
        'class' => array('btn', 'btn-block', 'btn-lg', 'btn-primary'),
        'target' => '_blank',
      ),
    ),
  );

  $tweet_options = array(
    'query' => array(
      'url' => $abs_path,
      'via' => 'el_abee',
      'text' => $title,
    ),
  );
  $body['tweet_button'] = array(
    '#type' => 'link',
    '#title' => '<span class="fa fa-twitter"></span> Twitter',
    '#href' => url('https://twitter.com/intent/tweet', $tweet_options),
    '#options' => array(
      'html' => TRUE,
      'attributes' => array(
        'class' => array('btn', 'btn-block', 'btn-lg', 'btn-info'),
        'target' => '_blank',
      ),
    ),
  );

  if ($language->language == 'en') {
    $gplus_lang = 'en_US';
  }
  else {
    $gplus_lang = 'id';
  }
  $gplus_options = array(
    'query' => array(
      'url' => $abs_path,
      'hl' => $gplus_lang,
    ),
  );
  $body['google_plus'] = array(
    '#type' => 'link',
    '#title' => '<span class="fa fa-google-plus"></span> Google+',
    '#href' => url('https://plus.google.com/share', $gplus_options),
    '#options' => array(
      'html' => TRUE,
      'attributes' => array(
        'class' => array('btn', 'btn-block', 'btn-lg', 'btn-danger'),
        'target' => '_blank',
      ),
    ),
  );

  $page['page_bottom']['share'] = array(
    '#theme' => 'bootstrap_modal',
    '#size' => 'sm',
    '#heading' => t('Share'),
    '#body' => $body,
    '#attributes' => array(
      'id' => 'share',
    ),
  );
}

/**
 * Implements hook_form_alter().
 */
function elstrap_form_alter(&$form, &$form_state, $form_id) {
  $form['#attributes']['role'] = 'form';
}

/**
 * Implements hook_form_FORM_ID_alter() for search_form().
 */
function elstrap_form_search_form_alter(&$form, &$form_state) {
  $form['basic']['#attributes']['class'] = array('input-group');

  $form['basic']['keys']['#theme_wrappers'] = array();

  $form['basic']['submit']['#attributes']['class'] = array();
  $form['basic']['submit']['#label'] = '<span class="fa fa-search"></span>';
  $form['basic']['submit']['#prefix'] = '<span class="input-group-btn">';
  $form['basic']['submit']['#suffix'] = '</span>';
}

/**
 * Implements hook_form_FORM_ID_alter() for pagespeed_insight_analyze().
 */
function elstrap_form_pagespeed_insight_analyze_form_alter(&$form, &$form_state, $form_id) {
  $form['url']['#field_prefix'] = '<div class="input-group"><span class="input-group-addon fa fa-globe"></span>';
  $form['url']['#field_suffix'] = '</div>';

  $form['actions']['submit']['#label'] = '<span class="fa fa-tachometer"></span> ' . $form['actions']['submit']['#value'];
  $form['actions']['submit']['#attributes']['class'][] = 'btn-primary';
  $form['actions']['submit']['#attributes']['class'][] = 'btn-lg';
  $form['actions']['submit']['#attributes']['class'][] = 'btn-block';
  $form['actions']['submit']['#prefix'] = '<div class="form-group">';
  $form['actions']['submit']['#suffix'] = '</div>';

  $form['#attached']['js'][drupal_get_path('theme', 'elstrap') . '/js/elstrap.pagespeed-insight.js'] = array(
    'type' => 'file',
    'scope' => 'footer',
    'group' => JS_THEME,
  );
}
