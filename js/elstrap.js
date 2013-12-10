(function ($) {

if (typeof($.easing.easeInExpo == 'undefined')) {
  $.easing.easeInExpo = function (x, t, b, c, d) {
    return (t==0) ? b : c * Math.pow(2, 10 * (t/d - 1)) + b;
  };
};

$(document).ready(function() {
  $('#preloader').fadeTo(1000, 0.75, 'easeInExpo');
});

$(window).load(function() {
  $('#preloader').fadeOut(1000, 'easeInExpo');
});

Drupal.behaviors.elstrap = {
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
