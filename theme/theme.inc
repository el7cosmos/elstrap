<?php

/**
 * @file
 * theme.inc
 */

/**
 * Overrides theme_button().
 */
function elstrap_button($variables) {
  $element = $variables['element'];
  $label = isset($element['#label']) ? $element['#label'] : $element['#value'];
  element_set_attributes($element, array('id', 'name', 'value', 'type'));

  // If a button type class isn't present then add in default.
  $button_classes = array(
    'btn-default',
    'btn-primary',
    'btn-success',
    'btn-info',
    'btn-warning',
    'btn-danger',
    'btn-link',
  );
  $class_intersection = array_intersect($button_classes, $element['#attributes']['class']);
  if (empty($class_intersection)) {
    $element['#attributes']['class'][] = 'btn-default';
  }

  // Add in the button type class.
  $element['#attributes']['class'][] = 'form-' . $element['#button_type'];

  // This line break adds inherent margin between multiple buttons.
  return '<button' . drupal_attributes($element['#attributes']) . '>' . $label . "</button>\n";
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
    if ($link['attributes']['lang'] == $variables['language']) {
      $class[] = 'disabled';
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
    $variables['links']['node-readmore']['title'] .= '&nbsp;<i class="fa fa-arrow-circle-right"></i>';
  }
  if (isset($variables['links']['disqus_comments_num'])) {
    $variables['links']['disqus_comments_num']['title'] .= '&nbsp;<i class="fa fa-comments-o"></i>';
    $variables['links']['disqus_comments_num']['html'] = TRUE;
  }

  foreach ($variables['links'] as $key => $link) {
    if (isset($link['href'])) {
      $links[] = l($link['title'], $link['href'], $link);
    }
  }
  $output = implode(' &middot ', $links);

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
    case 'contact':
      $element['#title'] = '<i class="fa fa-envelope"></i> ' . t($element['#title']) . '</span>';
      break;
  }

  switch ($element['#original_link']['link_title']) {
    case 'Article':
      $element['#title'] = '<i class="fa fa-pencil"></i> ' . t('Article') . '</span> <span class="caret"></span>';
      break;
    case 'Infographics':
      $element['#title'] = '<i class="fa fa-picture-o"></i> ' . t($element['#title']) . '</span>';
      break;
    case 'Internet':
      $element['#title'] = '<i class="fa fa-globe"></i> ' . t($element['#title']);
      break;
    case 'Programming':
      $element['#title'] = '<i class="fa fa-code"></i> ' . t($element['#title']);
      break;
    case 'Technology':
      $element['#title'] = '<i class="fa fa-flash"></i> ' . t($element['#title']);
      break;
  }

  $element['#localized_options']['html'] = TRUE;
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
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
