Updatescript processor
2012(c) By Bright Solutions GmbH
Written and developed by Marc Sven Kleinboehl
Contact: kleinboehl@brightsolutions.de

Please use the issue queue at drupal.org for making bug reports an feature requests.


ABOUT

The updatescript processor is a deployment tool for drupal configurations.
It provides a scripting environment that allows you to define your own
configurations as script files with incremental version-controlling.

The API of the updatescript processor supports functions to configure, disable and enable modules and themes.

Furthermore, it provides a drush function for other tasks that do not have corresponding API functions in the updatescript environment.

The updatescript processor can be used with CI systems for updating target systems like dev and stage installations.


UPDATESCRIPTS

Put your updatescripts into a "updatescripts" folder in the "sites/default" folder.
For multisite installation, please put the "updatescripts" folder into "sites/yoursite.tld".


UPDATESCRIPT EXAMPLE

--- CODE ---
<?php
// This will be logged.
$this->setAuthor ('John Doe');
$this->setDescription ('This will install the contact module');

// This will enable the contact module.
$this->setupModules (array ('contact'));

// This will finish processing this script for future processing iterations.
// You can create batch scripts by only calling this method conditionally.
$this->finished ();
--- END OF CODE ---


API

UpdatescriptAPI::setupModules     Installs/Enables specific modules.
UpdatescriptAPI::unsetupModules   Disables specific modules.
UpdatescriptAPI::setupThemes      Installs/Enables specific themes.
UpdatescriptAPI::unsetupThemes    Disables specific themes.
UpdatescriptAPI::setDefaultTheme  Sets a specific theme as default theme or admin theme.            
UpdatescriptAPI::log              Writes a text message to the log of the current running updatescript.
UpdatescriptAPI::drush            Runs a drush commandline.

IMPORTANT!

It is necessary to install drush. Otherwise, the drush method of the processor API will not work.

