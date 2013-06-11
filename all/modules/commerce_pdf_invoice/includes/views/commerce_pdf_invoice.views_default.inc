<?php

/**
 * Views for the default product UI.
 */

/**
 * Implements hook_views_default_views().
 */
function commerce_pdf_invoice_views_default_views() {
  $views = array();
  $view = new view;
  $view->name = 'commerce_pdf_invoice';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_order';
  $view->human_name = 'Commerce Invoice';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Commerce Invoice';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Order: Referenced customer profile */
  $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['id'] = 'commerce_customer_billing_profile_id';
  $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['table'] = 'field_data_commerce_customer_billing';
  $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['field'] = 'commerce_customer_billing_profile_id';
  $handler->display->display_options['relationships']['commerce_customer_billing_profile_id']['required'] = 1;
  /* Field: Commerce Order: Order ID */
  $handler->display->display_options['fields']['order_id']['id'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_id']['field'] = 'order_id';
  $handler->display->display_options['fields']['order_id']['label'] = '';
  $handler->display->display_options['fields']['order_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['order_id']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['external'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['order_id']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['order_id']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['order_id']['alter']['html'] = 0;
  $handler->display->display_options['fields']['order_id']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['order_id']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['order_id']['hide_empty'] = 0;
  $handler->display->display_options['fields']['order_id']['empty_zero'] = 0;
  /* Field: Customer profile: Address */
  $handler->display->display_options['fields']['commerce_customer_address']['id'] = 'commerce_customer_address';
  $handler->display->display_options['fields']['commerce_customer_address']['table'] = 'field_data_commerce_customer_address';
  $handler->display->display_options['fields']['commerce_customer_address']['field'] = 'commerce_customer_address';
  $handler->display->display_options['fields']['commerce_customer_address']['relationship'] = 'commerce_customer_billing_profile_id';
  $handler->display->display_options['fields']['commerce_customer_address']['label'] = '';
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_customer_address']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_customer_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['commerce_customer_address']['type'] = 'addressfield_invoice';
  $handler->display->display_options['fields']['commerce_customer_address']['field_api_classes'] = 0;
  /* Field: Commerce Order: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Order Date';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  /* Field: Commerce Order: Order number */
  $handler->display->display_options['fields']['order_number']['id'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['table'] = 'commerce_order';
  $handler->display->display_options['fields']['order_number']['field'] = 'order_number';
  $handler->display->display_options['fields']['order_number']['label'] = 'Order Number';
  $handler->display->display_options['fields']['order_number']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['external'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['order_number']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['order_number']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['order_number']['alter']['html'] = 0;
  $handler->display->display_options['fields']['order_number']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['order_number']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['order_number']['hide_empty'] = 0;
  $handler->display->display_options['fields']['order_number']['empty_zero'] = 0;
  /* Field: Document Title */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Document Title';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Invoice';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
  /* Field: View: Include View */
  $handler->display->display_options['fields']['include']['id'] = 'include';
  $handler->display->display_options['fields']['include']['table'] = 'view';
  $handler->display->display_options['fields']['include']['field'] = 'include';
  $handler->display->display_options['fields']['include']['label'] = '';
  $handler->display->display_options['fields']['include']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['include']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['include']['hide_empty'] = 0;
  $handler->display->display_options['fields']['include']['empty_zero'] = 0;
  $handler->display->display_options['fields']['include']['view'] = 'commerce_pdf_invoice_line_items';
  $handler->display->display_options['fields']['include']['number_of_args'] = '1';
  $handler->display->display_options['fields']['include']['args'] = array(
    0 => '[order_id]',
  );
  /* Field: Order: Order total */
  $handler->display->display_options['fields']['commerce_order_total']['id'] = 'commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['table'] = 'field_data_commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['field'] = 'commerce_order_total';
  $handler->display->display_options['fields']['commerce_order_total']['label'] = '';
  $handler->display->display_options['fields']['commerce_order_total']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_order_total']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_order_total']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_order_total']['type'] = 'commerce_price_formatted_components';
  $handler->display->display_options['fields']['commerce_order_total']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['commerce_order_total']['field_api_classes'] = 0;
  /* Contextual filter: Commerce Order: Order ID */
  $handler->display->display_options['arguments']['order_id']['id'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['table'] = 'commerce_order';
  $handler->display->display_options['arguments']['order_id']['field'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['order_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['order_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['order_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['order_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['order_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['order_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['order_id']['not'] = 0;

  /* Display: PDF Page */
  $handler = $view->new_display('pdf', 'PDF Page', 'pdf_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'pdf_unformatted';
  $handler->display->display_options['row_plugin'] = 'pdf_fields';
  $handler->display->display_options['row_options']['formats'] = array(
    'commerce_customer_address' => array(
      'position' => array(
        'object' => 'page',
        'corner' => 'top_left',
        'x' => '85',
        'y' => '40',
        'width' => '',
        'height' => '',
      ),
      'text' => array(
        'font_size' => '',
        'font_family' => 'default',
        'font_style' => NULL,
        'align' => NULL,
        'color' => '',
      ),
      'render' => array(
        'is_html' => 1,
        'eval_before' => '',
        'eval_after' => '',
      ),
    ),
    'created' => array(
      'position' => array(
        'object' => 'page',
        'corner' => 'top_left',
        'x' => '',
        'y' => '80',
        'width' => '',
        'height' => '',
      ),
      'text' => array(
        'font_size' => '',
        'font_family' => 'default',
        'font_style' => NULL,
        'align' => NULL,
        'color' => '',
      ),
      'render' => array(
        'is_html' => 1,
        'eval_before' => '',
        'eval_after' => '',
      ),
    ),
    'order_number' => array(
      'position' => array(
        'object' => 'field_created',
        'corner' => 'bottom_left',
        'x' => '',
        'y' => '',
        'width' => '',
        'height' => '',
      ),
      'text' => array(
        'font_size' => '',
        'font_family' => 'default',
        'font_style' => NULL,
        'align' => NULL,
        'color' => '',
      ),
      'render' => array(
        'is_html' => 1,
        'eval_before' => '',
        'eval_after' => '',
      ),
    ),
    'nothing' => array(
      'position' => array(
        'object' => 'field_order_number',
        'corner' => 'bottom_left',
        'x' => '',
        'y' => '5',
        'width' => '',
        'height' => '',
      ),
      'text' => array(
        'font_size' => '18',
        'font_family' => 'default',
        'font_style' => array(
    'b' => 'b',
    'i' => 0,
    'u' => 0,
    'd' => 0,
    'o' => 0,
        ),
        'align' => NULL,
        'color' => '',
      ),
      'render' => array(
        'is_html' => 1,
        'eval_before' => '',
        'eval_after' => '',
      ),
    ),
    'include' => array(
      'position' => array(
        'object' => 'field_nothing',
        'corner' => 'bottom_left',
        'x' => '',
        'y' => '3',
        'width' => '',
        'height' => '',
      ),
      'text' => array(
        'font_size' => '',
        'font_family' => 'default',
        'font_style' => NULL,
        'align' => NULL,
        'color' => '',
      ),
      'render' => array(
        'is_html' => 1,
        'eval_before' => '',
        'eval_after' => '',
      ),
    ),
    'commerce_order_total' => array(
      'position' => array(
        'object' => 'field_include',
        'corner' => 'bottom_left',
        'x' => '70',
        'y' => '',
        'width' => '',
        'height' => '',
      ),
      'text' => array(
        'font_size' => '',
        'font_family' => 'default',
        'font_style' => NULL,
        'align' => 'R',
        'color' => '',
      ),
      'render' => array(
        'is_html' => 1,
        'eval_before' => '',
        'eval_after' => '',
      ),
    ),
  );
  $handler->display->display_options['row_options']['leading_template'] = '0';
  $handler->display->display_options['row_options']['template'] = '0';
  $handler->display->display_options['row_options']['succeed_template'] = '0';
  $handler->display->display_options['path'] = 'commerce/invoice/%';
  $handler->display->display_options['leading_template'] = '0';
  $handler->display->display_options['template'] = 'Vorlage_9';
  $handler->display->display_options['succeed_template'] = '0';
  $handler->display->display_options['default_font_style'] = array(
    'b' => 0,
    'i' => 0,
    'u' => 0,
    'd' => 0,
    'o' => 0,
  );
  $handler->display->display_options['default_font_size'] = '10';
  $translatables['commerce_invoice'] = array(
    t('Master'),
    t('Commerce Invoice'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Customer profile'),
    t('Order Date'),
    t('Order Number'),
    t('Invoice'),
    t('All'),
    t('PDF Page'),
  );

  $views[$view->name] = $view;



  $view = new view;
  $view->name = 'commerce_pdf_invoice_line_items';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'commerce_line_item';
  $view->human_name = 'Commerce Pdf Invoice Line Items';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Order */
  $handler->display->display_options['relationships']['order_id']['id'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['relationships']['order_id']['field'] = 'order_id';
  $handler->display->display_options['relationships']['order_id']['ui_name'] = 'Order';
  $handler->display->display_options['relationships']['order_id']['required'] = 1;
  /* Field: Commerce Line Item: Label */
  $handler->display->display_options['fields']['line_item_label']['id'] = 'line_item_label';
  $handler->display->display_options['fields']['line_item_label']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['line_item_label']['field'] = 'line_item_label';
  $handler->display->display_options['fields']['line_item_label']['label'] = 'SKU';
  $handler->display->display_options['fields']['line_item_label']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['external'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['line_item_label']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['line_item_label']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['line_item_label']['alter']['html'] = 0;
  $handler->display->display_options['fields']['line_item_label']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['line_item_label']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['line_item_label']['hide_empty'] = 0;
  $handler->display->display_options['fields']['line_item_label']['empty_zero'] = 0;
  /* Field: Commerce Line Item: Title */
  $handler->display->display_options['fields']['line_item_title']['id'] = 'line_item_title';
  $handler->display->display_options['fields']['line_item_title']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['line_item_title']['field'] = 'line_item_title';
  $handler->display->display_options['fields']['line_item_title']['label'] = 'Name';
  $handler->display->display_options['fields']['line_item_title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['line_item_title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['line_item_title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['line_item_title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['line_item_title']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['line_item_title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['line_item_title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['line_item_title']['empty_zero'] = 0;
  /* Field: Commerce Line Item: Quantity */
  $handler->display->display_options['fields']['quantity']['id'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['table'] = 'commerce_line_item';
  $handler->display->display_options['fields']['quantity']['field'] = 'quantity';
  $handler->display->display_options['fields']['quantity']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['external'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['quantity']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['quantity']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['quantity']['alter']['html'] = 0;
  $handler->display->display_options['fields']['quantity']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['quantity']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['quantity']['hide_empty'] = 0;
  $handler->display->display_options['fields']['quantity']['empty_zero'] = 0;
  $handler->display->display_options['fields']['quantity']['set_precision'] = 1;
  $handler->display->display_options['fields']['quantity']['precision'] = '2';
  $handler->display->display_options['fields']['quantity']['format_plural'] = 0;
  /* Field: Line item: Unit price */
  $handler->display->display_options['fields']['commerce_unit_price']['id'] = 'commerce_unit_price';
  $handler->display->display_options['fields']['commerce_unit_price']['table'] = 'field_data_commerce_unit_price';
  $handler->display->display_options['fields']['commerce_unit_price']['field'] = 'commerce_unit_price';
  $handler->display->display_options['fields']['commerce_unit_price']['label'] = 'Unit Price';
  $handler->display->display_options['fields']['commerce_unit_price']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_unit_price']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_unit_price']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_unit_price']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_unit_price']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_unit_price']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_unit_price']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_unit_price']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_unit_price']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_unit_price']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_unit_price']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_unit_price']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['commerce_unit_price']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_unit_price']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_unit_price']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_unit_price']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_unit_price']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['commerce_unit_price']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['commerce_unit_price']['field_api_classes'] = 0;
  /* Field: Line item: Total */
  $handler->display->display_options['fields']['commerce_total']['id'] = 'commerce_total';
  $handler->display->display_options['fields']['commerce_total']['table'] = 'field_data_commerce_total';
  $handler->display->display_options['fields']['commerce_total']['field'] = 'commerce_total';
  $handler->display->display_options['fields']['commerce_total']['label'] = 'Unit Price';
  $handler->display->display_options['fields']['commerce_total']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['external'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['commerce_total']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['commerce_total']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['commerce_total']['alter']['html'] = 0;
  $handler->display->display_options['fields']['commerce_total']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['commerce_total']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['commerce_total']['hide_empty'] = 0;
  $handler->display->display_options['fields']['commerce_total']['empty_zero'] = 0;
  $handler->display->display_options['fields']['commerce_total']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['commerce_total']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['commerce_total']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['commerce_total']['field_api_classes'] = 0;
  /* Contextual filter: Commerce Line Item: Order ID */
  $handler->display->display_options['arguments']['order_id']['id'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['table'] = 'commerce_line_item';
  $handler->display->display_options['arguments']['order_id']['field'] = 'order_id';
  $handler->display->display_options['arguments']['order_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['order_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['order_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['order_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['order_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['order_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['order_id']['specify_validation'] = 1;
  $handler->display->display_options['arguments']['order_id']['validate']['type'] = 'numeric';
  $handler->display->display_options['arguments']['order_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['order_id']['not'] = 0;

  /* Display: PDF Page */
  $handler = $view->new_display('pdf', 'PDF Page', 'pdf_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'pdf_table';
  $handler->display->display_options['style_options']['info'] = array(
    'line_item_label' => array(
      'header_style' => array(
        'text' => array(
    'font_size' => '',
    'font_family' => 'default',
    'font_style' => array(
      'b' => 'b',
      'i' => 0,
      'u' => 0,
      'd' => 0,
      'o' => 0,
    ),
    'align' => NULL,
    'color' => '',
        ),
        'render' => array(
    'is_html' => 1,
    'eval_before' => '',
    'eval_after' => '',
        ),
      ),
      'body_style' => array(
        'text' => array(
    'font_size' => '',
    'font_family' => 'default',
    'font_style' => array(
      'b' => 0,
      'i' => 0,
      'u' => 0,
      'd' => 0,
      'o' => 0,
    ),
    'align' => NULL,
    'color' => '',
        ),
        'render' => array(
    'is_html' => 1,
    'eval_before' => '',
    'eval_after' => '',
        ),
      ),
      'position' => array(
        'width' => '80',
      ),
    ),
    'line_item_title' => array(
      'header_style' => array(
        'text' => array(
    'font_size' => '',
    'font_family' => 'default',
    'font_style' => array(
      'b' => 'b',
      'i' => 0,
      'u' => 0,
      'd' => 0,
      'o' => 0,
    ),
    'align' => NULL,
    'color' => '',
        ),
        'render' => array(
    'is_html' => 1,
    'eval_before' => '',
    'eval_after' => '',
        ),
      ),
      'body_style' => array(
        'text' => array(
    'font_size' => '',
    'font_family' => 'default',
    'font_style' => array(
      'b' => 0,
      'i' => 0,
      'u' => 0,
      'd' => 0,
      'o' => 0,
    ),
    'align' => NULL,
    'color' => '',
        ),
        'render' => array(
    'is_html' => 1,
    'eval_before' => '',
    'eval_after' => '',
        ),
      ),
      'position' => array(
        'width' => '50',
      ),
    ),
    'quantity' => array(
      'header_style' => array(
        'text' => array(
    'font_size' => '',
    'font_family' => 'default',
    'font_style' => array(
      'b' => 'b',
      'i' => 0,
      'u' => 0,
      'd' => 0,
      'o' => 0,
    ),
    'align' => NULL,
    'color' => '',
        ),
        'render' => array(
    'is_html' => 1,
    'eval_before' => '',
    'eval_after' => '',
        ),
      ),
      'body_style' => array(
        'text' => array(
    'font_size' => '',
    'font_family' => 'default',
    'font_style' => array(
      'b' => 0,
      'i' => 0,
      'u' => 0,
      'd' => 0,
      'o' => 0,
    ),
    'align' => NULL,
    'color' => '',
        ),
        'render' => array(
    'is_html' => 1,
    'eval_before' => '',
    'eval_after' => '',
        ),
      ),
      'position' => array(
        'width' => '20',
      ),
    ),
    'commerce_unit_price' => array(
      'header_style' => array(
        'text' => array(
    'font_size' => '',
    'font_family' => 'default',
    'font_style' => array(
      'b' => 'b',
      'i' => 0,
      'u' => 0,
      'd' => 0,
      'o' => 0,
    ),
    'align' => 'R',
    'color' => '',
        ),
        'render' => array(
    'is_html' => 1,
    'eval_before' => '',
    'eval_after' => '',
        ),
      ),
      'body_style' => array(
        'text' => array(
    'font_size' => '',
    'font_family' => 'default',
    'font_style' => array(
      'b' => 0,
      'i' => 0,
      'u' => 0,
      'd' => 0,
      'o' => 0,
    ),
    'align' => 'R',
    'color' => '',
        ),
        'render' => array(
    'is_html' => 1,
    'eval_before' => '',
    'eval_after' => '',
        ),
      ),
      'position' => array(
        'width' => '30',
      ),
    ),
    'commerce_total' => array(
      'header_style' => array(
        'text' => array(
    'font_size' => '',
    'font_family' => 'default',
    'font_style' => array(
      'b' => 'b',
      'i' => 0,
      'u' => 0,
      'd' => 0,
      'o' => 0,
    ),
    'align' => 'R',
    'color' => '',
        ),
        'render' => array(
    'is_html' => 1,
    'eval_before' => '',
    'eval_after' => '',
        ),
      ),
      'body_style' => array(
        'text' => array(
    'font_size' => '',
    'font_family' => 'default',
    'font_style' => array(
      'b' => 0,
      'i' => 0,
      'u' => 0,
      'd' => 0,
      'o' => 0,
    ),
    'align' => 'R',
    'color' => '',
        ),
        'render' => array(
    'is_html' => 1,
    'eval_before' => '',
    'eval_after' => '',
        ),
      ),
      'position' => array(
        'width' => '30',
      ),
    ),
  );
  $handler->display->display_options['style_options']['position'] = array(
    'x' => '',
    'y' => '',
    'width' => '',
    'row_height' => '',
  );
  $handler->display->display_options['path'] = 'commerce/invoice-lines/%';
  $translatables['commerce_pdf_invoice_line_items'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Order'),
    t('SKU'),
    t('Name'),
    t('Quantity'),
    t('.'),
    t(','),
    t('Unit Price'),
    t('All'),
    t('PDF Page'),
  );



  $views[$view->name] = $view;


  return $views;
}
