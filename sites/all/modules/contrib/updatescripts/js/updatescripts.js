/**
 * @copyright 	2012 (c) By Bright Solutions GmbH
 * @author		Marc Sven Kleinboehl
 *
 */

(function ($) {
	
	Drupal.behaviors.updatescripts = { attach: function(context) {
	 
			$('.updatescripts-show-log-link', context).click(function(e) {
				
				jQuery("#updatescripts-dialog").text (Drupal.settings.updatescripts.wait_loading_log);
 
				jQuery("#updatescripts-dialog").dialog({modal: true, maxHeight: 400, height: 400, title: 'Log' });
		 
				$.get(e.currentTarget.href, function(data) {
					$('#updatescripts-dialog').html (data);
				});
				
				e.preventDefault();
				
				return false;
			});
			return;
		}
	};
})(jQuery)