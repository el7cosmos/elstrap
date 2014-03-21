<?php

/**
 * @file
 * theme.inc
 */

/**
 * Overrides theme_button().
 */
function elstrap_button($variables) {
  $label = isset($variables['element']['#label']) ? $variables['element']['#label'] : $variables['element']['#value'];

  // This line break adds inherent margin between multiple buttons.
  return '<button' . drupal_attributes($variables['element']['#attributes']) . '>' . $label . "</button>\n";
}

/**
 * Overrides theme_status_messages().
 */
function elstrap_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
    'info' => t('Informative message'),
  );

  // Map Drupal message types to their corresponding Bootstrap classes.
  // @see http://twitter.github.com/bootstrap/components.html#alerts
  $status_class = array(
    'status' => 'success',
    'error' => 'danger',
    'warning' => 'warning',
    // Not supported, but in theory a module could send any type of message.
    // @see drupal_set_message()
    // @see theme_status_messages()
    'info' => 'info',
  );

  foreach (drupal_get_messages($display) as $type => $messages) {
    $class = (isset($status_class[$type])) ? ' alert-' . $status_class[$type] : '';
    $output .= "<div class=\"alert alert-block$class messages $type\">\n";

    if (!empty($status_heading[$type])) {
      $output .= '<h4 class="element-invisible">' . $status_heading[$type] . "</h4>\n";
    }

    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }

    $output .= "</div>\n";
  }
  return $output;
}


/**
 * Overrides theme_links__locale_menu().
 */
function elstrap_links__locale_menu($variables) {
  $links = $variables['links'];
  $attributes = $variables['attributes'];

  $output = '';

  $output .= '<ul' . drupal_attributes($attributes) . '>';

  $num_links = count($links);
  $i = 1;

  foreach ($links as $key => $link) {
    $class = array($key);

    // Add first, last and active classes to the list of links to help out themers.
    if ($i == 1) {
      $class[] = 'first';
    }
    if ($i == $num_links) {
      $class[] = 'last';
    }
    if ($link['attributes']['lang'] == $variables['language'] || !isset($link['href'])) {
      $class[] = 'disabled';
      $link['href'] = '#';
      $link['external'] = TRUE;
    }
    $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';

    $output .= l($link['title'], $link['href'], $link);

    $i++;
    $output .= "</li>\n";
  }

  $output .= '</ul>';

  return $output;
}

/**
 * Overrides theme_links__node().
 */
function elstrap_links__node(&$variables) {
  $attributes = $variables['attributes'];
  $links = array();

  if (isset($variables['links']['node-readmore'])) {
    $variables['links']['node-readmore']['title'] .= '&nbsp;<span class="fa fa-arrow-circle-right"></span>';
  }
  if (isset($variables['links']['disqus_comments_num'])) {
    $variables['links']['disqus_comments_num']['title'] .= '&nbsp;<span class="fa fa-comments-o"></span>';
    $variables['links']['disqus_comments_num']['html'] = TRUE;
  }

  foreach ($variables['links'] as $key => $link) {
    if (isset($link['href'])) {
      $links[] = l($link['title'], $link['href'], $link);
    }
  }
  $output = implode(' &middot; ', $links);

  return $output;
}

/**
 * Overrides theme_menu_link().
 */
function elstrap_menu_link(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#below']) {
    // Prevent dropdown functions from being added to management menu so it
    // does not affect the navbar module.
    if (($element['#original_link']['menu_name'] == 'management') && (module_exists('navbar'))) {
      $sub_menu = drupal_render($element['#below']);
    }
    else {
      // Add our own wrapper.
      unset($element['#below']['#theme_wrappers']);
      // $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
      $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';

      // Check if this element is nested within another.
      if ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] > 1)) {
        // Generate as dropdown submenu.
        // $element['#attributes']['class'][] = 'dropdown-submenu';
      }
      else {
        // Generate as standard dropdown.
        $element['#attributes']['class'][] = 'dropdown';
        $element['#localized_options']['html'] = TRUE;
        $element['#title'] .= ' <span class="caret"></span>';
      }

      // Set dropdown trigger element to # to prevent inadvertant page loading
      // when a submenu link is clicked.
      $element['#localized_options']['attributes']['data-target'] = '#';
    }
  }
  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Overrides theme_menu_link__main_menu().
 */
function elstrap_menu_link__main_menu(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#below'] && $element['#original_link']['depth'] == 1) {
    // Prevent dropdown functions from being added to management menu so it
    // does not affect the navbar module.
    if (($element['#original_link']['menu_name'] == 'management') && (module_exists('navbar'))) {
      $sub_menu = drupal_render($element['#below']);
    }
    else {
      // Add our own wrapper.
      unset($element['#below']['#theme_wrappers']);
      $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
      $element['#attributes']['class'][] = 'dropdown';
      $element['#title'] .= ' <span class="caret"></span>';
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
      $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';
      $element['#localized_options']['html'] = TRUE;


      // Set dropdown trigger element to # to prevent inadvertant page loading
      // when a submenu link is clicked.
      $element['#localized_options']['attributes']['data-target'] = '#';
    }
  }
  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }

  switch ($element['#href']) {
    case 'pagespeed-insight':
      $element['#title'] = '<span class="fa fa-tachometer"></span> ' . t($element['#title']);
      break;
    case 'contact':
      $element['#title'] = '<span class="fa fa-envelope"></span> ' . t($element['#title']);
      break;
  }

  switch ($element['#original_link']['link_title']) {
    case 'Article':
      $element['#title'] = '<span class="fa fa-pencil"></span> ' . t('Article') . ' <span class="caret"></span>';
      break;
    case 'Internet':
      $element['#title'] = '<span class="fa fa-globe"></span> ' . t($element['#title']);
      break;
    case 'Programming':
      $element['#title'] = '<span class="fa fa-code"></span> ' . t($element['#title']);
      break;
    case 'Technology':
      $element['#title'] = '<span class="fa fa-rocket"></span> ' . t($element['#title']);
      break;
    case 'Infographics':
      $element['#title'] = '<span class="fa fa-bar-chart-o"></span> ' . t($element['#title']);
      break;
    case 'Journal':
      $element['#title'] = '<span class="fa fa-road"></span> ' . t($element['#title']);
      break;
  }

  $element['#localized_options']['html'] = TRUE;
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Overrides theme_menu_tree().
 */
function elstrap_menu_tree(&$variables) {
  return '<ul class="nav">' . $variables['tree'] . '</ul>';
}

/**
 * eL Strap theme wrapper function for the primary menu links.
 */
function elstrap_menu_tree__primary(&$variables) {
  return '<ul class="nav navbar-nav">' . $variables['tree'] . '</ul>';
}

/**
 * el Strap theme wrapper function for the secondary menu links.
 */
function elstrap_menu_tree__secondary(&$variables) {
  return '<ul class="nav navbar-nav">' . $variables['tree'] . '</ul>';
}

/**
 * Overrides theme_image_style().
 */
function elstrap_image_style($variables) {
  // Determine the dimensions of the styled image.
  $dimensions = array(
    'width' => $variables['width'],
    'height' => $variables['height'],
  );

  image_style_transform_dimensions($variables['style_name'], $dimensions);

  $variables['width'] = $dimensions['width'];
  $variables['height'] = $dimensions['height'];

  // Determine the URL for the styled image.
  $path = image_style_url($variables['style_name'], $variables['path']);
  $parsed_url = drupal_parse_url($path);
  $variables['path'] = $parsed_url['path'];
  return theme('image', $variables);
}

/**
 * Overrides theme_pagespeed_insight_score().
 */
function elstrap_pagespeed_insight_score($variables) {
  $score = $variables['score'];

  if ($score >= 50 && $score < 85) {
    $state = 'warning';
  }
  elseif ($score < 50) {
    $state = 'danger';
  }
  else {
    $state = 'success';
  }

  return '<p id="score" class="lead text-center text-' . $state . '"><span class="fa-5x"><span class="fa fa-tachometer"></span> ' . $score . '/100</span></p>';
}

/**
 * Overrides theme_pagespeed_insight_header().
 */
function elstrap_pagespeed_insight_header($variables) {
  $header = $variables['header'];

  if (isset($header['args'])) {
    $options = array(
      'html' => TRUE,
      'attributes' => array(
        'target' => '_blank',
      ),
    );
    $search = array();
    $replace = array();

    foreach ($header['args'] as $key => $arg) {
      if ($arg['type'] == 'HYPERLINK') {
        $header['format'] .= ' <span class="small">(' . l($arg['value'] . ' <span class="fa fa-external-link"></span>', $arg['value'], $options) . ')</span>';
      }
      else {
        $search[] = "\$" . ($key + 1);
        $replace[] = '<span class="badge">' .$arg['value'] . '</span>';
      }
    }
    if (!empty($search)) {
      return str_replace($search, $replace, $header['format']);
    }
  }

  return $header['format'];
}

/**
 * Overrides theme_pagespeed_insight_result().
 */
function elstrap_pagespeed_insight_result($variables) {
  $result = $variables['result'];

  if (isset($result['args'])) {
    $options = array(
      'html' => TRUE,
      'attributes' => array(
        'target' => '_blank',
      ),
    );
    $search = array();
    $replace = array();

    foreach ($result['args'] as $key => $arg) {
      $search[] = "\$" . ($key + 1);
      if ($arg['type'] == 'URL') {
        $replace[] = l(_filter_url_trim($arg['value'], 77) . ' <span class="fa fa-external-link"></span>', $arg['value'], $options);
      }
      else {
        $replace[] = '<span class="badge">' .$arg['value'] . '</span>';
      }
    }
    if (!empty($search)) {
      return str_replace($search, $replace, $result['format']);
    }
  }

  return $result['format'];
}
