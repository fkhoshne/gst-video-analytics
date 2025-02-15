#!/bin/bash

CURDIR=$PWD
cd /tmp/

wget -O - https://github.com/eclipse/paho.mqtt.c/archive/v1.3.0.tar.gz | tar -xz
cd paho.mqtt.c-1.3.0
make
sudo make install
cd ..
sudo rm -rf paho.mqtt.c-1.3.0

wget -O - https://github.com/edenhill/librdkafka/archive/v1.0.0.tar.gz | tar -xz
cd librdkafka-1.0.0
./configure --prefix=/usr --libdir=/usr/lib/x86_64-linux-gnu/
make
sudo make install
cd ..
sudo rm -rf librdkafka-1.0.0

cd $CURDIR
