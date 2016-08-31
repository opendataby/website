/**
 * @file
 * Custom JS for the CodeMirror interface on admin pages.
 */

(function ($) {
  Drupal.behaviors.cpnCodeMirrorAdmin = {

    attach: function(context, settings) {
      var button = ' <a href="#" class="cpn-toggle">Enable syntax highlighting</a>.';
      $('.form-item-cpn-wrapper-block-css, .form-item-cpn-wrapper-block-js', context).each(function() {
        $('.description', this).append(button);
      });
      $('.form-item-cpn-wrapper-node-css, .form-item-cpn-wrapper-node-js', context).each(function() {
        $('.description', this).append(button);
      });
      $('.form-item-cpn-global-css, .form-item-cpn-global-js', context).each(function() {
        $('.description', this).append(button);
      });

      // Toggle syntax highlighting.
      $('.cpn-toggle', context).click(function() {
        var $textarea = $(this).parents('.form-item').find('textarea');
        var $grippie = $textarea.parents('.resizable-textarea').find('.grippie');
        var type = $textarea.attr('id')
          .replace('edit-cpn-wrapper-block-', '')
          .replace('edit-cpn-wrapper-node-', '')
          .replace('edit-cpn-global-', '');
        var mode = type == 'css' ? 'css' : 'javascript';

        // Enable.
        if (!$(this).hasClass('enabled')) {
          $grippie.hide();
          var editor = CodeMirror.fromTextArea($textarea.get(0), {
            mode: mode,
            tabSize: 2,
            gutters: ['CodeMirror-linenumbers'],
            lineNumbers: true
          });
          $(this).data('editor', editor);
          $(this).text(Drupal.t('Disable syntax highlighting')).addClass('enabled');
        }

        // Disable.
        else {
          $(this).data('editor').toTextArea();
          $grippie.show();
          $(this).text(Drupal.t('Enable syntax highlighting')).removeClass('enabled');
        }
        return false;
      });
    }

  };
})(jQuery);
