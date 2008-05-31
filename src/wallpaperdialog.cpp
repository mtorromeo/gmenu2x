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

#ifdef TARGET_GP2X
#include "gp2x.h"
#endif
#include "wallpaperdialog.h"
#include "filelister.h"

using namespace std;

WallpaperDialog::WallpaperDialog(GMenu2X *gmenu2x) {
	this->gmenu2x = gmenu2x;
	selRow = 0;
}

bool WallpaperDialog::exec() {
	bool close = false, result = true;

	FileLister fl("skins/"+gmenu2x->skin+"/wallpapers");
	fl.setFilter(".png,.jpg,.jpeg,.bmp");
	vector<string> wallpapers;
	if (fileExists("skins/"+gmenu2x->skin+"/wallpapers")) {
		fl.browse();
		wallpapers = fl.files;
	}
	if (gmenu2x->skin != "Default") {
		fl.setPath("skins/Default/wallpapers",true);
		for (uint i=0; i<fl.files.size(); i++)
			wallpapers.push_back(fl.files[i]);
	}
#ifdef DEBUG
	cout << "Wallpapers: " << wallpapers.size() << endl;
#endif

	uint i, selected = 0, firstElement = 0, iY;
	while (!close) {
		if (selected>firstElement+9) firstElement=selected-9;
		if (selected<firstElement) firstElement=selected;

		//Wallpaper
		if (selected<wallpapers.size()-fl.files.size())
			gmenu2x->sc["skins/"+gmenu2x->skin+"/wallpapers/"+wallpapers[selected]]->blit(gmenu2x->s,0,0);
		else
			gmenu2x->sc["skins/Default/wallpapers/"+wallpapers[selected]]->blit(gmenu2x->s,0,0);

		gmenu2x->drawTopBar(gmenu2x->s);
		gmenu2x->drawBottomBar(gmenu2x->s);

		gmenu2x->drawTitleIcon("icons/wallpaper.png",true);
		gmenu2x->writeTitle("Wallpaper selection");
		gmenu2x->writeSubTitle("Select an image from the list, to use as a wallpaper");

		gmenu2x->drawButton(gmenu2x->s, "b", gmenu2x->tr["Select wallpaper"],5);

		//Selection
		iY = selected-firstElement;
		iY = 44+(iY*17);
		gmenu2x->s->box(2, iY, 308, 16, gmenu2x->selectionColor);

		//Files & Directories
		gmenu2x->s->setClipRect(0,41,311,179);
		for (i=firstElement; i<wallpapers.size() && i<firstElement+10; i++) {
			iY = i-firstElement;
			gmenu2x->s->write(gmenu2x->font, wallpapers[i], 5, 52+(iY*17), SFontHAlignLeft, SFontVAlignMiddle);
		}
		gmenu2x->s->clearClipRect();

		gmenu2x->drawScrollBar(10,wallpapers.size(),firstElement,44,170);
		gmenu2x->s->flip();


#ifdef TARGET_GP2X
		gmenu2x->joy.update();
		if ( gmenu2x->joy[GP2X_BUTTON_SELECT] ) { close = true; result = false; }
		if ( gmenu2x->joy[GP2X_BUTTON_UP    ] ) {
			if (selected==0)
				selected = wallpapers.size()-1;
			else
				selected -= 1;
		}
		if ( gmenu2x->joy[GP2X_BUTTON_L     ] ) {
			if ((int)(selected-9)<0) {
				selected = 0;
			} else {
				selected -= 9;
			}
		}
		if ( gmenu2x->joy[GP2X_BUTTON_DOWN  ] ) {
			if (selected+1>=wallpapers.size())
				selected = 0;
			else
				selected += 1;
		}
		if ( gmenu2x->joy[GP2X_BUTTON_R     ] ) {
			if (selected+9>=wallpapers.size()) {
				selected = wallpapers.size()-1;
			} else {
				selected += 9;
			}
		}
		if ( gmenu2x->joy[GP2X_BUTTON_X] ) {
			close = true;
			result = false;
		}
		if ( gmenu2x->joy[GP2X_BUTTON_B] || gmenu2x->joy[GP2X_BUTTON_CLICK] ) {
			close = true;
			if (wallpapers.size()>0) {
				if (selected<wallpapers.size()-fl.files.size())
					wallpaper = "skins/"+gmenu2x->skin+"/wallpapers/"+wallpapers[selected];
				else
					wallpaper = "skins/Default/wallpapers/"+wallpapers[selected];
			} else result = false;
		}
#else
		while (SDL_PollEvent(&gmenu2x->event)) {
			if ( gmenu2x->event.type == SDL_QUIT ) { close = true; result = false; }
			if ( gmenu2x->event.type==SDL_KEYDOWN ) {
				if ( gmenu2x->event.key.keysym.sym==SDLK_ESCAPE ) { close = true; result = false; }
				if ( gmenu2x->event.key.keysym.sym==SDLK_UP ) {
					if (selected==0) {
						selected = wallpapers.size()-1;
					} else
						selected -= 1;
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_DOWN ) {
					if (selected+1>=wallpapers.size())
						selected = 0;
					else
						selected += 1;
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_BACKSPACE ) {
					close = true;
					result = false;
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_RETURN ) {
					close = true;
					if (wallpapers.size()>0) {
						if (selected<wallpapers.size()-fl.files.size())
							wallpaper = "skins/"+gmenu2x->skin+"/wallpapers/"+wallpapers[selected];
						else
							wallpaper = "skins/Default/wallpapers/"+wallpapers[selected];
					} else result = false;
				}
			}
		}
#endif
	}

	for (uint i=0; i<wallpapers.size(); i++)
		if (i<wallpapers.size()-fl.files.size())
			gmenu2x->sc.del("skins/"+gmenu2x->skin+"/wallpapers/"+wallpapers[i]);
		else
			gmenu2x->sc.del("skins/Default/wallpapers/"+wallpapers[i]);

	return result;
}
