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
  foreach ($javascript as $data => $js) {
    if ($js['group'] != JS_LIBRARY && $js['scope'] == 'header') {
      $javascript[$data]['scope'] = 'footer';
    }
  }
}

/**
 * Implements hook_page_alter().
 */
function elstrap_page_alter(&$page) {
  global $language;
  $path = drupal_is_front_page() ? '<front>' : current_path();
  $title = drupal_get_title();

  $body['fb_like'] = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array('fb-like'),
      'data-href' => url($path, array('absolute' => TRUE)),
      'data-layout' => 'box_count',
    ),
    '#value' => '',
  );
  $body['fb_share'] = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array('fb-share-button'),
      'data-href' => url($path, array('absolute' => TRUE)),
      'data-layout' => 'box_count',
    ),
    '#value' => '',
  );
  $body['tweet_button'] = array(
    '#type' => 'link',
    '#title' => 'Tweet',
    '#href' => 'https://twitter.com/share',
    '#options' => array(
      'attributes' => array(
        'class' => array('twitter-share-button'),
        'data-url' => url($path, array('absolute' => TRUE)),
        'data-via' => variable_get('twitter_username'),
        'data-count' => 'vertical',
        'data-lang' => $language->language,
      ),
    ),
    '#attached' => array(
      'js' => array(
        path_to_theme() . '/js/elstrap.twitter.js' => array(
          'type' => 'file',
          'scope' => 'footer',
          'group' => JS_THEME,
        ),
      ),
    ),
  );
  if (!empty($title)) {
    $body['tweet_button']['#options']['attributes']['data-text'] = drupal_get_title();
  }

  if ($language->language == 'en') {
    $gplus_lang = 'en_US';
  }
  else {
    $gplus_lang = 'id';
  }

  $body['google_plus'] = array(
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => array(
      'class' => array('g-plusone'),
      'data-size' => 'tall',
      'data-href' => url($path, array('absolute' => TRUE)),
    ),
    '#value' => '',
    '#attached' => array(
      'js' => array(
        array(
          'data' => array(
            'elstrapGooglePlus' => array(
              'lang' => $gplus_lang,
              'publisherId' => variable_get('google_plus_publisher_id'),
            ),
          ),
          'type' => 'setting',
        ),
        path_to_theme() . '/js/elstrap.gplus.js' => array(
          'type' => 'file',
          'scope' => 'footer',
          'group' => JS_THEME,
        ),
      ),
    ),
  );
  $page['page_bottom']['share'] = array(
    '#theme' => 'bootstrap_modal',
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

