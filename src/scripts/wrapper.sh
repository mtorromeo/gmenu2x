#!/bin/sh
echo Wrapping...
$*
cd /mnt/sd/unimenu2x
exec ./unimenu2x
