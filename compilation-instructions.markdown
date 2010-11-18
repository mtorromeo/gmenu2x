---
layout: default
title: Compilation Instructions
---

## Requirements

GMenu2X is written in C++ and requires the following libraries to be present:

* SDL
* SDL_image
* SDL_ttf >= 2.0.10
* SDL_gfx
* libpng
* libjpeg
* freetype >= 2.4.0
* [Open2x toolchain](http://wiki.open2x.org/open2x/wiki/index.php?title=Toolchain) (recommended)

## Instructions

To retrieve GMenu2X' sources you need the [git version control system installed](http://help.github.com/linux-git-installation/) on your pc.

You can then clone the repository with the following command:

{% highlight bash %}
git clone git://github.com/mtorromeo/gmenu2x.git
{% endhighlight %}

The project directory contains various Makefiles for the different supported targets.
To compile GMenu2X for a x86/x86_64 linux system, issue the following command:

{% highlight bash %}
make -f Makefile.linux
{% endhighlight %}

The main Makefile targets the GP2X device and supports both static and shared libraries compilation (default).
The OPEN2X global variable needs to be exported and point to the toolchain directory (e.g. /opt/open2x/gcc-4.1.1-glibc-2.3.6)
To build a static binary:

{% highlight bash %}
make static
{% endhighlight %}