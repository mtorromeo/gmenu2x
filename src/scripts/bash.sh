#!/bin/sh
export HOME=/mnt/sd
LOG=${HOME}/log.txt
rm -f ${LOG}
sync

function log()
{
	echo -e "# $*" >> ${LOG}
	( $* 2>&1 ) | sed -e 's/^/| /' >> ${LOG}
	echo >> ${LOG}
}

log insmod /lib/modules/2.4.25/kernel/drivers/usb/gadget/net2272.o
log insmod ${HOME}/g_serial.o use_acm=1
log lsmod

log mknod /dev/ttygs0 c 127 0

sync
sleep 3
bash --login -i -s < /dev/ttygs0 > /dev/ttygs0 2>&1

log rmmod /lib/modules/2.4.25/kernel/drivers/usb/gadget/net2272.o
log rmmod ${HOME}/g_serial.o
log lsmod
