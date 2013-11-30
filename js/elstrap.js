(function ($) {

Drupal.behaviors.elstrap = {
  attach: function (context, settings) {
    if (typeof($.easing.easeInExpo == 'undefined')) {
      $.easing.easeInExpo = function (x, t, b, c, d) {
        return (t==0) ? b : c * Math.pow(2, 10 * (t/d - 1)) + b;
      };
    };

    $('#preloader').fadeTo(1000, 0.75, 'easeInExpo');

    $(window).load(function() {
      $('#preloader').fadeOut(1000, 'easeInExpo');
    });
  }
};

})(jQuery);
