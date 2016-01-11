(function ($) {
  /**
   * Drupal.Nodejs.callback on node update.
   */
  Drupal.Nodejs.callbacks.ajaxCommentsNodejs = {
    callback: function (message) {
      if (message.authToken != Drupal.settings.nodejs.authToken) {
        if (typeof message.action === 'undefined') {
          Drupal.nodejs_ajax.runCommands(message);
        }
        else {
          if (message.action == 'updated' && $('.comment-wrapper-' + message.cid).length == 0) {
            message.action = 'added';
          }
          var commentUrl = Drupal.settings.basePath + 'ajax_comments_nodejs/view/' + message.action + '/' + message.cid;
          var ajaxSettings = {url : commentUrl};
          var ajaxRequest = new Drupal.ajax(false, false, ajaxSettings);
          ajaxRequest.eventResponse(ajaxRequest, {});
        }
      }
    }
  };

  // Drupal.ajaxCommentsNodejs
  Drupal.behaviors.ajaxCommentsNodejs = {
    attach: function(context, settings) {
      $('.ajax-comments-nodejs-new', context).once('ajax-comments-nodejs-new-behavior', function() {
        if ($.isFunction($.fn.live)) {
          $('.ajax-comments-nodejs-new', context).live('mouseenter', function() {
            $(this).removeClass('ajax-comments-nodejs-new');
            $(this).unbind('mouseenter')
          });
        }
        else {
          $('.ajax-comments-nodejs-new', context).on('mouseenter', function() {
            $(this).removeClass('ajax-comments-nodejs-new');
            $(this).unbind('mouseenter')
          });
        };
      });
      $('.ajax-comments-nodejs-updated', context).once('ajax-comments-nodejs-updated-behavior', function() {
        if ($.isFunction($.fn.live)) {
          $('.ajax-comments-nodejs-updated', context).live('mouseenter', function() {
            $(this).removeClass('ajax-comments-nodejs-updated');
            $(this).unbind('mouseenter')
          });
        }
        else {
          $('.ajax-comments-nodejs-updated', context).on('mouseenter', function() {
            $(this).removeClass('ajax-comments-nodejs-updated');
            $(this).unbind('mouseenter')
          });
        };
      });
    }
  };

}(jQuery));

