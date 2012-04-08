#!/bin/bash

MOUNT_POINT="/mnt/usb"

DEVICES=`cat /proc/partitions | grep -v sda | awk 'NR > 2 { print $4 }'`

`umount -f -l $MOUNT_POINT; mkdir -p $MOUNT_POINT`

echo "Found devices:";

if [ -z "$DEVICES" ]; then
	echo "no devices found";

	exit 1;
else
	echo "$DEVICES";

	for i in $DEVICES; do
		echo "mounting /dev/$i $MOUNT_POINT ...";
		
		`sudo mount /dev/$i $MOUNT_POINT &> /dev/null`

		if [ $? == 0 ]; then 
			echo "device $i mounted"
			exit 0;
		else
			echo "cannot mount device $i"
		fi
	done
fi

exit 1;
