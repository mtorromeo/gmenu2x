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
#include "menu.h"
#include "linkapp.h"
#include "selector.h"
#include "filelister.h"

using namespace std;

Selector::Selector(GMenu2X *gmenu2x, LinkApp *link, string selectorDir) {
	this->gmenu2x = gmenu2x;
	this->link = link;
	loadAliases();
	selRow = 0;
	if (selectorDir=="")
		dir = link->getSelectorDir();
	else
		dir = selectorDir;
	if (dir[dir.length()-1]!='/') dir += "/";
}

int Selector::exec(int startSelection) {
	bool close = false, result = true;
	vector<string> screens, titles;

	FileLister fl(dir, link->getSelectorBrowser());
	fl.setFilter(link->getSelectorFilter());
	fl.browse();

	Surface bg(gmenu2x->sc["imgs/bg.png"]);
	gmenu2x->drawTitleIcon(link->getIcon(),true,&bg);
	gmenu2x->writeTitle(link->getTitle(),&bg);
	gmenu2x->writeSubTitle(link->getDescription(),&bg);

	if (link->getSelectorBrowser()) {
		gmenu2x->drawButton(&bg, "start", gmenu2x->tr["Exit"],
		gmenu2x->drawButton(&bg, "b", gmenu2x->tr["Select file"],
		gmenu2x->drawButton(&bg, "x", gmenu2x->tr["Up one directory"], 5)));
	} else {
		gmenu2x->drawButton(&bg, "x", gmenu2x->tr["Exit"],
		gmenu2x->drawButton(&bg, "b", gmenu2x->tr["Select file"], 5));
	}

	Uint32 selTick = SDL_GetTicks(), curTick;
	uint i, firstElement = 0, iY;
	screens.resize(fl.files.size());
	titles.resize(fl.files.size());

	prepare(&fl,&screens,&titles);
	uint selected = constrain(startSelection,0,fl.size()-1);

	//Add the folder icon manually to be sure to load it with alpha support since we are going to disable it for screenshots
	if (gmenu2x->sc.skinRes("imgs/folder.png")==NULL)
		gmenu2x->sc.addSkinRes("imgs/folder.png");
	gmenu2x->sc.defaultAlpha = false;
	while (!close) {
		bg.blit(gmenu2x->s,0,0);

		if (selected>=firstElement+SELECTOR_ELEMENTS) firstElement=selected-SELECTOR_ELEMENTS+1;
		if (selected<firstElement) firstElement=selected;

		//Selection
		iY = selected-firstElement;
		iY = 42+(iY*16);
		if (selected<fl.size())
			gmenu2x->s->box(1, iY, 309, 14, gmenu2x->selectionColor);

		//Files & Dirs
		gmenu2x->s->setClipRect(0,41,311,179);
		for (i=firstElement; i<fl.size() && i<firstElement+SELECTOR_ELEMENTS; i++) {
			iY = i-firstElement;
			if (fl.isDirectory(i)) {
				gmenu2x->sc["imgs/folder.png"]->blit(gmenu2x->s, 4, 42+(iY*16));
				gmenu2x->s->write(gmenu2x->font, fl[i], 21, 49+(iY*16), SFontHAlignLeft, SFontVAlignMiddle);
			} else
				gmenu2x->s->write(gmenu2x->font, titles[i-fl.dirCount()], 4, 49+(iY*16), SFontHAlignLeft, SFontVAlignMiddle);
		}
		gmenu2x->s->clearClipRect();

		if (selected-fl.dirCount()<screens.size() && screens[selected-fl.dirCount()]!="") {
			curTick = SDL_GetTicks();
			if (curTick-selTick>200)
				gmenu2x->sc[screens[selected-fl.dirCount()]]->blitRight(gmenu2x->s, 311, 42, 160, 160, min((curTick-selTick-200)/3,255));
		}

		gmenu2x->drawScrollBar(SELECTOR_ELEMENTS,fl.size(),firstElement,42,175);
		gmenu2x->s->flip();


#ifdef TARGET_GP2X
		gmenu2x->joy.update();
		if ( gmenu2x->joy[GP2X_BUTTON_START] ) { close = true; result = false; }
		if ( gmenu2x->joy[GP2X_BUTTON_UP] ) {
			if (selected==0) {
				selected = fl.size()-1;
			} else {
				selected -= 1;
			}
			selTick = SDL_GetTicks();
		}
		if ( gmenu2x->joy[GP2X_BUTTON_L] ) {
			if ((int)(selected-SELECTOR_ELEMENTS+1)<0) {
				selected = 0;
			} else {
				selected -= SELECTOR_ELEMENTS-1;
			}
			selTick = SDL_GetTicks();
		}
		if ( gmenu2x->joy[GP2X_BUTTON_DOWN] ) {
			if (selected+1>=fl.size()) {
				selected = 0;
			} else {
				selected += 1;
			}
			selTick = SDL_GetTicks();
		}
		if ( gmenu2x->joy[GP2X_BUTTON_R] ) {
			if (selected+SELECTOR_ELEMENTS-1>=fl.size()) {
				selected = fl.size()-1;
			} else {
				selected += SELECTOR_ELEMENTS-1;
			}
			selTick = SDL_GetTicks();
		}
		if ( gmenu2x->joy[GP2X_BUTTON_X] ) {
			if (link->getSelectorBrowser()) {
				string::size_type p = dir.rfind("/", dir.size()-2);
				if (p==string::npos || dir.substr(0,4)!="/mnt" || p<4) {
					close = true;
					result = false;
				} else {
					dir = dir.substr(0,p+1);
					cout << dir << endl;
					selected = 0;
					firstElement = 0;
					prepare(&fl,&screens,&titles);
				}
			} else {
				close = true;
				result = false;
			}
		}
		if ( gmenu2x->joy[GP2X_BUTTON_B] || gmenu2x->joy[GP2X_BUTTON_CLICK] ) {
			if (fl.isFile(selected)) {
				file = fl[selected];
				close = true;
			} else {
				dir = dir+fl[selected]+"/";
				selected = 0;
				firstElement = 0;
				prepare(&fl,&screens,&titles);
			}
		}
#else
		while (SDL_PollEvent(&gmenu2x->event)) {
			if ( gmenu2x->event.type == SDL_QUIT ) { close = true; result = false; }
			if ( gmenu2x->event.type==SDL_KEYDOWN ) {
				if ( gmenu2x->event.key.keysym.sym==SDLK_ESCAPE ) { close = true; result = false; }
				if ( gmenu2x->event.key.keysym.sym==SDLK_UP ) {
					if ((int)(selected-1)<0) {
						selected = fl.size()-1;
					} else {
						selected -= 1;
					}
					selTick = SDL_GetTicks();
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_DOWN ) {
					if (selected+1>=fl.size()) {
						selected = 0;
					} else {
						selected += 1;
					}
					selTick = SDL_GetTicks();
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_BACKSPACE ) {
					if (link->getSelectorBrowser()) {
						string::size_type p = dir.rfind("/", dir.size()-2);
						if (p==string::npos || dir.substr(0,4)!="/mnt" || p<4) {
							close = true;
							result = false;
						} else {
							dir = dir.substr(0,p+1);
							cout << dir << endl;
							selected = 0;
							firstElement = 0;
							prepare(&fl,&screens,&titles);
						}
					} else {
						close = true;
						result = false;
					}
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_RETURN ) {
					if (fl.isFile(selected)) {
						file = fl[selected];
						close = true;
					} else {
						dir = dir+fl[selected]+"/";
						selected = 0;
						firstElement = 0;
						prepare(&fl,&screens,&titles);
					}
				}
			}
		}
#endif
	}
	gmenu2x->sc.defaultAlpha = true;
	freeScreenshots(&screens);

	return result ? (int)selected : -1;
}

void Selector::prepare(FileLister *fl, vector<string> *screens, vector<string> *titles) {
	fl->setPath(dir);
	freeScreenshots(screens);
	screens->resize(fl->files.size());
	titles->resize(fl->files.size());

	string screendir = link->getSelectorScreens();
	if (screendir != "" && screendir[screendir.length()-1]!='/') screendir += "/";

	string noext;
	string::size_type pos;
	for (uint i=0; i<fl->files.size(); i++) {
		noext = fl->files[i];
		pos = noext.rfind(".");
		if (pos!=string::npos && pos>0)
			noext = noext.substr(0, pos);
		titles->at(i) = getAlias(noext);
		if (titles->at(i)=="")
			titles->at(i) = noext;
#ifdef DEBUG
		cout << "\033[0;34mGMENU2X:\033[0m Searching for screen " << screendir << noext << ".png" << endl;
#endif
		if (fileExists(screendir+noext+".png"))
			screens->at(i) = screendir+noext+".png";
		else if (fileExists(screendir+noext+".jpg"))
			screens->at(i) = screendir+noext+".jpg";
		else
			screens->at(i) = "";
	}
}

void Selector::freeScreenshots(vector<string> *screens) {
	for (uint i=0; i<screens->size(); i++) {
		if (screens->at(i) != "")
			gmenu2x->sc.del(screens->at(i));
	}
}

void Selector::loadAliases() {
	aliases.clear();
	if (fileExists(link->getAliasFile())) {
		string line;
		ifstream infile (link->getAliasFile().c_str(), ios_base::in);
		while (getline(infile, line, '\n')) {
			string::size_type position = line.find("=");
			string name = trim(line.substr(0,position));
			string value = trim(line.substr(position+1));
			aliases[name] = value;
		}
		infile.close();
	}
}

string Selector::getAlias(string key) {
	hash_map<string, string>::iterator i = aliases.find(key);
	if (i == aliases.end())
		return "";
	else
		return i->second;
}
