<div class="node <?php print $node_classes; ?>" id="node-<?php print $node->nid; ?>"><div class="node-inner">

  <?php if ($page == 0): ?>
    <h2 class="title">
      <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
    </h2>
  <?php endif; ?>

  <?php if ($unpublished): ?>
    <div class="unpublished"><?php print t('Unpublished'); ?></div>
  <?php endif; ?>

  <?php if (count($taxonomy)): ?>
    <span class="taxonomy"><?php print t(' Tagged under: ') . $terms ?></span>
  <?php endif; ?>

  <?php if ($submitted): ?>
    <div class="submitted">
      <?php print $submitted; ?>
    </div>
  <?php endif; ?>

  <?php if ($picture) print $picture; ?>

	<?php
    // Since the cck date field is not in UNIX timestamp format, convert first
    $year = format_date($node->created, 'custom', 'Y');
    $month = format_date($node->created, 'custom', 'M');
    $date = format_date($node->created, 'custom', 'd');
    $day = format_date($node->created, 'custom', 'D');
  ?>

  <div class="content">
    <div class="post-date">
      <span class="day top"><?php print $day; ?></span>
	  <div class="btm">
		<span class="date"><?php print $date; ?></span>
		<span class="month"><?php print $month; ?></span>
		<span class="year"><?php print $year; ?></span>
	  </div>
    </div>
    <?php print $content; ?>
  </div>

  <?php if ($links): ?>
    <div class="links">
      <?php print $links; ?>
    </div>
  <?php endif; ?>

</div></div> <!-- /node-inner, /node -->
