(function ($) {

Drupal.behaviors.elstrapPageSpeedInsight = {
  attach: function (context, settings) {
    var rendered = false;
    $('#statistic').on('shown.bs.collapse', function () {
      if (!rendered) {
        var resources = $('#resources').get(0);
        if (typeof resources !== 'undefined') {
          resources = resources.getContext('2d');
          var statistic = new Chart(resources).Pie(settings.pageSpeedInsight, { segmentShowStroke: false });
          rendered = true;
        };
      };
    })
  }
};

})(jQuery);
