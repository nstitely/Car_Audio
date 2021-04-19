#!/bin/bash

# Power Detect Pin
echo 17 > /sys/class/gpio/export
# Power Enable Pin
echo 27 > /sys/class/gpio/export

# Activate Relay
cd /sys/class/gpio/
echo out > gpio27/direction
echo 1 > gpio27/value

exit 0
