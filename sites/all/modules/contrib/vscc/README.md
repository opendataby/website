## Contents of this file
  
* Introduction
* Requirements
* Recommended modules
* Installation
* Configuration
* Customizing appearance
* Troubleshooting
* Maintainers

## Introduction

The **Views Slideshow Configurable Controls** (VSCC) module adds to
**Views Slideshow: Cycle** (part of the [**Views Slideshow**][1]
project) configurable and extensible controls.

In addition to the the original “Text” control type, this module
provides a “Configurable controls” control type, which, when chosen,
adds following options to the slideshow settings:

* Display the pause/resume control button (or not).
* Select a Controls skin.

Three skins are provided with the module: “Text” (same as original),
“White icons” or “Black icons”.

It is possible to add new skins to the available configurable
controls.  See the section *Customizing appearance* for more.

## Requirements

* [Views Slideshow][1]:<br>
  To provide the basic slideshow cycle functionality.


## Recommended modules

* [Advanced Help][2]:<br>
  When this module is enabled, display of the project's `README.md`
  will be rendered when you visit `help/vscc/README.md`.
* [Markdown filter][3]:<br>
  When this module is enabled, display of the project's `README.md`
  will be rendered with the markdown filter.

## Installation

Before installing this module set up your views slideshow cycle and
verify that it is working with the default text controls.

Then install this module as you would normally install a contributed
drupal module. See: [Installing modules][4] for further information.

## Configuration

In the view for your views slideshow cycle, locate the *Format* area
on the left-hand side of the Views GUI. Click *Settings* next to
*Slideshow*.

Change the *Controls Type* from “Text” to “Configurable controls”.

You can now configure the appearance of the controls using the
“Display pause control” checkbox and the “Controls skin” pull down
menu.

## Customizing appearance

If you want to replace the images used for the controls of the default
images with your own images, it is not recommended to replace supplied
images with your own images having the same file names.  Doing so will
result in your images being overwritten the next time you update the
project.

Instead, to be able to keep your own images below your theme folder.
You can do this by adding the following function in your theme's
`template.php` (replace “MYTHEME” with the name of your theme).


    function MYTHEME_vscc_element_black_icons($vars) {
      $image_vars = array(
        'path' => drupal_get_path('theme', 'MYTHEME') . '/images/vscc/' . $vars['element'] . '.png',
        'alt' => t($vars['element']),
        'title' => t($vars['element']),
      );
      return theme('image', $image_vars);
    }

This function hijacks the supplied “Black icons” skin and points it to
a different set of images.

For it to work, that different set of images must exist.  In the
directory `/images/vscc/` of your theme, place the four image files
with the graphics for your alternative controls.  In the function
above, it is assumed that they have the following names:

* `previous.png`
* `next.png`
* `pause.png`
* `resume.png`

If you want to use different file names and/or file extensions, you
need to alter the function accordingly.

To see the new images, you first need to clear cache and refresh the
page.

It is also possible to provide a new skin that appears in addition to
the skins supplied with the module. A demonstration of this is the
module named **VSCC new skin** that is supplied as part of this
project.  It is not intended to be used directly, but to be copied,
renamed and used as a template for your own skins.  See the comment at
the beginning of `vsccnewskin.module` for details.

## Troubleshooting

* If you use CSS to re-position the controls, and, as a result, they
  stop working, the most likely cause is that another DOM element is
  overlapping the VSCC controls.  To make sure the VCSS controls are
  active, make sure the VSCC controls have a higher z-index than any
  other DOM element in the same position.

* If the controls show up stacked vertically, the cause is usually
  that you have custom CSS on your site that makes the width of the
  area for the controls too narrow.  If you experience this, you need
  to change your CSS to allow enough horizontal space for the
  controls.

## Maintainers

This project has been sponsored by <em>Makina Corpus</em>, France.

* [David Stosik](https://www.drupal.org/u/david-stosik)
* [gisle](https://www.drupal.org/u/gisle)

Any help with development (patches, reviews, comments) are welcome.

[1]: https://www.drupal.org/project/views_slideshow
[2]: https://www.drupal.org/project/advanced_help
[3]: https://www.drupal.org/project/markdown
[4]: https://drupal.org/documentation/install/modules-themes/modules-7
