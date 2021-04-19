#!/bin/bash

export XDG_RUNTIME_DIR=/tmp
export LD_LIBRARY_PATH=/home/pi/weston/install/lib/:/home/pi/weston/install/lib/arm-linux-gnueabihf/
export QT_QPA_PLATFORM=wayland
cd /home/pi/weston/install/bin/
openvt -s ./weston -- --log=dump.txt -c /home/pi/weston.ini
