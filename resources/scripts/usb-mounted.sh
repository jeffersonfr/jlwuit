#!/bin/bash

MOUNT_POINT="/mnt/usb"

DEVICES=`cat /proc/partitions | grep -v sda | awk 'NR > 2 { print $4 }'`

if [ -z "$DEVICES" ]; then
	echo "USB does not mounted ...";

	exit 0;
fi

echo "USB mounted ...";

exit 1;
