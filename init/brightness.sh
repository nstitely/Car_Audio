#!/bin/bash
cd /sys/class/pwm/pwmchip0

if [ ! -e pwm0 ]
then
  echo 0 > export
fi
cd pwm0

echo 50000 > period

echo 50000 > duty_cycle
# echo 20000 > duty_cycle
# echo 200 > duty_cycle

echo 1 > enable
