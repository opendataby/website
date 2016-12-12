# Development guidelines

## Initial configuration

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