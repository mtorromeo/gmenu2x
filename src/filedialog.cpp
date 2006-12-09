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

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

//for browsing the filesystem
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#ifdef TARGET_GP2X
#include "gp2x.h"
#endif
#include "filedialog.h"
#include "filelister.h"

using namespace std;

FileDialog::FileDialog(GMenu2X *gmenu2x, string text, string filter) {
	this->gmenu2x = gmenu2x;
	this->text = text;
	this->filter = filter;
	selRow = 0;
}

bool FileDialog::exec() {
	bool close = false, result = true;
	path = "/mnt";

	FileLister fl(path);
	fl.setFilter(filter);
	fl.browse();

	Surface bg("imgs/bg.png");
	gmenu2x->drawTopBar(&bg,15);
	bg.write(gmenu2x->font,"File Browser: "+text,160,8, SFontHAlignCenter, SFontVAlignMiddle);
	gmenu2x->drawBottomBar(&bg);

	gmenu2x->drawButton(&bg, "B", "Enter folder/Confirm",
	gmenu2x->drawButton(&bg, "X", "Up one folder", 10));


	uint i, selected = 0, firstElement = 0, iY;

	while (!close) {
		bg.blit(gmenu2x->s,0,0);

		if (selected>firstElement+10) firstElement=selected-10;
		if (selected<firstElement) firstElement=selected;

		//Selection
		iY = selected-firstElement;
		iY = 20+(iY*18);
		gmenu2x->s->box(2, iY, 308, 16, gmenu2x->selectionColor);

		//Files & Directories
		gmenu2x->s->setClipRect(0,16,311,204);
		for (i=firstElement; i<fl.size() && i<firstElement+11; i++) {
			iY = i-firstElement;
			if (fl.isDirectory(i))
				gmenu2x->sc["imgs/folder.png"]->blit(gmenu2x->s, 5, 21+(iY*18));
			else
				gmenu2x->sc["imgs/file.png"]->blit(gmenu2x->s, 5, 21+(iY*18));
			gmenu2x->s->write(gmenu2x->font, fl[i], 24, 29+(iY*18), SFontHAlignLeft, SFontVAlignMiddle);
		}
		gmenu2x->s->clearClipRect();

		gmenu2x->drawScrollBar(11,fl.size(),firstElement,20,196);
		gmenu2x->s->flip();


#ifdef TARGET_GP2X
		gmenu2x->joy.update();
		if ( gmenu2x->joy[GP2X_BUTTON_SELECT] ) { close = true; result = false; }
		if ( gmenu2x->joy[GP2X_BUTTON_UP    ] ) {
			if (selected==0)
				selected = fl.size()-1;
			else
				selected -= 1;
		}
		if ( gmenu2x->joy[GP2X_BUTTON_L     ] ) {
			if ((int)(selected-10)<0) {
				selected = 0;
			} else {
				selected -= 8;
			}
		}
		if ( gmenu2x->joy[GP2X_BUTTON_DOWN  ] ) {
			if (selected+1>=fl.size())
				selected = 0;
			else
				selected += 1;
		}
		if ( gmenu2x->joy[GP2X_BUTTON_R     ] ) {
			if (selected+10>=fl.size()) {
				selected = fl.size()-1;
			} else {
				selected += 10;
			}
		}
		if ( gmenu2x->joy[GP2X_BUTTON_X] || gmenu2x->joy[GP2X_BUTTON_LEFT] ) {
			string::size_type p = path.rfind("/");
			if (p==string::npos || path.substr(0,4)!="/mnt" || p<4)
				return false;
			else
				path = path.substr(0,p);
			selected = 0;
			fl.setPath(path);
		}
		if ( gmenu2x->joy[GP2X_BUTTON_B] || gmenu2x->joy[GP2X_BUTTON_CLICK] ) {
			if (fl.isDirectory(selected)) {
				path += "/"+fl[selected];
				selected = 0;
				fl.setPath(path);
			} else {
				if (fl.isFile(selected)) {
					file = fl[selected];
					close = true;
				}
			}
		}
#else
		while (SDL_PollEvent(&gmenu2x->event)) {
			if ( gmenu2x->event.type == SDL_QUIT ) { close = true; result = false; }
			if ( gmenu2x->event.type==SDL_KEYDOWN ) {
				if ( gmenu2x->event.key.keysym.sym==SDLK_ESCAPE ) { close = true; result = false; }
				if ( gmenu2x->event.key.keysym.sym==SDLK_UP ) {
					if (selected==0) {
						selected = fl.size()-1;
					} else
						selected -= 1;
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_DOWN ) {
					if (selected+1>=fl.size())
						selected = 0;
					else
						selected += 1;
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_BACKSPACE ) {
					string::size_type p = path.rfind("/");
					if (p==string::npos || path.substr(0,4)!="/mnt" || p<4)
						return false;
					else
						path = path.substr(0,p);
					selected = 0;
					fl.setPath(path);
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_RETURN ) {
					if (fl.isDirectory(selected)) {
						path += "/"+fl[selected];
						selected = 0;
						fl.setPath(path);
					} else {
						if (fl.isFile(selected)) {
							file = fl[selected];
							close = true;
						}
					}
				}
			}
		}
#endif
	}

	return result;
}
