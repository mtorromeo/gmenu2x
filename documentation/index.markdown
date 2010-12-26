---
layout: default
title: Documentation
---

## Installation
The simpliest way of installing GMenu2X is to copy **autorun.gpu** and the folder **gmenu2x** to the root of your sd card, but you can also install it to a different location.

If you want to install the program to a different location you have to edit the file **autorun.gpu**.

For example if you want to install it to the nand (useful if you have multiple sd cards) you have to edit the file like this:

#### autorun.gpu

	#!/bin/sh
	cd /mnt/nand/gmenu2x
	exec ./gmenu2x

## Controls
{% include controls.markdown %}

## Configuration
Before you can use gmenu2x you have to create the links to the applications and the games you want to appear  in the menu.

From version 0.3 you can create links directly from gmenu2x.
To do that, bring up the option menu by pressing **SELECT** and choose **Add link in '...' **, then browse to the game/application directory and select an application. The link will be added to the selected section.

### Sections
You can create any number of sections just by creating a new directory under **sections/** and adding the corresponding icon with the same name as the directory plus the '.png' extension.

For example if you want to create the "emulators" section, you have to create the directory ** sections/emulators** and place the icon as **sections/emulators.png**.

There are 4 pre-configured sections: *applications*, *emulators*, *games* and *settings*.

From version 0.6 sections are also creatable from gmenu2x.

### Links
Links are located in the corrisponding section directory (IE: sections/games).

The links are plain-text files containing the informations needed by GMenu2X to display and launch the games.
A sample link looks like this:

	title=SNES
	description=SquidgeSnes: Super Nintendo Emulator
	icon=icons/snes.png
	clock=266
	exec=/mnt/sd/snes/squidgesnes.gpe

The syntax is made of a number of keys and values lines. Keys are case-sensitive so **title** is not the same as **Title**.

Here is a list of keys.

#### title
This is the title of the application/game, it's value is only used for display purposes.

#### description
*Optional*<br />
A short description of the application/game.

#### icon
*Optional*<br />
The path to the icon for the application/game. If not specified a default icon will be used or the png file with the same name as the exec param if the file exists.<br />
The icon size should be 32x32px.

#### clock
*Optional*<br />
Sets the default clock speed for the link (can be modified at run-time)

#### volume
*Optional*<br />
Sets the volume for the link (can be modified at run-time).

#### exec
The path to the application to launch. If the file doesn't exist the link will be disabled, so that you can create links for applications that are not installed or that are on different sd cards, and GMenu2X will only show the valid ones.<br />
The path can be relative instead of absolute and GMenu2X will check for the existence of the file based on the **workdir** directive or on the current path (usually /mnt/sd/gmenu2x).

#### workdir
*Optional*<br />
If specified Gmenu2X will chdir to this path before the launch of the link. If not specified GMenu2X will chdir to the path of the exec key (IE: /mnt/sd/drmd if exec=/mnt/sd/drmd/drmd.gpe).

#### params
*Optional*<br />
Optional parameters to pass to the application/game to launch.

There are some magic string which will be replaced before the launch of the link:
* [selPath]: this string will be replaced by the selector path.
* [selFile]: this string will be replaced by the selected file's name, in the selector, without its extension.
* [selExt]: this string will be replaced by the selected file's extension.
* [selFullPath]: this is a shortcut value that means [selPath][selFile][selExt]

#### wrapper
*Values: true, false*<br />
*Optional, default:false*<br />
If true GMenu2X will launch the link around a script that will relaunch GMenu2X after program termination.

#### dontleave
*Values: true, false*<br />
*Optional, default:false*<br />
If true GMenu2X will not terminate when launching the link. Useful for launching programs in background.

#### selectordir
*Optional*<br />
If a valid directory is specified, then gmenu2x will show a list of files to launch with the link when it is selected.

#### selectorbrowser
*Values: true, false*<br />
*Optional, default:false*<br />
If true the selector will allow to change the folder.

#### selectorfilter
*Optional*<br />
If this directory is specified, then only files matching this filter are shown on the selector screen.

You can specify multiple filters separating them with a comma (,).

A typical filter could be ".zip,.smc"

#### selectorscreens
*Optional*<br />
If this directory is specified, gmenu2x will search here for a file with the same name as the file selected in the selector but with the png extension and it will display it as a screenshot.

Screenshots should be of a maximum size of 160x160px.

#### aliasfile
*Optional*<br />
A file that contains a list of aliases for the files in the selector. Useful for those emulators that have roms with fixed file names like MAME, CPS2 and NeoGeo.

The alias file must contain a list of aliases like this:
	pacland=Pac Land

### The selector
The selector is useful to launch a link with a file that can be selected from a list.

The link's property that activates the selector for the link is **selectordir**.

The selector displays a list of files matching a given filter and showing a corresponding screenshot if present.

If the **params** property is empty it will be substituted by the selected filename, otherwise you will need to use some magic string that will be replaced with the selected file's informations. (See the **params** property documentation for details on the supported magic strings)

The corresponding **params** property if not specified is "[selPath][selFile][selExt]" (note that quotes are included).

#### Example params line
* MAME: [selFile]
* SquidgeSnes (with wrapper=ON): nrtm load=[selFullPath]

### Customising the interface
You can customise the appearance of GMenu2X by changing wallpapers and fonts and other gui elements.
They are located in **imgs/** and **icons/**.

GMenu2X uses a custom version of [SFont](http://www.linux-games.com/sfont/) (Included in the source package). You can use [sfontmake](http://www.nostatic.org/sfont/) or [SFont FontbuilderGUI (Win)](http://sfont.nein-andy.de/) to create fonts for GMenu2X.

Since version 0.9 GMenu2X extended the characters supported by adding utf8, so the official sfontmake utility is no longer compatible wih GMenu2X.
GMenu2X uses a modified version of sfontmake which supports those characters. This utility has not been released yet, but send me an email if you need it.
