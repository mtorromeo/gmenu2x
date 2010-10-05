---
layout: default
title: Compiling
---

To retrieve GMenu2X' sources you need the [git version control system installed](http://help.github.com/linux-git-installation/) on your pc.

You can then clone the repository with the following command:

{% highlight bash %}
git clone git://github.com/mtorromeo/gmenu2x.git
{% endhighlight %}

The *src* dir contains various Makefiles for the different supported targets.
To compile GMenu2X for a x86/x86_64 linux system, issue the following command:

{% highlight bash %}
cd src/
make -f Makefile.linux
{% endhighlight %}