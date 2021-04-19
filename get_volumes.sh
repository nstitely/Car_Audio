#!/bin/bash
rear=`i2cget -y 1 0x4b`
front=`i2cget -y 1 0x4a`

echo "Front: $front; Rear: $rear"
