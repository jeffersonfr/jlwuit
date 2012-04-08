#ifndef MACROS_H
#define MACROS_H

#define USB_DEVICE_1		    		"/dev/sda1"
#define USB_DEVICE_2						"/dev/sdb1"
#define USB_DEVICE_3						"/dev/sdc1"

#define USB_ROOT			      		"/mnt/usbdisk"
#define USB_TEMP_DIR						"/mnt/usbdisk/.usbtmp"

#define APPLICATION_DESCRIPTOR	"/mnt/usbdisk/.usbtmp/application.xml"
#define UPDATE_DESCRIPTOR      	"/mnt/usbdisk/.usbtmp/update.xml"
#define UPDATE_FILE							"/mnt/usbdisk/softupdate.zip"

#define MOUNT_COMMAND_1 				"mount /dev/sda1 /mnt/usbdisk"
#define MOUNT_COMMAND_2					"mount /dev/sdb1 /mnt/usbdisk"
#define MOUNT_COMMAND_3					"mount /dev/sdc1 /mnt/usbdisk"

#define UMOUNT_COMMAND 			   	"umount -f -l /mnt/usbdisk"

#endif

