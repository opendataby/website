<?php
/**
 * @file
 * dkan_sitewide_demo_front.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function dkan_sitewide_demo_front_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = '[front] Google group';
  $fe_block_boxes->format = 'full_html';
  $fe_block_boxes->machine_name = 'google_group_front';
  $fe_block_boxes->body = '<iframe id="forum_embed"
 src="javascript:void(0)"
 scrolling="no"
 frameborder="0"
 width="900"
 height="500">
</iframe>

<script type="text/javascript">
 document.getElementById("forum_embed").src =
  "https://groups.google.com/forum/embed/?place=forum/opendata-belarus" +
  "&showsearch=true&showpopout=true&parenturl=" +
  encodeURIComponent(window.location.href);
</script>';

  $export['google_group_front'] = $fe_block_boxes;

  return $export;
}
