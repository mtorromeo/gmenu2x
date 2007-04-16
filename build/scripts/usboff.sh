#!/bin/bash
rmmod g_file_storage
rmmod net2272
if [ $1 = "nand" ]; then
	mount /mnt/nand || mount -o remount,rw /mnt/nand
elif [ $1 = "root" ]; then
	mount -o remount,rw /
else
	mount /mnt/sd || mount -o remount,rw /mnt/sd
fi
