(function ($) {

Drupal.behaviors.elstrapFacebook = {
  attach: function (context, settings) {
    $('#share-facebook').click(function() {
      FB.ui({
        method: 'feed',
        link: 'http://elabee.me',
        caption: 'Tak semua daun berwarna hijau',
      }, function(response) {});
    })
  }
};

})(jQuery);
