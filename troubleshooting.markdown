---
layout: default
title: Troubleshooting
---

## I put GMenu2X on the NAND and my gp2x does not boot anymore

For GMenu2X to work on the nand you have to edit the autorun.gpu script (with an editor supporting unix line-endings) and change the line

{% highlight bash %}
cd /mnt/sd/gmenu2x
{% endhighlight %}

to

{% highlight bash %}
cd /mnt/nand/gmenu2x
{% endhighlight %}

To let the gp2x boot to the standard menu, so that you can mount the nand on your pc, keep pressed **SELECT**+**START** during the boot process.

## GMenu2X output is being logged after link's output

This may happen when the application being logged automatically relaunches the menu on exit. This is bad design for various reasons, and developers should use a script to do this, instead of coding it in the application.

If the application you are using, comes with a script with extension .gpe and an executable with no extension, be sure to link against the executable itself, instead of the script.

If this is not the case, notify the author of the application of this issue and kindly ask if he/she could solve it.

## Sometimes startup is slower, sometimes faster

This may be related to GMenu2X output being logged. High quantity of output may slowdown the gp2x and the SDL initialization output is high enough to trigger this case.