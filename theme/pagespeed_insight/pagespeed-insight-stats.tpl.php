<div class="panel panel-info">
  <div class="panel-heading">
    <h4 class="panel-title">
      <a data-toggle="collapse" href="#statistic">
        <?php print t('Page Statistic'); ?>
      </a>
    </h4>
  </div>
  <div id="statistic" class="panel panel-collapse collapse">
    <div class="panel-body text-center">
      <canvas id="resources"></canvas>
    </div>

    <ul class="list-group">
      <?php if (isset($stats['htmlResponseBytes'])): ?>
        <li class="list-group-item text-primary"><strong>HTML</strong> <span class="badge"><?php print format_size($stats['htmlResponseBytes']); ?></span></li>
      <?php endif; ?>
      <?php if (isset($stats['cssResponseBytes'])): ?>
        <li class="list-group-item text-success"><strong>CSS</strong> <span class="badge"><?php print format_size($stats['cssResponseBytes']); ?></span></li>
      <?php endif; ?>
      <?php if (isset($stats['imageResponseBytes'])): ?>
        <li class="list-group-item text-warning"><strong><?php print t('Image'); ?></strong> <span class="badge"><?php print format_size($stats['imageResponseBytes']); ?></span></li>
      <?php endif; ?>
      <?php if (isset($stats['javascriptResponseBytes'])): ?>
        <li class="list-group-item text-danger"><strong>JavaScript</strong> <span class="badge"><?php print format_size($stats['javascriptResponseBytes']); ?></span></li>
      <?php endif; ?>
      <?php if (isset($stats['flashResponseBytes'])): ?>
        <li class="list-group-item text-danger"><strong><?php print t('JavaScript'); ?></strong> <span class="badge"><?php print format_size($stats['flashResponseBytes']); ?></span></li>
      <?php endif; ?>
      <?php if (isset($stats['textResponseBytes'])): ?>
        <li class="list-group-item text-info"><strong><?php print t('Text'); ?></strong> <span class="badge"><?php print format_size($stats['textResponseBytes']); ?></span></li>
      <?php endif; ?>
      <?php if (isset($stats['otherResponseBytes'])): ?>
        <li class="list-group-item text-muted"><strong><?php print t('Other'); ?></strong> <span class="badge"><?php print format_size($stats['otherResponseBytes']); ?></span></li>
      <?php endif; ?>
    </ul>
  </div>
</div>
