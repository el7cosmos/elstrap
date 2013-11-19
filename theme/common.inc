<?php
/**
 * @file
 * common.inc
 *
 * Contains common functionality for the entire base theme.
 */

function elstrap_state_variable($key) {
  $states = array('primary', 'success', 'info', 'warning', 'danger');
  return $states[$key % 5];
}

function elstrap_node_type_icon($type) {
  $icon = array(
    'article' => 'pencil',
    'infographics' => 'picture-o',
  );

  return $icon[$type];
}
