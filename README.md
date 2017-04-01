# Development guidelines

## General

Please commit everything to the `dev` branch.

## Requirements

In order to make changes here you need a way to run PHP scripts (also from the command line) on your local machine and a database. Apps like MAMP, XAMPP and any LAMP/LEMP stacks will do just fine.

Sanitized version of the database to start with can be requested by saying hello to help@opendata.by (briefly introduce yourself).

To work on styling you don't need LAMP/LEMP stack at all, as you can save the static page to your local machine and edit theme files directly in the repository.
Theme path is `/docroot/sites/all/themes/data_radix`. You need a way to compile CSS files from SCSS (i.e. Compass).

## Initial installation and configuration

1. Pull the `dev` branch from this repository

2. Provided that you have Composer ready, run `composer install`. It will download all required libraries.

3. Run `.bin/phing update` to rebuild the local website according to the latest changes from Git.

Make sure the website has the English locale, otherwise all exports will be screwed. Insert
the following code into settings.local.php (the same file with db connection details):

```
/**
 * Keep English as default site language.
 */
$conf['language_default'] = (object) array(
  'language' => 'en',
  'name' => 'English',
  'native' => 'English',
  'direction' => '0',
  'enabled' => '1',
  'prefix' => 'en',
);
```

## Interface translations

Interface translations are stored in `/docroot/sites/default/translations as .po files.`

Two ways of translating the website exist:

1. Edit .po files manually and commit to the remote repository (`dev` branch). Use any gettext catalogs (.po files) editor. Recommended one is [Poedit](https://poedit.net).

When working with .po files make sure you'e got the latest version of files from Git.

2. Translate strings available for translation using Drupal's native translation interface provided by the i18n module. You have to have your local Drupal installation of the website to do that.

Go to `/admin/config/regional/translate/translate`, edit the strings using a configuration form, save and export all the translations via `/admin/config/regional/translate/export`.

Again, before editing, saving and exporting or making any changes make sure you'e pulled the recent version of the codebase from Git and ran `.bin/phing drupal:config:import-translations`, OR (if you prefer the UI), import the .po files using the "Import" tab.
 
Whatever method you use just remember - get the most recent version of the stuff you what to change from Git first and import it to Drupal. 

