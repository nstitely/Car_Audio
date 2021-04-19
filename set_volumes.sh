echo "Front: $1"
echo "Rear: $2"

i2cset -y 1 0x4a 0x${1}
i2cset -y 1 0x4b 0x${2}
