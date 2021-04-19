#!/bin/bash

# Power Detect
v1=`cat /sys/class/gpio/gpio17/value`
# Power Enabled
v2=`cat /sys/class/gpio/gpio27/value`

# Make sure we are applying power to the main relay - I.E. fully booted
# If so, check if ignition is cut
if [ "$v2" == "1" -a "$v1" == "0" ]
then
  poweroff
fi
