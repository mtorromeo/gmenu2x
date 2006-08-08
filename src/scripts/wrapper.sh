#!/bin/sh
echo Wrapping...
$*
cd /mnt/sd/gmenu2x
exec ./gmenu2x
