<?php

/**
 * @file
 *   Administrative pages for the Help Inject module.
 */

/**
 * Configuration options for excluding forms and pathes.
 */
function helpinject_settings($form, &$form_state) {
  $form = array();

  $form['helpinject_excluded_forms'] = array(
    '#type' => 'textarea',
    '#title' => t('Forms that should be excluded from the Help Inject module.'),
    '#default_value' => variable_get('helpinject_excluded_forms', "helpinject_settings\r\nmenu_overview_form"),
    '#description' => t("One form id per line. Help Inject icons won't show up on these forms."),
  );
  $form['helpinject_excluded_paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Paths that should be excluded from the Help Inject module.'),
    '#default_value' => variable_get('helpinject_excluded_paths', "admin/structure/helpinject\r\nadmin/settings/helpinject"),
    '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are blog for the blog page and blog/* for every personal blog. <front> is the front page."),
  );
  return system_settings_form($form);
}
