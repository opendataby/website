#!/bin/sh
# $Id: bot_check.sh,v 1.1.2.2 2010/12/30 01:05:46 morbus Exp $

# This is one simple approach to ensuring your bot is always available.
# Here, we're just checking to see if "bot-start" is in the process list -
# if it isn't, we'll restart the bot using Drush. Since it's likely that
# the bot has crashed, we force a status reset to first clear the internal
# "connected" state. A script like this could be run through cron with:
#
#   * * * * * cd /path/to/bot/scripts && sh bot_check.sh >> /dev/null 2>&1

if ! ps ax | grep -v grep | grep bot-start
then
  drush -y bot-status-reset
  nohup drush bot-start >> bot.log &
fi
