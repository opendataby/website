<?php
// $Id: bot.drush.inc,v 1.1.2.2 2010/12/31 01:50:04 morbus Exp $

/**
 * @file
 * Drush commands for Bot module.
 */

/**
 * Implements hook_drush_command().
 */
function bot_drush_command() {
  $items = array();

  $items['bot-start'] = array(
    'description' => 'Start the IRC bot.',
    'examples' => array(
      'drush bot-start &'       => 'Start the IRC bot as a background process.',
      'nohup drush bot-start &' => 'Start the IRC bot as a background process using nohup.',
    ),
  );
  $items['bot-stop'] = array(
    'description' => 'Stops the IRC bot.',
  );
  $items['bot-status'] = array(
    'description' => 'Returns the connection state of the IRC bot.',
  );
  $items['bot-status-reset'] = array(
    'description' => 'Resets the connection state of the IRC bot',
  );

  return $items;
}

/**
 * Drush command handler for "drush bot-start".
 */
function drush_bot_start() {
  if (bot_status_get() == BOT_STATUS_DISCONNECTED) {
    require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'bot') . '/bot.smartirc.inc';
    bot_smartirc_start(); // Deathwing doesn't care what level you are. Nor does Morbus.
  }

  drush_log(dt('The IRC bot is already connected. If this is wrong, try "drush bot-status-reset".'), 'error');
}

/**
 * Drush command handler for "drush bot-start".
 */
function drush_bot_stop() {
  if (bot_status_get() == BOT_STATUS_CONNECTED) {
    lock_acquire('bot_disconnect', 45); // it shouldn't take long to end it all.
    drush_print(dt('Disconnecting the IRC bot. This might take up to 45 seconds.'));
    while (!(bot_status_get() == BOT_STATUS_DISCONNECTED || lock_may_be_available('bot_disconnect'))) {
      sleep(1); // check the status every second. most should disconnect within 20 seconds.
    }

    drush_log(dt('The IRC bot is disconnected.'), 'success');
    return lock_release('bot_disconnect'); // WEEP.
  }

  drush_log(dt('The IRC bot is already disconnected.'), 'error');
}

/**
 * Drush command handler for "drush bot-status".
 */
function drush_bot_status() {
  switch (bot_status_get()) {
    case BOT_STATUS_DISCONNECTED: drush_log(dt('The IRC bot is disconnected.'), 'ok');  break;
    case BOT_STATUS_CONNECTING:   drush_log(dt('The IRC bot is connecting.'), 'ok');    break;
    case BOT_STATUS_CONNECTED:    drush_log(dt('The IRC bot is connected.'), 'ok');     break;
  }

  return;
}

/**
 * Drush command handler for "drush bot-status-reset".
 */
function drush_bot_status_reset() {
  if (lock_may_be_available('bot_disconnect')) {
    if (drush_confirm(dt("Are you sure you want to reset the IRC bot's connect status?"))) {
      variable_set('bot_status', BOT_STATUS_DISCONNECTED); // NO LIKELY YOU GO 'WAY NOW KTHX.
      drush_log(dt("The IRC bot's connection status has been reset."), 'ok');
    }
  }
  else {
    drush_log(t('The IRC bot is disconnecting. Wait 45 seconds and then try again.'), 'warning');
  }
}
