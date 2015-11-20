<?php

/**
 * @file
 * Views Slideshow Configurable Controls HTML template.
 */
print '<div id="vscc_controls_' . $variables['vss_id'] .'" class="' . $classes . '">';
print $rendered_control_previous;
if (isset($rendered_control_pause)) {
  print $rendered_control_pause;
}
print $rendered_control_next;
print '</div>';
