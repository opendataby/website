<?php
// $Id: bot.smartirc.inc,v 1.1.2.4 2010/12/29 21:36:21 morbus Exp $

/**
 * @file
 * Classes and functions that wrap Drupal up for Net_SmartIRC.
 */

/**
 * Start the Net_SmartIRC bot.
 */
function bot_smartirc_start() {
  require_once 'Net/SmartIRC.php';
  require_once 'Net/SmartIRC/defines.php';
  variable_set('bot_status', BOT_STATUS_CONNECTING);

  // prevent MySQL timeouts on slow channels.
  db_query('SET SESSION wait_timeout = 86400');

  // initialize the bot with some sane defaults.
  global $irc; // allow it to be slurped by Drupal modules if need be.
  $irc = new Net_SmartIRC(); // MmmmmmM. The IRC object itself. Magick happens here.
  $irc->nreplycodes = $SMARTIRC_nreplycodes; // unreliably set from $_GLOBALS, so force it here.
  $irc->setDebug( variable_get('bot_debugging', 0) ? SMARTIRC_DEBUG_ALL : SMARTIRC_DEBUG_NONE );
  // the (boolean) here is required, as Net_SmartIRC doesn't respect a FAPI checkbox value of 1, only TRUE.
  $irc->setAutoReconnect((boolean) variable_get('bot_auto_reconnect', 1)); // reconnect to the server if disconnected.
  $irc->setAutoRetry((boolean) variable_get('bot_auto_retry', 1)); // retry if a server connection fails.
  $irc->setUseSockets((boolean) variable_get('bot_real_sockets', 1)); // socket_connect or fsockopen?
  $irc->setChannelSyncing(TRUE); // keep a list of joined users per channel.

  // send every message type the library supports to our wrapper class.
  // we can automate the creation of these actionhandlers, but not the
  // class methods below (only PHP 5 supports default methods easily).
  $irc_message_types = array(
    'UNKNOWN',    'CHANNEL', 'QUERY',    'CTCP',        'NOTICE',       'WHO',
    'JOIN',       'INVITE',  'ACTION',   'TOPICCHANGE', 'NICKCHANGE',   'KICK',
    'QUIT',       'LOGIN',   'INFO',     'LIST',        'NAME',         'MOTD',
    'MODECHANGE', 'PART',    'ERROR',    'BANLIST',     'TOPIC',        'NONRELEVANT',
    'WHOIS',      'WHOWAS',  'USERMODE', 'CHANNELMODE', 'CTCP_REQUEST', 'CTCP_REPLY',
  );

  foreach ($irc_message_types as $irc_message_type) {
    $class = 'bot_irc_msg_' . drupal_strtolower($irc_message_type);
    $irc->registerActionhandler(constant('SMARTIRC_TYPE_' . $irc_message_type), '.*', new $class(), 'invoke');
  }

  // set up a timers similar to Drupal's hook_cron(), multiple types. I would have
  // liked to just pass a parameter to a single function, but SmartIRC can't do that.
  $irc->registerTimehandler(300000, new bot_irc_bot_cron(),         'invoke'); // 5 minutes.
  $irc->registerTimehandler(60000,  new bot_irc_bot_cron_faster(),  'invoke'); // 1 minute.
  $irc->registerTimehandler(15000,  new bot_irc_bot_cron_fastest(), 'invoke'); // 15 seconds.

  // connect and begin listening.
  $irc->connect(variable_get('bot_server', 'irc.freenode.net'), variable_get('bot_server_port', 6667));
  $irc->login(variable_get('bot_nickname', 'bot_module'), variable_get('bot_nickname', 'bot_module') . ' :http://drupal.org/project/bot', 8, variable_get('bot_nickname', 'bot_module'), variable_get('bot_password'));
  variable_set('bot_status', BOT_STATUS_CONNECTED);

  // channel joining has moved to bot_irc_bot_cron_fastest().
  // read that function for the rationale, and what we gain from it.

  $irc->listen(); // go into the forever loop - no code after this is run.
  $irc->disconnect(); // if we stop listening, disconnect properly.
  // see bot_irc_bot_cron_fastest() for another disconnect() call.
  variable_set('bot_status', BOT_STATUS_DISCONNECTED);
}

/**
 * A Drupal wrapper for the various Net_SmartIRC handlers.
 */
class bot_smartirc_wrapper {

  /**
   * Handle all Net_SmartIRC callbacks.
   *
   * @param &$irc
   *    The Net_SmartIRC $irc object.
   * @param &$data
   *    The Net_SmartIRC data object for this message.
   */
  function invoke(&$irc, &$data = NULL) {
    if (isset($data)) {
      // Net_SmartIRC passes data through in the encoding received from the
      // IRC server. The IRC server, in turn, passes it through as received
      // from the remote client. If the remote client is using a single byte
      // encoding (ISO-8559-1 aka Latin-1), this will result in mangled
      // characters or may raise errors for 8-bit characters. Under Drupal 7
      // and PHP 5.3, this caused an "invalid multibyte sequence" warning
      // from htmlspecialchars() and a PDOException that crashed the bot.
      // (To reproduce: use XChat to connect to a server as latin1, but then
      // send an 8-bit Latin-1 character like a Euro [€]). Since we cannot
      // control the encoding of IRC messages like we can control the encoding
      // of web form submissions, we need to force UTF-8 for all messages.
      if (function_exists('mb_detect_encoding')) {
        $encoding = mb_detect_encoding($data->message, 'UTF-8, ISO-8859-1');
        if ($encoding != 'UTF-8') { // no point of converting it already.
          // we only convert over message related elements and leave the
          // existing parses (nick, ident, host, type, channel, etc.) alone.
          $data->message      = mb_convert_encoding($data->message, 'UTF-8', $encoding);
          $data->rawmessage   = mb_convert_encoding($data->rawmessage, 'UTF-8', $encoding);
          $data->messageex    = explode(' ', $data->message);
          $data->rawmessageex = explode(' ', $data->rawmessage);
          watchdog('bot', 'Converted @encoding to UTF-8: @message.', array('@encoding' => $encoding, '@message' => $data->message), WATCHDOG_INFO);
        }
      }
    }

    // The name of the hook is a substring of the class name.
    $hook = drupal_substr(get_class($this), drupal_strlen('bot_'));

    // Give modules an opportunity to stop message processing.
    foreach (module_implements('irc_access') as $module) {
      $function = "{$module}_irc_access";
      $result = $function($hook, $data);

      // Stop handling this request if FALSE.
      if (isset($result) && $result === FALSE) {
        return;
      }
    }

    // Proceed normally.
    module_invoke_all($hook, $data);
  }
}

// Bot cron sub-classes.
class bot_irc_bot_cron          extends bot_smartirc_wrapper {}
class bot_irc_bot_cron_faster   extends bot_smartirc_wrapper {}
class bot_irc_bot_cron_fastest  extends bot_smartirc_wrapper {}

// IRC message sub-classes.
class bot_irc_msg_unknown       extends bot_smartirc_wrapper {}
class bot_irc_msg_channel       extends bot_smartirc_wrapper {}
class bot_irc_msg_query         extends bot_smartirc_wrapper {}
class bot_irc_msg_ctcp          extends bot_smartirc_wrapper {}
class bot_irc_msg_notice        extends bot_smartirc_wrapper {}
class bot_irc_msg_who           extends bot_smartirc_wrapper {}
class bot_irc_msg_join          extends bot_smartirc_wrapper {}
class bot_irc_msg_invite        extends bot_smartirc_wrapper {}
class bot_irc_msg_action        extends bot_smartirc_wrapper {}
class bot_irc_msg_topicchange   extends bot_smartirc_wrapper {}
class bot_irc_msg_nickchange    extends bot_smartirc_wrapper {}
class bot_irc_msg_kick          extends bot_smartirc_wrapper {}
class bot_irc_msg_quit          extends bot_smartirc_wrapper {}
class bot_irc_msg_login         extends bot_smartirc_wrapper {}
class bot_irc_msg_info          extends bot_smartirc_wrapper {}
class bot_irc_msg_list          extends bot_smartirc_wrapper {}
class bot_irc_msg_name          extends bot_smartirc_wrapper {}
class bot_irc_msg_motd          extends bot_smartirc_wrapper {}
class bot_irc_msg_modechange    extends bot_smartirc_wrapper {}
class bot_irc_msg_part          extends bot_smartirc_wrapper {}
class bot_irc_msg_error         extends bot_smartirc_wrapper {}
class bot_irc_msg_banlist       extends bot_smartirc_wrapper {}
class bot_irc_msg_topic         extends bot_smartirc_wrapper {}
class bot_irc_msg_nonrelevant   extends bot_smartirc_wrapper {}
class bot_irc_msg_whois         extends bot_smartirc_wrapper {}
class bot_irc_msg_whowas        extends bot_smartirc_wrapper {}
class bot_irc_msg_usermode      extends bot_smartirc_wrapper {}
class bot_irc_msg_channelmode   extends bot_smartirc_wrapper {}
class bot_irc_msg_ctcp_request  extends bot_smartirc_wrapper {}
class bot_irc_msg_ctcp_reply    extends bot_smartirc_wrapper {}
