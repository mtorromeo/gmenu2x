/***************************************************************************
 *   Copyright (C) 2006 by Massimiliano Torromeo   *
 *   massimiliano.torromeo@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <iostream>

#include "wallpaperdialog.h"
#include "filelister.h"
#include "debug.h"

using namespace std;

WallpaperDialog::WallpaperDialog(GMenu2X *gmenu2x)
	: Dialog(gmenu2x) {}

bool WallpaperDialog::exec()
{
	bool close = false, result = true;

	FileLister fl("skins/"+gmenu2x->confStr["skin"]+"/wallpapers");
	fl.setFilter(".png,.jpg,.jpeg,.bmp");
	vector<string> wallpapers;
	if (fileExists("skins/"+gmenu2x->confStr["skin"]+"/wallpapers")) {
		fl.browse();
		wallpapers = fl.getFiles();
	}
	if (gmenu2x->confStr["skin"] != "Default") {
		fl.setPath("skins/Default/wallpapers",true);
		for (uint i=0; i<fl.getFiles().size(); i++)
			wallpapers.push_back(fl.getFiles()[i]);
	}

	DEBUG("Wallpapers: %i", wallpapers.size());

	uint i, selected = 0, firstElement = 0, iY;
	while (!close) {
		if (selected>firstElement+9) firstElement=selected-9;
		if (selected<firstElement) firstElement=selected;

		//Wallpaper
		if (selected<wallpapers.size()-fl.getFiles().size())
			gmenu2x->sc["skins/"+gmenu2x->confStr["skin"]+"/wallpapers/"+wallpapers[selected]]->blit(gmenu2x->s,0,0);
		else
			gmenu2x->sc["skins/Default/wallpapers/"+wallpapers[selected]]->blit(gmenu2x->s,0,0);

		gmenu2x->drawTopBar(gmenu2x->s);
		gmenu2x->drawBottomBar(gmenu2x->s);

		drawTitleIcon("icons/wallpaper.png",true);
		writeTitle("Wallpaper selection");
		writeSubTitle("Select an image from the list, to use as a wallpaper");

		gmenu2x->drawButton(gmenu2x->s, "b", gmenu2x->tr["Select wallpaper"],5);

		//Selection
		iY = selected-firstElement;
		iY = 44+(iY*17);
		gmenu2x->s->box(2, iY, 308, 16,	gmenu2x->skinConfColors[COLOR_SELECTION_BG]);

		//Files & Directories
		gmenu2x->s->setClipRect(0,41,311,179);
		for (i=firstElement; i<wallpapers.size() && i<firstElement+10; i++) {
			iY = i-firstElement;
			gmenu2x->s->write(gmenu2x->font, wallpapers[i], 5, 52+(iY*17), HAlignLeft, VAlignMiddle);
		}
		gmenu2x->s->clearClipRect();

		gmenu2x->drawScrollBar(10,wallpapers.size(),firstElement,44,170);
		gmenu2x->s->flip();


		gmenu2x->input.update();
		if ( gmenu2x->input[SETTINGS] ) { close = true; result = false; }
		if ( gmenu2x->input[UP] ) {
			if (selected==0)
				selected = wallpapers.size()-1;
			else
				selected -= 1;
		}
		if ( gmenu2x->input[PAGEUP] ) {
			if ((int)(selected-9)<0) {
				selected = 0;
			} else {
				selected -= 9;
			}
		}
		if ( gmenu2x->input[DOWN] ) {
			if (selected+1>=wallpapers.size())
				selected = 0;
			else
				selected += 1;
		}
		if ( gmenu2x->input[PAGEDOWN] ) {
			if (selected+9>=wallpapers.size()) {
				selected = wallpapers.size()-1;
			} else {
				selected += 9;
			}
		}
		if ( gmenu2x->input[CANCEL] ) {
			close = true;
			result = false;
		}
		if ( gmenu2x->input[CONFIRM] ) {
			close = true;
			if (wallpapers.size()>0) {
				if (selected<wallpapers.size()-fl.getFiles().size())
					wallpaper = "skins/"+gmenu2x->confStr["skin"]+"/wallpapers/"+wallpapers[selected];
				else
					wallpaper = "skins/Default/wallpapers/"+wallpapers[selected];
			} else result = false;
		}
	}

	for (uint i=0; i<wallpapers.size(); i++)
		if (i<wallpapers.size()-fl.getFiles().size())
			gmenu2x->sc.del("skins/"+gmenu2x->confStr["skin"]+"/wallpapers/"+wallpapers[i]);
		else
			gmenu2x->sc.del("skins/Default/wallpapers/"+wallpapers[i]);

	return result;
}
