<div class="panel panel-<?php print $state; ?>">
  <div class="panel-heading">
    <h4 class="panel-title">
      <a data-toggle="collapse" href="#<?php print $id; ?>">
        <?php print $rule['localizedRuleName']; ?>
      </a>
    </h4>
  </div>
  <div id="<?php print $id; ?>" class="panel-collapse collapse<?php print $rule['ruleImpact'] ? ' in' : ''; ?>">
    <div class="panel-body">
      <?php foreach ($rule['urlBlocks'] as $block): ?>
        <p><?php print theme('pagespeed_insight_header', array('header' => $block['header'])); ?></p>
        <?php if (isset($block['urls'])): ?>
          <ul>
            <?php foreach ($block['urls'] as $url): ?>
              <li><?php print theme('pagespeed_insight_result', array('result' => $url['result'])); ?></li>
            <?php endforeach; ?>
          </ul>
        <?php endif; ?>
      <?php endforeach; ?>
    </div>
  </div>
</div>
