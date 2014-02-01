<nav id="navbar" role="navigation" class="<?php print $navbar_classes; ?>">
  <div class="container">
    <div class="navbar-header">
      <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
        <span class="sr-only"><?php print t('Toggle navigation'); ?></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>

      <?php if ($logo): ?>
      <a class="logo navbar-btn pull-left" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
      </a>
      <?php endif; ?>

      <?php if (!empty($site_name)): ?>
      <a class="name navbar-brand" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
      <?php endif; ?>
    </div>

    <div class="collapes navbar-collapse">
      <?php if (!empty($primary_nav)): ?>
        <?php print render($primary_nav); ?>
      <?php endif; ?>

      <div class="navbar-right">
        <ul class="nav navbar-nav">
          <li>
            <a data-toggle="modal" href="#share">
              <strong>
                <?php print t('Share'); ?>
                <span class="fa fa-share"></span>
              </strong>
            </a>
          </li>

          <li class="dropdown">
            <a href="#" class="dropdown-toggle" data-toggle="dropdown"><?php print $language->native; ?> <span class="caret"></span></a>
            <?php print $language_menu; ?>
          </li>
        </ul>

        <?php if (!empty($secondary_nav)): ?>
          <?php print render($secondary_nav); ?>
        <?php endif; ?>
      </div>

      <?php if (!empty($page['navigation'])): ?>
        <?php print render($page['navigation']); ?>
      <?php endif; ?>
    </div>
  </div>
</nav>

<div class="main-container container">

  <header role="banner" id="page-header">
    <?php if (!empty($site_slogan)): ?>
      <div class="jumbotron">
        <p class="lead text-center text-primary"><?php print $site_slogan; ?></p>
      </div>
    <?php endif; ?>

    <?php print render($page['header']); ?>
  </header> <!-- /#header -->

  <div class="row">

    <?php if (!empty($page['sidebar_first'])): ?>
      <aside class="col-sm-4" role="complementary">
        <?php print render($page['sidebar_first']); ?>
      </aside>  <!-- /#sidebar-first -->
    <?php endif; ?>

    <section<?php print $content_column_class; ?>>
      <?php if (!empty($page['highlighted'])): ?>
        <div class="highlighted hero-unit"><?php print render($page['highlighted']); ?></div>
      <?php endif; ?>
      <?php if (!empty($breadcrumb)): print $breadcrumb; endif;?>

      <?php if ($panel): ?><div class="panel panel-default"><div class="panel-body"><?php endif; ?>
      <a id="main-content"></a>
      <?php print render($title_prefix); ?>
      <?php if (!empty($title)): ?>
        <h1 class="page-header"><?php print $title; ?></h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php print $messages; ?>
      <?php if (!empty($tabs)): ?>
        <?php print render($tabs); ?>
      <?php endif; ?>
      <?php if (!empty($page['help'])): ?>
        <div class="well"><?php print render($page['help']); ?></div>
      <?php endif; ?>
      <?php if (!empty($action_links)): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
      <?php if ($panel) : ?></div></div><?php endif; ?>
      </section>

    <?php if (!empty($page['sidebar_second'])): ?>
      <aside class="col-sm-4" role="complementary">
        <?php print render($page['sidebar_second']); ?>
      </aside>  <!-- /#sidebar-second -->
    <?php endif; ?>

  </div>
</div>

<footer class="footer container">
  <div class="row">
    <div class="col-sm-4">
      <?php print render($page['footer_left']); ?>
    </div>

    <div class="col-sm-4">
      <?php print render($page['footer_middle']); ?>
    </div>

    <div id="touch" class="col-sm-4">
      <div class="panel panel-default">
        <div class="panel-heading">
          <h3 class="panel-title"><?php print t('Touch me on'); ?></h3>
        </div>

        <div class="panel-body text-center">
          <ul class="list-inline">
            <li><a href="https://github.com/el7cosmos" title="<?php print t('Touch me on @service', array('@service' => 'github')); ?>" class="github" target="_blank"><span class="fa fa-github-square fa-5x"></span><span class="sr-only"> Github</span></a></li>
            <li><a href="https://twitter.com/el_abee" title="<?php print t('Touch me on @service', array('@service' => 'twitter')); ?>" class="twitter" target="_blank"><span class="fa fa-twitter-square fa-5x"></span><span class="sr-only"> Twitter</span></a></li>
            <li><a href="https://www.facebook.com/pages/eL-Abee/197066260350131" title="<?php print t('Touch me on @service', array('@service' => 'facebook')); ?>" class="facebook" target="_blank"><span class="fa fa-facebook-square fa-5x"></span><span class="sr-only"> Facebook</span></a></li>
            <li><a href="https://plus.google.com/107523342151360625331" title="<?php print t('Touch me on @service', array('@service' => 'google+')); ?>" class="google-plus" target="_blank"><span class="fa fa-google-plus-square fa-5x"></span><span class="sr-only"> Google+</span></a></li>
          </ul>
        </div>
      </div>
    </div>
  </div>

  <?php print render($page['footer']); ?>
</footer>
