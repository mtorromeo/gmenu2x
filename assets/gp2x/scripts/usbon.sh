#!/bin/bash
# $1 = sd|nand|root
# defaults to sd (compatible with previous versions)
export PATH=$PATH:/sbin
modprobe net2272
if [ $1 = "nand" ]; then
	umount /mnt/nand || mount -o remount,loop,ro /mnt/nand
	modprobe g_file_storage file=/dev/loop/7
elif [ $1 = "root" ]; then
	mount -o remount,loop,ro /
	modprobe g_file_storage file=/dev/mtdblock/3
else
	umount /mnt/sd || mount -o remount,loop,ro /mnt/sd
	modprobe g_file_storage file=/dev/mmcsd/disc0/disc
fi
