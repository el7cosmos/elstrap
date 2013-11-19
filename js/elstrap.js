(function ($) {

Drupal.behaviors.elstrap = {
  attach: function (context, settings) {
    $('html').niceScroll({
      cursoropacitymax: 0.5,
      cursorborder: 'none',
      cursorminheight: 60,
    });
  }
};

})(jQuery);
