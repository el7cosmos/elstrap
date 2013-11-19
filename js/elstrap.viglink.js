var vglnk = {
  api_url: '//api.viglink.com/api',
  key: Drupal.settings.elstrapViglink.apiKey
};

(function(d, t) {
  var s = d.createElement(t);
  s.type = 'text/javascript';
  s.async = true;
  s.src = ('https:' == document.location.protocol ? vglnk.api_url : '//cdn.viglink.com/api') + '/vglnk.js';
  var r = d.getElementsByTagName(t)[0];
  r.parentNode.insertBefore(s, r);
})(document, 'script');
