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

using namespace std;

FileDialog::FileDialog(GMenu2X *gmenu2x, string text, string filter) {
	this->gmenu2x = gmenu2x;
	this->text = text;
	split(this->filter,filter,",");
	selRow = 0;
}

bool FileDialog::exec() {
	bool close = false, result = true;
	path = "/mnt";

	vector<string> directories;
	vector<string> files;
	browsePath(path,&directories,&files);

	Surface bg("imgs/bg.png");
	gmenu2x->drawTopBar(&bg,15);
	bg.write(gmenu2x->font,"File Browser: "+text,160,8, SFontHAlignCenter, SFontVAlignMiddle);
	gmenu2x->drawBottomBar(&bg);

	gmenu2x->drawButton(&bg, "B", "Enter folder/Confirm",
	gmenu2x->drawButton(&bg, "A", "Up one folder", 10));
	

	uint i, selected = 0, firstElement = 0, iY, ds;

	while (!close) {
		bg.blit(gmenu2x->s,0,0);

		if (selected>firstElement+10) firstElement=selected-10;
		if (selected<firstElement) firstElement=selected;

		//Selection
		iY = selected-firstElement;
		iY = 20+(iY*18);
		gmenu2x->s->box(2, iY, 308, 16, gmenu2x->selectionColor);

		//Directories
		for (i=firstElement; i<directories.size() && i<firstElement+11; i++) {
			iY = i-firstElement;
			gmenu2x->sc["imgs/folder.png"]->blit(gmenu2x->s, 5, 21+(iY*18));
			gmenu2x->s->write(gmenu2x->font, directories[i], 24, 29+(iY*18), SFontHAlignLeft, SFontVAlignMiddle);
		}

		//Files
		ds = directories.size();
		for (; i<files.size()+ds && i<firstElement+11; i++) {
			iY = i-firstElement;
			gmenu2x->sc["imgs/file.png"]->blit(gmenu2x->s, 5, 21+(iY*18));
			gmenu2x->s->write(gmenu2x->font, files[i-ds], 24, 29+(iY*18), SFontHAlignLeft, SFontVAlignMiddle);
		}

		gmenu2x->drawScrollBar(11,directories.size()+files.size(),firstElement,20,196);
		gmenu2x->s->flip();


#ifdef TARGET_GP2X
		gmenu2x->joy.update();
		if ( gmenu2x->joy[GP2X_BUTTON_SELECT] ) { close = true; result = false; }
		if ( gmenu2x->joy[GP2X_BUTTON_UP    ] ) {
			if (selected==0)
				selected = directories.size()+files.size()-1;
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
			if (selected+1>=directories.size()+files.size())
				selected = 0;
			else
				selected += 1;
		}
		if ( gmenu2x->joy[GP2X_BUTTON_R     ] ) {
			if (selected+10>=directories.size()+files.size()) {
				selected = directories.size()+files.size()-1;
			} else {
				selected += 10;
			}
		}
		if ( gmenu2x->joy[GP2X_BUTTON_A] || gmenu2x->joy[GP2X_BUTTON_LEFT] ) {
			string::size_type p = path.rfind("/");
			if (p==string::npos || path.substr(0,4)!="/mnt" || p<4)
				return false;
			else
				path = path.substr(0,p);
			selected = 0;
			browsePath(path,&directories,&files);
		}
		if ( gmenu2x->joy[GP2X_BUTTON_B] || gmenu2x->joy[GP2X_BUTTON_CLICK] ) {
			if (selected<directories.size()) {
				path += "/"+directories[selected];
				selected = 0;
				browsePath(path,&directories,&files);
			} else {
				if (selected-directories.size()<files.size()) {
					file = files[selected-directories.size()];
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
						selected = directories.size()+files.size()-1;
					} else
						selected -= 1;
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_DOWN ) {
					if (selected+1>=directories.size()+files.size())
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
					browsePath(path,&directories,&files);
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_RETURN ) {
					if (selected<directories.size()) {
						path += "/"+directories[selected];
						selected = 0;
						browsePath(path,&directories,&files);
					} else {
						if (selected-directories.size()<files.size()) {
							file = files[selected-directories.size()];
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

void FileDialog::browsePath(string path, vector<string>* directories, vector<string>* files) {
	DIR *dirp;
	struct stat st;
	struct dirent *dptr;
	string filepath;

	directories->clear();
	files->clear();

	if ((dirp = opendir(path.c_str())) == NULL) return;
	if (path[path.length()-1]!='/') path += "/";

	while ((dptr = readdir(dirp))) {
		if (dptr->d_name[0]=='.') continue;
		filepath = path+dptr->d_name;
		int statRet = stat(filepath.c_str(), &st);
		if (statRet == -1) continue;
		if (S_ISDIR(st.st_mode)) {
			string dname = dptr->d_name;
			if (!(path=="/mnt/" && (dname!="sd" && dname!="ext" && dname!="nand")))
				directories->push_back(dname);
		} else {
			bool filterOk = false;
			string file = dptr->d_name;
			for (uint i = 0; i<filter.size() && !filterOk; i++) {
				filterOk = file.substr(file.length()-filter[i].length(),filter[i].length())==filter[i];
			}
			if (filterOk)
				files->push_back(file);
		}
	}

	closedir(dirp);

	sort(directories->begin(),directories->end(),case_less());
	sort(files->begin(),files->end(),case_less());
}
