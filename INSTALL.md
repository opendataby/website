This gide describe how up Open Data Belarus portal on debian or ubuntu server.
All commands you can found in `install.sh` file.

Additional requirements:
- nginx config
- sql dump
- data files

TODO:
- add complete nginx configuration
- add base sql dump
- add fetching data files from public source
- add complete mysql configuration
- automatically input passwords for mysql

Run:

    su
    bash install.sh

or

    sudo bash install.sh

1. Get debian or ubuntu (current gite tested on Debian Wheezy and Ubuntu 14.04 LTS).
2. Add repositories:

        echo "deb http://nginx.org/packages/OS/ CODENAME nginx" | tee /etc/apt/sources.list.d/nginx.list
        wget -q http://nginx.org/keys/nginx_signing.key -O- | apt-key add -
        apt-get update

3. Install web server components:

        apt-get -yq install nginx php5-mysql php5-fpm

4. Download and configure site

        mkdir -p /var/www/log
        chown -R www-data /var/www/log

        mkdir -p /var/www/odata/docroot
        apt-get -yq install git
        git clone https://github.com/opendataby/website.git /var/www/odata/docroot
        _connection="<?php
        \$databases = array (
          'default' =>
          array (
            'default' =>
            array (
              'database' => 'odb',
              'username' => 'odb',
              'password' => 'odb',
              'host' => 'localhost',
              'port' => '',
              'driver' => 'mysql',
              'prefix' => '',
            ),
          ),
        );
        "
        echo "$_connection" | tee /var/www/odata/docroot/sites/default/settings.local.php

        mkdir -p /var/www/odata/docroot/files
        tar -zxvf Archive.tar.gz -C /var/www/odata/docroot/files
        chown -R www-data /var/www/odata

5. Configure php5-fpm (fastcgi):

        echo "cgi.fix_pathinfo=0" | tee -a /etc/php5/fpm/php.ini
        service php5-fpm restart

6. Configure nginx. Currently this part need update. Config you can found there https://github.com/opendataby/configs/blob/master/odata.
7. Install and configure database:

        apt-get -yq install mysql-server
        #mysql_install_db
        #mysql_secure_installation
        _command="
            CREATE DATABASE odb CHARACTER SET utf8 COLLATE utf8_general_ci;
            CREATE USER 'odb'@'localhost' IDENTIFIED BY 'odb';
            GRANT ALL ON odb.* TO 'odb'@'localhost';
        "
        mysql -u root -p -e "$_command"

        mysql -u odb -p odb < dump.sql
        _command="
            DELETE FROM cache;
            DELETE FROM cache_admin_menu;
            DELETE FROM cache_block;
            DELETE FROM cache_bootstrap;
            DELETE FROM cache_entity_og_membership;
            DELETE FROM cache_entity_og_membership_type;
            DELETE FROM cache_field;
            DELETE FROM cache_filter;
            DELETE FROM cache_form;
            DELETE FROM cache_gravatar;
            DELETE FROM cache_image;
            DELETE FROM cache_l10n_update;
            DELETE FROM cache_libraries;
            DELETE FROM cache_menu;
            DELETE FROM cache_metatag;
            DELETE FROM cache_page;
            DELETE FROM cache_path;
            DELETE FROM cache_rules;
            DELETE FROM cache_token;
            DELETE FROM cache_variable;
            DELETE FROM cache_views;
            DELETE FROM cache_views_data;
        "
        mysql -u odb -p odb -e "$_command"
