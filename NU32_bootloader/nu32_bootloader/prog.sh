#!/bin/sh

hex=$(/bin/cygpath --unix "$1\\$2")
port=$3
baud=$4

if [ -z "$baud" ]; then
~/nu32_bootloader/nu32_boot.py -f "$hex" -p "$port"
else
~/nu32_bootloader/nu32_boot.py -f "$hex" -p "$port" -b "$baud"
fi
