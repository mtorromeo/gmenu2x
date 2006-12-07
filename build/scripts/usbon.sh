#!/bin/bash
# $1 = sd|nand|root
# defaults to sd (compatible with previous versions)
modprobe net2272
if [ $1 = "nand" ]; then modprobe g_file_storage file=/dev/loop/7
elif [ $1 = "root" ]; then modprobe g_file_storage file=/dev/mtdblock/3
else modprobe g_file_storage file=/dev/mmcsd/disc0/disc
fi
