#!/bin/sh
LOG=/mnt/nand/log.txt
rm -f ${LOG}
sync

function log()
{
	echo -e "# $*" >> ${LOG}
	( $* 2>&1 ) | sed -e 's/^/| /' >> ${LOG}
	echo >> ${LOG}
}

log insmod /lib/modules/2.4.25/kernel/drivers/usb/gadget/net2272.o
log insmod /lib/modules/2.4.25/kernel/drivers/usb/gadget/g_ether.o
log lsmod
log /etc/init.d/inet start
