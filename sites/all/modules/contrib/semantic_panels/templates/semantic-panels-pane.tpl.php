<?php
/**
 * @file
 * Pane template.
 */
?>
<?php if ($wrapper_type): ?>
  <<?php print $wrapper_type; ?> class="<?php print $classes; ?>" <?php print $id; ?> <?php print $attributes; ?>>
<?php endif; ?>

    <?php if ($admin_links): ?>
      <?php print $admin_links; ?>
    <?php endif; ?>

    <?php if ($title_html): ?>
      <?php print $title_html; ?>
    <?php endif; ?>

    <?php if ($feeds): ?>
      <div class="feed">
        <?php print $feeds; ?>
      </div>
    <?php endif; ?>

    <?php if ($content_html): ?>
      <?php print $content_html; ?>
    <?php endif; ?>

    <?php if ($links): ?>
      <div class="links">
        <?php print $links; ?>
      </div>
    <?php endif; ?>

    <?php if ($more): ?>
      <div class="more-link">
        <?php print $more; ?>
      </div>
    <?php endif; ?>

<?php if ($wrapper_type): ?>
  </<?php print $wrapper_type; ?>>
<?php endif; ?>
