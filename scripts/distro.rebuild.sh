#!/bin/bash

# Pull down latest copy of DKAN.
./distro.pull.sh

GIT_ROOT=$(git rev-parse --show-toplevel)
cd $GIT_ROOT

echo "Removing docroot"
rm -rf docroot

echo "Building DKAN profile"
drush make -y scripts/build-dkan-profile.make docroot --no-gitinfofile

# Remove .gitignore files that are undesired.
rm docroot/profiles/dkan/.gitignore
rm docroot/profiles/dkan/libraries/Leaflet/.gitignore

echo "Symlinking sites directory to docroot/sites"
cd docroot
rm -rf sites
ln -s ../sites
echo "Symlinking .htaccess docroot/.htaccess"
rm .htaccess
ln -s ../.htaccess
echo "Symlinking robots.txt to docroot/robots.txt"
rm robots.txt
ln -s ../robots.txt
echo "Removing default .gitignore file"
rm .gitignore
echo "Removing Drupal .txt files"
rm CHANGELOG.txt COPYRIGHT.txt INSTALL.mysql.txt INSTALL.pgsql.txt INSTALL.sqlite.txt INSTALL.txt LICENSE.txt MAINTAINERS.txt PATCHES.txt README.txt UPGRADE.txt
