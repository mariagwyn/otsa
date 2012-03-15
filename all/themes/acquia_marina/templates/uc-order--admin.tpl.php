<?php

/**
 * @file
 * This file is the default admin notification template for Ubercart.
 */
?>

<h3><?php print t('Order number:'); ?> <?php print $order_admin_link; ?></h3>
<p><?php print t('Customer:'); ?> <?php print $order_first_name; ?> <?php print $order_last_name; ?> - <?php print $order_email; ?><br />
<?php print t('Order total:'); ?> <?php print $order_total; ?><br />
<?php print t('Shipping method:'); ?> <?php print $order_shipping_method; ?><br />
<?php print t('Payment method:'); ?> <strong><?php print $order_payment_method; ?></strong>
</p>
<h3><?php print t('Registration(s) Placed:'); ?></h3>
<p>Each item registered for lists the <strong>total amount</strong>, and if options exist, they are listed below the primary item.  Options with a price (such as a donation) are listed after the item name.</p>
<?php foreach ($products as $product): ?>
<strong><?php print $product->qty; ?> <?php print $product->title; ?></strong><br />
<?php print t('Total Amount: ')?><strong><?php print $product->total_price; ?></strong><br />
<?php print t('SKU'); ?>: <?php print $product->model; ?><br />
  <?php if (!empty($product->data['attributes'])): ?><strong><?php print t('Options Selected:')?></strong><ul>
    <?php foreach ($product->data['attributes'] as $attribute => $option): ?>
    <li><?php print t('@attribute: @options', array('@attribute' => $attribute, '@options' => implode(', ', (array)$option))); ?></li>
    <?php endforeach; ?></ul>
    <?php endif; ?>
<?php endforeach; ?>
</p>
<h4><?php print t('Order comments:'); ?></h4>
<p><?php print $order_comments; ?>
</p>
<h3><?php print t('OTSA Store Management Links'); ?></h3>
<p>You MUST be logged in to view these links</p>
<ul>
	<li>View all orders: <a href="http://otsamerica.org/admin/store/orders/view">http://otsamerica.org/admin/store/orders/view</a></li>
	<li>View orders by what was purchased: <a href="http://otsamerica.org/admin/store/reports/uc_who_bought_what">http://otsamerica.org/admin/store/reports/uc_who_bought_what</a></li>