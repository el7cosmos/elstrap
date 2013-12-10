<div class="panel panel-info">
  <div class="panel-heading">
    <h4 class="panel-title">
      <a data-toggle="collapse" href="#statistic">
        <?php print t('Page Statistic'); ?>
      </a>
    </h4>
  </div>
  <div id="statistic" class="panel-collapse collapse">
    <div class="panel-body">
      <div class="row">
        <div class="col-xs-12 col-sm-5 col-md-3 text-center">
          <canvas id="resources" width="250" height="150"></canvas>
        </div>
        <div class="col-xs-12 col-sm-7 col-md-9">
          <ul>
            <?php if (isset($stats['htmlResponseBytes'])): ?>
              <li class="text-primary">HTML <span class="badge pull-right"><?php print format_size($stats['htmlResponseBytes']); ?></span></li>
            <?php endif; ?>
            <?php if (isset($stats['cssResponseBytes'])): ?>
              <li class="text-success">CSS <span class="badge pull-right"><?php print format_size($stats['cssResponseBytes']); ?></span></li>
            <?php endif; ?>
            <?php if (isset($stats['imageResponseBytes'])): ?>
              <li class="text-warning"><?php print t('Image'); ?> <span class="badge pull-right"><?php print format_size($stats['imageResponseBytes']); ?></span></li>
            <?php endif; ?>
            <?php if (isset($stats['javascriptResponseBytes'])): ?>
              <li class="text-danger">JavaScript <span class="badge pull-right"><?php print format_size($stats['javascriptResponseBytes']); ?></span></li>
            <?php endif; ?>
            <?php if (isset($stats['flashResponseBytes'])): ?>
              <li class="text-danger"><?php print t('JavaScript'); ?> <span class="badge pull-right"><?php print format_size($stats['flashResponseBytes']); ?></span></li>
            <?php endif; ?>
            <?php if (isset($stats['textResponseBytes'])): ?>
              <li class="text-info"><?php print t('Text'); ?> <span class="badge pull-right"><?php print format_size($stats['textResponseBytes']); ?></span></li>
            <?php endif; ?>
            <?php if (isset($stats['otherResponseBytes'])): ?>
              <li class="text-muted"><?php print t('Other'); ?> <span class="badge pull-right"><?php print format_size($stats['otherResponseBytes']); ?></span></li>
            <?php endif; ?>
          </ul>
        </div>
      </div>
    </div>
  </div>
</div>
