<?php

/**
 * @file
 * Administrative interface for specifying the attribute dependencies.
 *
 * These functions supply the administrative interface for specifying the
 * attribute dependencies using AJAX.  Based on code from the Examples module.
 */

/**
 * Specify the attribute dependencies.
 */
function uc_dropdown_attributes($form, &$form_state, $product) {
  $nid = $product->nid;
  $attributes = uc_product_get_attributes($nid);

  $parent = array();
  $values = array();
  $required = array();
  if (isset($form_state['values'])) {
    foreach ($form_state['values']['attributes'] as $key => $attribute) {
      $parent[$key] = $attribute['parent'];
      $values[$key] = $attribute['values'];
      $required[$key] = $attribute['required'];
    }
  }
  else {
    $query = 'SELECT aid, parent_aid, parent_values, required
      FROM {uc_dropdown_attributes} WHERE nid=:nid';
    $result = db_query($query, array(':nid' => $product->nid));
    foreach ($result as $item) {
      $parent[$item->aid] = $item->parent_aid;
      $values[$item->aid] = unserialize($item->parent_values);
      $required[$item->aid] = $item->required;
    }
  }

  $options_first = drupal_map_assoc(array(t('String'), t('Woodwind'), t('Brass'), t('Percussion')));

  $form['#tree'] = TRUE;
  $form['intro'] =array(
    '#markup' => '<p>' . t('Since drop down attributes may not appear, they cannot be always required.  The required checkbox applies only when the dropdown attribute appears.  Any dropdown attribute is also checked under the attributes table to make sure it is not required there as this would cause validation errors.') . '</p>',
  );
  $form['prefix'] = array(
    '#markup' => '<table><tr><th>' . t('Attribute') . '</th><th>' .
                 t('Depends On') . '</th><th>' . t('With Values') .
                 '</th><th>' . t('Required') . '</th></tr>',
  );

  foreach ($attributes as $attribute) {
    $form['attributes'][$attribute->aid]['attribute'] = array(
      '#markup' => '<tr><td>' . $attribute->name . '</td>',
    );

    $options = array();
    $options[0] = 'None';
    foreach ($attributes as $option) {
      if ($option->aid!=$attribute->aid) {
        $options[$option->aid] = $option->name;
      }
    }
    $selected = array_key_exists($attribute->aid, $parent) ?
                $parent[$attribute->aid] : 0;
    $form['attributes'][$attribute->aid]['parent'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => $selected,
      '#ajax' => array(
        'callback' => 'uc_dropdown_attributes_dependent_callback',
        'wrapper' => 'dropdown-' . $attribute->aid . '-replace',
      ),
      '#prefix' => '<td>',
      '#suffix' => '</td><td>',
    );
  
    $options = array();
    if ($selected==0) {
      $type = 'select';
    }
    else {
      $parent_attributes = uc_attribute_load($selected);
      if (count($parent_attributes->options)==0) {
        $type = 'textfield';
      }
      else {
        $type= 'select';
        foreach ($parent_attributes->options as $oid => $option)
          $options[$oid] = $option->name;
      }
    }
    if ($type=='select') {
      $form['attributes'][$attribute->aid]['values'] = array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#prefix' => '<div id="dropdown-' . $attribute->aid . '-replace">',
        '#suffix' => '</div>',
        '#options' => $options,
      );
      if (array_key_exists($attribute->aid, $values)) {
        $form['attributes'][$attribute->aid]['values']['#default_value'] =
          $values[$attribute->aid];
      }
    }
    else {
      $form['attributes'][$attribute->aid]['values'] = array(
        '#type' => 'textfield',
        '#prefix' => '<div id="dropdown-' . $attribute->aid . '-replace">',
        '#suffix' => '</div>',
      );
    }

    $form['attributes'][$attribute->aid]['required'] = array(
      '#type' => 'checkbox',
      '#prefix' => '<td>',
      '#returned_value' => 1,
      '#default_value' => array_key_exists($attribute->aid, $required) ?
        $required[$attribute->aid] : 0,
      '#suffix' => '</td></tr>',
    );
  }
  
  $form['suffix'] = array(
    '#markup' => '</table>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('OK'),
  );

  return $form;
}

function uc_dropdown_attributes_dependent_callback($form, $form_state) {
  $wrapper = explode('-',
    $form_state['triggering_element']['#ajax']['wrapper']);
  $attribute = $wrapper[1];
  return $form['attributes'][$attribute]['values'];
}

function uc_dropdown_attributes_options($key = '') {
  $options = array(
    t('String') => drupal_map_assoc(array(t('Violin'), t('Viola'), t('Cello'), t('Double Bass'))),
    t('Woodwind') => drupal_map_assoc(array(t('Flute'), t('Clarinet'), t('Oboe'), t('Bassoon'))),
    t('Brass') => drupal_map_assoc(array(t('Trumpet'), t('Trombone'), t('French Horn'), t('Euphonium'))),
    t('Percussion') => drupal_map_assoc(array(t('Bass Drum'), t('Timpani'), t('Snare Drum'), t('Tambourine'))),
  );
  if (isset($options[$key])) {
    return $options[$key];
  }
  else {
    return array();
  }
}

/**
 * Write form values out to the database table.
 */
function uc_dropdown_attributes_submit($form, &$form_state) {
  if ($form_state['clicked_button']['#id'] == 'edit-submit') {
    $form_state['rebuild'] = FALSE;
    $nid = $form_state['build_info']['args'][0]->nid;
    foreach ($form_state['values']['attributes'] as $aid => $value) {
      if (!isset($records[$aid])) {
        $records[$aid] = new stdClass();
      }
      foreach ($value as $field => $field_value) {
        switch ($field) {
          case 'parent':
            $records[$aid]->parent_aid = $field_value;
            break;

          case 'values':
            $records[$aid]->parent_values = serialize($field_value);
            break;

          case 'required':
            $records[$aid]->required = $field_value;
            break;
        }
      }
    }
    $table = 'uc_dropdown_attributes';
    $result = db_delete('uc_dropdown_attributes')
              ->condition('nid', $nid)
              ->execute();
    drupal_set_message(t('Processing node ' . $nid));
    foreach ($records as $record_key => $record_value) {
      $attribute = uc_attribute_load($record_key);
      if ($record_value->parent_aid != 0) {
        $record_value->nid = $nid;
        $record_value->aid = $record_key;
        $record_value->html = '';
        $values = unserialize($record_value->parent_values);
        $result = drupal_write_record($table, $record_value);
        drupal_set_message(t('Saved ' .  $attribute->name));
        // Need to check to make sure attribute is not required all the time
        $sql = 'SELECT nid, aid, required FROM {uc_product_attributes}
          WHERE nid=:nid && aid=:aid';
        $result = db_query($sql, array(':nid' => $nid, ':aid' => $record_key));
        foreach($result as $item) {
          if ($item->required == 1) {
            $table = 'uc_product_attributes';
            $record = new stdClass();
            $record->nid = $item->nid;
            $record->aid = $item->aid;
            $record->required = 0;
            $record->html = '';
            $primary_keys = array('nid', 'aid');
            drupal_write_record($table, $record, $primary_keys);
          }
        }
      }
    }
  }

  // edit-next or anything else will cause rebuild.
  $form_state['rebuild'] = TRUE;
}

