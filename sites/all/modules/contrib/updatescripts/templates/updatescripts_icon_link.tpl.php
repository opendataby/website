<?php
/**
 * @copyright  2013+ (c) By Bright Solutions GmbH
 * @author     Marc Sven Kleinboehl
 *
 * Contains some API host methods for the update scripts. 
 *
 * @var boolean $blank      Indicates if the link target has to be opened in a new browser window.
 * @var string  $url        The URL of the links.
 * @var string  $icon_type  Contains the name of the icon type.
 */
?>
<a <?php isset ($blank) ? 'target="_blank"' : '' ; ?> href="<?php print $url; ?>" title="<?php print t('Download log file'); ?>">
	<img class="updatescripts-icon-link" src="<?php print base_path () . drupal_get_path ('module', 'updatescripts') .'/images/' . $icon_type; ?>.png" alt="<?php print t('Log file'); ?>" />
</a>