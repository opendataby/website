#!/bin/sh

mkdir -p .bin

# Download composer
curl -sS https://getcomposer.org/installer | php -- --install-dir=.bin --filename=composer

.bin/composer install
