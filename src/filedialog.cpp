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

#include "filedialog.h"

using namespace std;

FileDialog::FileDialog(GMenu2X *gmenu2x, string text, string filter, string file) {
	this->gmenu2x = gmenu2x;
	this->text = text;
	this->filter = filter;
	this->file = "";
	setPath("/mnt");
	title = "File Browser";
	if (!file.empty()) {
		string::size_type pos = file.rfind("/");
		if (pos != string::npos) {
			setPath( file.substr(0, pos) );
			this->file = file.substr(pos+1,file.length());
		}
	}
	selRow = 0;
}

bool FileDialog::exec() {
	bool close = false, result = true, ts_pressed = false;
	if (!fileExists(path()))
		setPath("/mnt");

	fl.setFilter(filter);
	fl.browse();

	uint i, firstElement = 0, iY, action;
	selected = 0;
	while (!close) {
		action = FD_NO_ACTION;
		if (gmenu2x->f200) gmenu2x->ts.poll();

		gmenu2x->bg->blit(gmenu2x->s,0,0);
		gmenu2x->drawTitleIcon("icons/explorer.png",true);
		gmenu2x->writeTitle(title);
		gmenu2x->writeSubTitle(text);

		gmenu2x->drawButton(gmenu2x->s, "x", gmenu2x->tr["Up one folder"],
		gmenu2x->drawButton(gmenu2x->s, "b", gmenu2x->tr["Enter folder/Confirm"], 5));

		if (selected>firstElement+9) firstElement=selected-9;
		if (selected<firstElement) firstElement=selected;

		//Selection
		iY = selected-firstElement;
		iY = 44+(iY*17);
		gmenu2x->s->box(2, iY, 308, 16, gmenu2x->skinConfColors["selectionBg"]);

		beforeFileList();

		//Files & Directories
		gmenu2x->s->setClipRect(0,41,311,179);
		if (ts_pressed && !gmenu2x->ts.pressed()) {
			action = FD_ACTION_SELECT;
			ts_pressed = false;
		}
		if (gmenu2x->f200 && gmenu2x->ts.pressed() && !gmenu2x->ts.inRect(2,44,308,179)) ts_pressed = false;
		for (i=firstElement; i<fl.size() && i<firstElement+10; i++) {
			iY = i-firstElement;
			if (fl.isDirectory(i)) {
				if (fl[i]=="..")
					gmenu2x->sc.skinRes("imgs/go-up.png")->blit(gmenu2x->s, 5, 45+(iY*17));
				else
					gmenu2x->sc.skinRes("imgs/folder.png")->blit(gmenu2x->s, 5, 45+(iY*17));
			} else {
				gmenu2x->sc.skinRes("imgs/file.png")->blit(gmenu2x->s, 5, 45+(iY*17));
			}
			gmenu2x->s->write(gmenu2x->font, fl[i], 24, 52+(iY*17), SFontHAlignLeft, SFontVAlignMiddle);
			if (gmenu2x->f200 && gmenu2x->ts.pressed() && gmenu2x->ts.inRect(2, 44+(iY*17), 308, 16)) {
				ts_pressed = true;
				selected = i;
			}
		}
		gmenu2x->s->clearClipRect();

		gmenu2x->drawScrollBar(10,fl.size(),firstElement,44,170);
		gmenu2x->s->flip();

		gmenu2x->input.update();
		if ( gmenu2x->input[ACTION_SELECT] ) action = FD_ACTION_CLOSE;
		if ( gmenu2x->input[ACTION_UP    ] ) action = FD_ACTION_UP;
		if ( gmenu2x->input[ACTION_L     ] ) action = FD_ACTION_SCROLLUP;
		if ( gmenu2x->input[ACTION_DOWN  ] ) action = FD_ACTION_DOWN;
		if ( gmenu2x->input[ACTION_R     ] ) action = FD_ACTION_SCROLLDOWN;
		if ( gmenu2x->input[ACTION_X] || gmenu2x->input[ACTION_LEFT] ) action = FD_ACTION_GOUP;
		if ( gmenu2x->input[ACTION_B     ] ) action = FD_ACTION_SELECT;

		if (action == FD_ACTION_SELECT && fl[selected]=="..") action = FD_ACTION_GOUP;
		switch (action) {
			case FD_ACTION_CLOSE: {
				close = true;
				result = false;
			} break;
			case FD_ACTION_UP: {
				if (selected==0)
					selected = fl.size()-1;
				else
					selected -= 1;
			} break;
			case FD_ACTION_SCROLLUP: {
				if ((int)(selected-9)<0) {
					selected = 0;
				} else {
					selected -= 9;
				}
			} break;
			case FD_ACTION_DOWN: {
				if (selected+1>=fl.size())
					selected = 0;
				else
					selected += 1;
			} break;
			case FD_ACTION_SCROLLDOWN: {
				if (selected+9>=fl.size()) {
					selected = fl.size()-1;
				} else {
					selected += 9;
				}
			} break;
			case FD_ACTION_GOUP: {
				string::size_type p = path().rfind("/");
				if (p==string::npos || path().substr(0,4)!="/mnt" || p<4)
					return false;
				else
					setPath( path().substr(0,p) );
			} break;
			case FD_ACTION_SELECT: {
				if (fl.isDirectory(selected)) {
					setPath( path()+"/"+fl[selected] );
				} else {
					if (fl.isFile(selected)) {
						file = fl[selected];
						close = true;
					}
				}
			} break;
		}
	}

	return result;
}

void FileDialog::setPath(string path) {
	path_v = path;
	fl.setPath(path);
	selected = 0;
	onChangeDir();
}

void FileDialog::beforeFileList() {}
void FileDialog::onChangeDir() {}
