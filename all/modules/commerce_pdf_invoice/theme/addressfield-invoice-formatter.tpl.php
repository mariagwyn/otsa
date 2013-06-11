<?php print implode('<br />', array_filter(array(
    $address['thoroughfare'],
    $address['premise'],
    $address['sub_premise'],
    $address['dependent_locality'],
  )));
?>
<br />
<?php print $address['country'] . ' - ' . $address['postal_code'] . ' ' . $address['locality'] ?>
