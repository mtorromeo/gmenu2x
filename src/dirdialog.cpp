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
#include "dirdialog.h"
#include "filelister.h"

using namespace std;

DirDialog::DirDialog(GMenu2X *gmenu2x, string text, string dir) {
	this->gmenu2x = gmenu2x;
	this->text = text;
	selRow = 0;
	if (dir.empty())
		path = "/mnt";
	else
		path = dir;
}

bool DirDialog::exec() {
	bool close = false, result = true;
	if (!fileExists(path))
		path = "/mnt";

	FileLister fl(path,true,false);
	fl.browse();

	uint i, selected = 0, firstElement = 0, iY;
	while (!close) {
		gmenu2x->sc["imgs/bg.png"]->blit(gmenu2x->s,0,0);
		gmenu2x->drawTitleIcon("icons/explorer.png",true);
		gmenu2x->writeTitle("Directory Browser");
		gmenu2x->writeSubTitle(text);

		gmenu2x->drawButton(gmenu2x->s, "start", gmenu2x->tr["Confirm"],
		gmenu2x->drawButton(gmenu2x->s, "x", gmenu2x->tr["Up one folder"],
		gmenu2x->drawButton(gmenu2x->s, "b", gmenu2x->tr["Enter folder"], 5)));

		if (selected>firstElement+9) firstElement=selected-9;
		if (selected<firstElement) firstElement=selected;

		//Selection
		iY = selected-firstElement;
		iY = 44+(iY*17);
		gmenu2x->s->box(2, iY, 308, 16, gmenu2x->selectionColor);

		//Directories
		gmenu2x->s->setClipRect(0,41,311,179);
		for (i=firstElement; i<fl.size() && i<firstElement+10; i++) {
			iY = i-firstElement;
			gmenu2x->sc.skinRes("imgs/folder.png")->blit(gmenu2x->s, 5, 45+(iY*17));
			gmenu2x->s->write(gmenu2x->font, fl[i], 24, 52+(iY*17), SFontHAlignLeft, SFontVAlignMiddle);
		}
		gmenu2x->s->clearClipRect();

		gmenu2x->drawScrollBar(10,fl.size(),firstElement,44,170);
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
			if ((int)(selected-9)<0) {
				selected = 0;
			} else {
				selected -= 9;
			}
		}
		if ( gmenu2x->joy[GP2X_BUTTON_DOWN  ] ) {
			if (selected+1>=fl.size())
				selected = 0;
			else
				selected += 1;
		}
		if ( gmenu2x->joy[GP2X_BUTTON_R     ] ) {
			if (selected+9>=fl.size()) {
				selected = fl.size()-1;
			} else {
				selected += 9;
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
		if ( (gmenu2x->joy[GP2X_BUTTON_B] || gmenu2x->joy[GP2X_BUTTON_CLICK]) && selected<fl.size() ) {
			path += "/"+fl[selected];
			selected = 0;
			fl.setPath(path);
		}
		if ( gmenu2x->joy[GP2X_BUTTON_START] ) close = true;
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
				if ( gmenu2x->event.key.keysym.sym==SDLK_RETURN && selected<fl.size()) {
					path += "/"+fl[selected];
					selected = 0;
					fl.setPath(path);
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_s ) close = true;
			}
		}
#endif
	}

	return result;
}
