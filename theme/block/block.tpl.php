<section id="<?php print $block_html_id; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <div class="panel-heading">
      <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
    </div>
  <?php endif;?>
  <?php print render($title_suffix); ?>

  <div class="panel-body">
    <?php print $content ?>
  </div>

</section> <!-- /.block -->
