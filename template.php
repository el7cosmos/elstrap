<?php

/**
 * @file
 * template.php
 *
 * This file should only contain light helper functions and stubs pointing to
 * other files containing more complex functions.
 *
 * The stubs should point to files within the `includes` folder named after
 * the function itself minus the theme prefix. If the stub contains a group
 * of functions, then please organize them so they are related in some way
 * and name the file appropriately to at least hint at what it contains.
 *
 * All [pre]process functions, theme function and template implementations
 * reside in the 'theme' folder. This is a highly automated and complex system
 * designed to only load the necessary files when a given theme hook is invoked.
 * @see _bootstrap_theme()
 * @see includes/registry.inc
 */

/**
 * Include common functions used through out theme.
 */
bootstrap_include('elstrap', 'theme/common.inc');

/**
 * Declare various hook_*_alter() hooks.
 *
 * hook_*_alter() implementations must live (via include) inside this file so
 * they are properly detected when drupal_alter() is invoked.
 */
bootstrap_include('elstrap', 'theme/alter.inc');

bootstrap_include('elstrap', 'theme/preprocess.inc');
bootstrap_include('elstrap', 'theme/process.inc');
bootstrap_include('elstrap', 'theme/theme.inc');
