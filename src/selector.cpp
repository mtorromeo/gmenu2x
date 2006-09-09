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
#include "selector.h"

using namespace std;

Selector::Selector(GMenu2X *gmenu2x, string text, string dir, string screendir, string filter) {
	this->gmenu2x = gmenu2x;
	this->text = text;
	if (dir[dir.length()-1]!='/') dir += "/";
	this->dir = dir;
	if (screendir[screendir.length()-1]!='/') screendir += "/";
	this->screendir = screendir;
	split(this->filter,filter,",");
	selRow = 0;
}

bool Selector::exec() {
	bool close = false, result = true;

	vector<string> files, screens;
	browsePath(dir,&files);

	Surface bg("imgs/bg.png");
	gmenu2x->drawTopBar(&bg,15);
	bg.write(gmenu2x->font,"Selector: "+text,160,8, SFontHAlignCenter, SFontVAlignMiddle);
	gmenu2x->drawBottomBar(&bg);

	gmenu2x->drawButton(&bg, "B", "Select file",
	gmenu2x->drawButton(&bg, "A", "Cancel", 10));

	Uint32 selTick = SDL_GetTicks(), curTick;
	uint i, selected = 0, firstElement = 0, iY;
	screens.resize(files.size());

	for (i=0; i<files.size(); i++) {
		string noext = files[i];
		string::size_type pos = noext.rfind(".");
		if (pos!=string::npos && pos>0)
			noext = noext.substr(0, pos);
		cout << "GMENU2X: Searching for screen " << screendir << noext << ".png" << endl;
		if (fileExists(screendir+noext+".png"))
			screens[i] = screendir+noext+".png";
		else if (fileExists(screendir+noext+".jpg"))
			screens[i] = screendir+noext+".jpg";
		else
			screens[i] = "";
	}
	
	while (!close) {
		bg.blit(gmenu2x->s,0,0);

		if (selected>firstElement+10) firstElement=selected-10;
		if (selected<firstElement) firstElement=selected;

		//Selection
		iY = selected-firstElement;
		iY = 20+(iY*18);
		gmenu2x->s->box(2, iY, 308, 16, gmenu2x->selectionColor);

		//Files
		for (i=firstElement; i<files.size() && i<firstElement+11; i++) {
			iY = i-firstElement;
			gmenu2x->sc["imgs/file.png"]->blit(gmenu2x->s, 5, 21+(iY*18));
			gmenu2x->s->write(gmenu2x->font, files[i], 24, 29+(iY*18), SFontHAlignLeft, SFontVAlignMiddle);
		}
		
		if (screens[selected]!="") {
			curTick = SDL_GetTicks();
			if (curTick-selTick>500)
				gmenu2x->sc[screens[selected]]->blitRight(gmenu2x->s, 310, 21, 160, 160);
		}

		gmenu2x->drawScrollBar(11,files.size(),firstElement,20,196);
		gmenu2x->s->flip();


#ifdef TARGET_GP2X
		gmenu2x->joy.update();
		if ( gmenu2x->joy[GP2X_BUTTON_A     ] ) { close = true; result = false; }
		if ( gmenu2x->joy[GP2X_BUTTON_UP    ] ) {
			if ((int)(selected-1)<0) {
				selected = files.size()-1;
			} else {
				selected -= 1;
			}
			selTick = SDL_GetTicks();
		}
		if ( gmenu2x->joy[GP2X_BUTTON_DOWN  ] ) {
			if (selected+1>=files.size()) {
				selected = 0;
			} else {
				selected += 1;
			}
			selTick = SDL_GetTicks();
		}
		if ( gmenu2x->joy[GP2X_BUTTON_B] || gmenu2x->joy[GP2X_BUTTON_CLICK] ) {
			file = dir+files[selected];
			close = true;
		}
#else
		while (SDL_PollEvent(&gmenu2x->event)) {
			if ( gmenu2x->event.type == SDL_QUIT ) { close = true; result = false; }
			if ( gmenu2x->event.type==SDL_KEYDOWN ) {
				if ( gmenu2x->event.key.keysym.sym==SDLK_ESCAPE ) { close = true; result = false; }
				if ( gmenu2x->event.key.keysym.sym==SDLK_UP ) {
					if ((int)(selected-1)<0) {
						selected = files.size()-1;
					} else {
						selected -= 1;
					}
					selTick = SDL_GetTicks();
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_DOWN ) {
					if (selected+1>=files.size()) {
						selected = 0;
					} else {
						selected += 1;
					}
					selTick = SDL_GetTicks();
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_RETURN ) {
					file = dir+files[selected];
					close = true;
				}
			}
		}
#endif
	}
	
	for (i=0; i<screens.size(); i++) {
		if (screens[i] != "")
			gmenu2x->sc.del(screens[i]);
	}

	return result;
}

void Selector::browsePath(string path, vector<string>* files) {
	DIR *dirp;
	struct stat st;
	struct dirent *dptr;
	string filepath;
	files->clear();

	if ((dirp = opendir(path.c_str())) == NULL) return;

	while ((dptr = readdir(dirp))) {
		if (dptr->d_name[0]=='.') continue;
		filepath = path+dptr->d_name;
		int statRet = stat(filepath.c_str(), &st);
		if (statRet == -1) continue;
		if (S_ISDIR(st.st_mode)) continue;
		
		bool filterOk = false;
		string file = dptr->d_name;
		for (uint i = 0; i<filter.size() && !filterOk; i++)
			filterOk = file.substr(file.length()-filter[i].length(),filter[i].length())==filter[i];
		if (filterOk) files->push_back(file);
	}

	closedir(dirp);
	sort(files->begin(),files->end());
}
