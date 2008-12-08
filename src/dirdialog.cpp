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

#include "dirdialog.h"
#include "filelister.h"
#include "FastDelegate.h"

using namespace std;
using namespace fastdelegate;

DirDialog::DirDialog(GMenu2X *gmenu2x, string text, string dir) {
	this->gmenu2x = gmenu2x;
	this->text = text;
	selRow = 0;
	if (dir.empty())
		path = "/mnt";
	else
		path = dir;

	//Delegates
	ButtonAction actionUp = MakeDelegate(this, &DirDialog::up);
	ButtonAction actionEnter = MakeDelegate(this, &DirDialog::enter);
	ButtonAction actionConfirm = MakeDelegate(this, &DirDialog::confirm);
	
	btnUp = new IconButton(gmenu2x, "skin:imgs/buttons/x.png", gmenu2x->tr["Up one folder"]);
	btnUp->setAction(actionUp);

	btnEnter = new IconButton(gmenu2x, "skin:imgs/buttons/b.png", gmenu2x->tr["Enter folder"]);
	btnEnter->setAction(actionEnter);

	btnConfirm = new IconButton(gmenu2x, "skin:imgs/buttons/start.png", gmenu2x->tr["Confirm"]);
	btnConfirm->setAction(actionConfirm);
}

bool DirDialog::exec() {
	bool ts_pressed = false;
	uint i, firstElement = 0, iY, action;
	
	if (!fileExists(path))
		path = "/mnt";

	fl = new FileLister(path,true,false);
	fl->browse();

	selected = 0;
	close = false;
	result = true;
	
	uint rowHeight = gmenu2x->font->getHeight()+1; // gp2x=15+1 / pandora=19+1
	uint numRows = (gmenu2x->resY-gmenu2x->skinConfInt["topBarHeight"]-20)/rowHeight;
	SDL_Rect clipRect = {0, gmenu2x->skinConfInt["topBarHeight"]+1, gmenu2x->resX-9, gmenu2x->resY-gmenu2x->skinConfInt["topBarHeight"]-25};
	SDL_Rect touchRect = {2, gmenu2x->skinConfInt["topBarHeight"]+4, gmenu2x->resX-12, clipRect.h};
	while (!close) {
		action = DirDialog::ACT_NONE;
		if (gmenu2x->f200) gmenu2x->ts.poll();
		
		gmenu2x->bg->blit(gmenu2x->s,0,0);
		gmenu2x->drawTitleIcon("icons/explorer.png",true);
		gmenu2x->writeTitle("Directory Browser");
		gmenu2x->writeSubTitle(text);

		gmenu2x->drawButton(btnConfirm,
		gmenu2x->drawButton(btnUp,
		gmenu2x->drawButton(btnEnter, 5)));

		if (selected>firstElement+numRows-1) firstElement=selected-numRows+1;
		if (selected<firstElement) firstElement=selected;

		//Selection
		iY = selected-firstElement;
		iY = gmenu2x->skinConfInt["topBarHeight"]+1+(iY*rowHeight);
		gmenu2x->s->box(2, iY, gmenu2x->resX-12, rowHeight-1, gmenu2x->skinConfColors["selectionBg"]);

		//Directories
		gmenu2x->s->setClipRect(clipRect);
		if (ts_pressed && !gmenu2x->ts.pressed()) {
			action = DirDialog::ACT_SELECT;
			ts_pressed = false;
		}
		if (gmenu2x->f200 && gmenu2x->ts.pressed() && !gmenu2x->ts.inRect(touchRect)) ts_pressed = false;
		for (i=firstElement; i<fl->size() && i<firstElement+numRows; i++) {
			iY = i-firstElement;
			gmenu2x->sc.skinRes("imgs/folder.png")->blit(gmenu2x->s, 5, gmenu2x->skinConfInt["topBarHeight"]+1+(iY*rowHeight));
			gmenu2x->s->write(gmenu2x->font, fl->at(i), 24, gmenu2x->skinConfInt["topBarHeight"]+9+(iY*rowHeight), SFontHAlignLeft, SFontVAlignMiddle);
			if (gmenu2x->f200 && gmenu2x->ts.pressed() && gmenu2x->ts.inRect(touchRect.x, touchRect.y+(iY*rowHeight), touchRect.w, rowHeight)) {
				ts_pressed = true;
				selected = i;
			}
		}
		gmenu2x->s->clearClipRect();

		gmenu2x->drawScrollBar(numRows,fl->size(),firstElement,clipRect.y,clipRect.h);
		gmenu2x->s->flip();

		btnConfirm->handleTS();
		btnUp->handleTS();
		btnEnter->handleTS();
		gmenu2x->input.update();
		if ( gmenu2x->input[ACTION_SELECT] ) action = DirDialog::ACT_CLOSE;
		if ( gmenu2x->input[ACTION_UP    ] ) action = DirDialog::ACT_UP;
		if ( gmenu2x->input[ACTION_L     ] ) action = DirDialog::ACT_SCROLLUP;
		if ( gmenu2x->input[ACTION_DOWN  ] ) action = DirDialog::ACT_DOWN;
		if ( gmenu2x->input[ACTION_R     ] ) action = DirDialog::ACT_SCROLLDOWN;
		if ( gmenu2x->input[ACTION_X] || gmenu2x->input[ACTION_LEFT] ) action = DirDialog::ACT_GOUP;
		if ( gmenu2x->input[ACTION_B     ] ) action = DirDialog::ACT_SELECT;
		if ( gmenu2x->input[ACTION_START ] ) action = DirDialog::ACT_CONFIRM;

		if (action == DirDialog::ACT_SELECT && fl->at(selected)=="..") action = DirDialog::ACT_GOUP;
		switch (action) {
			case DirDialog::ACT_CLOSE: {
				close = true;
				result = false;
			} break;
			case DirDialog::ACT_UP: {
				if (selected==0)
					selected = fl->size()-1;
				else
					selected -= 1;
			} break;
			case DirDialog::ACT_SCROLLUP: {
				if ((int)(selected-(numRows-2))<0) {
					selected = 0;
				} else {
					selected -= numRows-2;
				}
			} break;
			case DirDialog::ACT_DOWN: {
				if (selected+1>=fl->size())
					selected = 0;
				else
					selected += 1;
			} break;
			case DirDialog::ACT_SCROLLDOWN: {
				if (selected+(numRows-2)>=fl->size()) {
					selected = fl->size()-1;
				} else {
					selected += numRows-2;
				}
			} break;
			case DirDialog::ACT_GOUP: {
				up();
			} break;
			case DirDialog::ACT_SELECT: {
				enter();
			} break;
			case DirDialog::ACT_CONFIRM: {
				confirm();
			} break;
		}
	}
	
	delete(fl);

	return result;
}

void DirDialog::up() {
	string::size_type p = path.rfind("/");
	if (p==string::npos || path.substr(0,4)!="/mnt" || p<4) {
		close = true;
		result = false;
	} else {
		path = path.substr(0,p);
		selected = 0;
		fl->setPath(path);
	}
}

void DirDialog::enter() {
	path += "/"+fl->at(selected);
	selected = 0;
	fl->setPath(path);
}

void DirDialog::confirm() {
	close = true;
}
