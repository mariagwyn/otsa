<?php
?>

  <div id="page" class="page">
    <div id="page-inner" class="page-inner">
      <?php print render($page['header_top']); ?>

      <!-- header-group region: width = grid_width -->
      <div id="header-group-wrapper" class="header-group-wrapper full-width clearfix">
        <div id="header-group" class="header-group region <?php print $grid_width; ?>">
          <div id="header-group-inner" class="header-group-inner inner clearfix">
            <div id="header-blocks"><?php print render($page['header']); ?></div>
            <?php if ($logo || $site_name || $site_slogan): ?>
            <div id="header-site-info" class="header-site-info block">
              <div id="header-site-info-inner" class="header-site-info-inner inner">
                <?php if ($logo): ?>
                <div id="logo">
                  <a href="<?php print check_url($front_page); ?>" title="<?php print t('Home'); ?>"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
                </div>
                <?php endif; ?>
                <?php if ($site_name || $site_slogan): ?>
                <div id="site-name-wrapper" class="clearfix">
                  <?php if ($site_name): ?>
                  <span id="site-name"><a href="<?php print check_url($front_page); ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a></span>
                  <?php endif; ?>
                  <?php if ($site_slogan): ?>
                  <span id="slogan"><?php print $site_slogan; ?></span>
                  <?php endif; ?>
                </div><!-- /site-name-wrapper -->
                <?php endif; ?>
              </div><!-- /header-site-info-inner -->
            </div><!-- /header-site-info -->
            <?php endif; ?>
          </div><!-- /header-group-inner -->

          <?php print render($page['main_menu']); ?>
        </div><!-- /header-group -->
      </div><!-- /header-group-wrapper -->

<div id="preface-top-outer"><div id="preface-top-wrapper"><div id="preface-top-inner"><?php print render($page['preface_top']); ?> 
	<?php print theme('grid_block', array('content' => $breadcrumb, 'id' => 'breadcrumbs')); ?>
	</div></div></div>
 
      <!-- main region: width = grid_width -->
      <div id="main-wrapper" class="main-wrapper full-width clearfix">
        <div id="main" class="main region <?php print $grid_width; ?>">
          <div id="main-inner" class="main-inner inner clearfix">
            <?php print render($page['sidebar_first']); ?>

            <!-- main group: width = grid_width - sidebar_first_width -->
            <div id="main-group" class="main-group region nested <?php print $main_group_width; ?>">
              <div id="main-group-inner" class="main-group-inner inner">
                
                
             <?php print render($page['preface_bottom']); ?> 

                <div id="main-content" class="main-content region nested">
                  <div id="main-content-inner" class="main-content-inner inner">
                    <!-- content group: width = grid_width - sidebar_first_width - sidebar_second_width -->
                    <div id="content-group" class="content-group region nested <?php print $content_group_width; ?>">
                      <div id="content-group-inner" class="content-group-inner inner">
                        
                        <?php print theme('grid_block', array('content' => $messages, 'id' => 'content-messages')); ?>

                        <div id="content-region" class="content-region region nested">
                          <div id="content-region-inner" class="content-region-inner inner">
                            <a name="main-content-area" id="main-content-area"></a>
                            <?php print theme('grid_block', array('content' => render($page['help']), 'id' => 'content-help')); ?>
                            <div id="content-inner" class="content-inner block">
                              <div id="content-inner-inner" class="content-inner-inner inner">
                                <?php print render($title_prefix); ?>
                                <?php if ($title): ?>
                                <h1 class="title"><?php print $title; ?></h1>
                                <?php endif; ?>
                            <?php print theme('grid_block', array('content' => render($tabs), 'id' => 'content-tabs')); ?>
                                <?php print render($title_suffix); ?>
                                <?php if ($action_links): ?>
                                <ul class="action-links"><?php print render($action_links); ?></ul>
                                <?php endif; ?>
                                <?php if ($page['content']): ?>
                                <div id="content-content" class="content-content">
                                  <?php print render($page['content']); ?>
                                </div><!-- /content-content -->
                                <?php endif; ?>
                              </div><!-- /content-inner-inner -->
                            </div><!-- /content-inner -->
                          </div><!-- /content-region-inner -->
                        </div><!-- /content-region -->

                      </div><!-- /content-group-inner -->
                    </div><!-- /content-group -->

                    <?php print render($page['sidebar_second']); ?>
                  </div><!-- /main-content-inner -->
                </div><!-- /main-content -->

                <?php print render($page['postscript_top']); ?>
              </div><!-- /main-group-inner -->
            </div><!-- /main-group -->
          </div><!-- /main-inner -->
        </div><!-- /main -->
      </div><!-- /main-wrapper -->

      <?php print render($page['postscript_bottom']); ?>
      <?php print render($page['footer']); ?>
    </div><!-- /page-inner -->
  </div><!-- /page -->
