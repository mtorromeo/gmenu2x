#!/bin/bash
# $1 = ip
# $2 = inet (on/off)
# $3 = samba (on/off)
# $4 = web (on/off)
insmod net2272
insmod g_ether
ifconfig usb0 $1 netmask 255.255.255.0 up
# route add default gw $defaultgw
if [ $2 = "on" ]; then /etc/init.d/inet start; fi
if [ $3 = "on" ]; then smbd; fi
if [ $4 = "on" ]; then thttpd; fi
