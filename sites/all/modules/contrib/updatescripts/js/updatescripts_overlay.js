/*
 * @copyright 	2012 (c) By Bright Solutions GmbH
 * @author		Marc Sven Kleinboehl
 *
 */

(function ($) {
	
	Drupal.behaviors.updatescripts_overlay = { attach: function(context) {

			$('#updatescripts-overlay-button').mouseover (function (e) {
				$('#updatescripts-overlay-button-link').show ();
			});
			
			$('#updatescripts-overlay-button').mouseout (function (e) {
				$('#updatescripts-overlay-button-link').hide ();
			});
			
		}
	};
})(jQuery)