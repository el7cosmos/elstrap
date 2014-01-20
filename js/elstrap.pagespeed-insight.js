(function ($) {

Drupal.behaviors.elstrapPagespeedInsight = {
  attach: function (context, settings) {
    var rendered = false;
    $('#statistic').on('shown.bs.collapse', function() {
      if (!rendered) {
        var canvas = $('#resources');
        var resources = canvas.get(0);
        if (typeof resources !== 'undefined') {
          var options = {
            segmentStrokeWidth: 1,
          }
          resources = resources.getContext('2d');
          var statistic = new Chart(resources).Pie(canvas.data('stats'), options);
          rendered = true;
        };
      };
    });
  }
};

})(jQuery);
