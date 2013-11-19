(function ($) {

$(window).load(function() {
  $("#status").fadeOut();
  $("#preloader").delay(350).fadeOut("slow");
})

Drupal.behaviors.elstrapFront = {
  attach: function (context, settings) {
    $(window).stellar();
  }
};

})(jQuery);
