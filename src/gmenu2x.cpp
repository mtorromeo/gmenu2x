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
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <signal.h>

//for browsing the filesystem
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

//for statfs
#include <sys/vfs.h>
#include <errno.h>

#ifdef TARGET_GP2X
#include "gp2x.h"
#include <sys/fcntl.h> //for battery
#endif

#include "SFont.h"
#include "surface.h"
#include "utilities.h"
#include "inputdialog.h"
#include "gmenu2x.h"
#include "menusettingint.h"

using namespace std;
using namespace fastdelegate;

int main(int argc, char *argv[]) {
	signal(SIGINT,&exit);
	GMenu2X app(argc,argv);
	return 0;
}

GMenu2X::GMenu2X(int argc, char *argv[]) {
	path = getExePath();
	alphablend = 130;
	colorR = 255;
	colorG = 255;
	colorB = 255;

	//fork to set clock in background
	if (!fork()) {
		setClock(200);
		exit(0);
	}

	//Screen
	cout << "GMENU2X: Initializing screen..." << endl;
	if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK)<0 ) {
		fprintf(stdout, "Could not initialize SDL: %s\n", SDL_GetError());
		SDL_Quit();
	}
	s = new Surface();
	SDL_JoystickOpen(0);
	//s->raw = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
	s->raw = SDL_SetVideoMode(320, 240, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
	SDL_ShowCursor(0);

	font = new SFont( sc["imgs/font.png"]->raw );

	//Menu structure handler
	menu = new Menu(path);
	for (uint i=0; i<menu->sections.size(); i++) {
		string sectionIcon = "sections/"+menu->sections[i]+".png";
		if (fileExists(sectionIcon))
			sc.add(sectionIcon);
	}
	readConfig();

	initBG();

	//Events
#ifdef TARGET_GP2X
	joy.init(0);
#endif
	setInputSpeed();

	main();
	writeConfig();

	SDL_Quit();
	exit(0);
}

void GMenu2X::readConfig() {
	string conffile = path+"gmenu2x.conf";
	if (fileExists(conffile)) {
		ifstream inf(conffile.c_str(), ios_base::in);
		if (inf.is_open()) {
			string line;
			while (getline(inf, line, '\n')) {
				string::size_type pos = line.find("=");
				string name = trim(line.substr(0,pos));
				string value = trim(line.substr(pos+1,line.length()));

				if (name=="alpha") alphablend = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="colorR") colorR = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="colorG") colorG = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="colorB") colorB = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="section") menu->setSectionIndex( atoi(value.c_str()) );
				else if (name=="link") menu->setLinkIndex( atoi(value.c_str()) );
			}
			inf.close();
		}
	}
}

void GMenu2X::writeConfig() {
	string conffile = path+"gmenu2x.conf";
	ofstream inf(conffile.c_str());
	if (inf.is_open()) {
		inf << "colorR=" << colorR << endl;
		inf << "colorG=" << colorG << endl;
		inf << "colorB=" << colorB << endl;
		inf << "alpha=" << alphablend << endl;
		inf << "section=" << menu->selSectionIndex() << endl;
		inf << "link=" << menu->selLinkIndex() << endl;
		inf.close();
		system("sync");
	}
}

int GMenu2X::main() {
	bool quit = false;
	int x,y,ix, offset = menu->links.size()>24 ? 0 : 4;
	uint i;
	long tickBattery = -60000, tickNow;
	string batteryStatus;

	while (!quit) {
		//Background
		sc["imgs/bg.png"]->blit(s,0,0);

		//Sections
		if (menu->firstDispSection()>0)
			sc["imgs/left.png"]->blit(s,1,16);
		if (menu->firstDispSection()+5<menu->sections.size())
			sc["imgs/right.png"]->blit(s,311,16);
		for (i=menu->firstDispSection(); i<menu->sections.size() && i<menu->firstDispSection()+5; i++) {
			string sectionIcon = "sections/"+menu->sections[i]+".png";
			x = (i-menu->firstDispSection())*60+24;
			if (menu->selSectionIndex()==(int)i)
				boxRGBA(s->raw, x-14, 0, x+46, 40, colorR,colorG,colorB, alphablend);
			if (sc.exists(sectionIcon))
				sc[sectionIcon]->blit(s,x,0);
			else
				sc["icons/section.png"]->blit(s,x,0);
			writeCenter( s->raw, menu->sections[i], x+16, 27 );
		}

		//Links
		for (i=menu->firstDispRow()*6; i<(menu->firstDispRow()*6)+24 && i<menu->links.size(); i++) {
			int ir = i-menu->firstDispRow()*6;
			x = (ir%6)*52+offset;
			y = (ir/6+1)*41+1;
			ix = x+10;

			if (menu->selLink()==menu->links[i])
				boxRGBA(s->raw, x, y, x+50, y+41, colorR,colorG,colorB,alphablend);
				//sc["imgs/selection.png"]->blit(s,x,y);

			if (menu->links[i]->getIcon() != "")
				sc[menu->links[i]->getIcon()]->blit(s,ix,y);
			else
				sc["icons/generic.png"]->blit(s,ix,y);

			writeCenter( s->raw, menu->links[i]->getTitle(), ix+16, y+29 );
		}
		drawScrollBar(4,menu->links.size()/6 + ((menu->links.size()%6==0) ? 0 : 1),menu->firstDispRow(),43,159);

		if (menu->selLink()!=NULL) {
			writeCenter( s->raw, menu->selLink()->getDescription(), 160, 207 );
			write ( s->raw, menu->selLink()->clockStr(), cpuX, 223 );
		}

		//battery
		tickNow = SDL_GetTicks();
		//check battery status every 60 seconds
		if (tickNow-tickBattery >= 60000) {
			tickBattery = tickNow;
			stringstream ss;
			ss << getBatteryLevel();
			ss << "%";
			ss >> batteryStatus;
			cout << "GMENU2X: Battery level " << batteryStatus << endl;
		}
		write( s->raw, batteryStatus, batX, 223 );

#ifdef TARGET_GP2X
		joy.update();
		if ( joy[GP2X_BUTTON_START ] ) options();
		// LINK NAVIGATION
		if ( joy[GP2X_BUTTON_LEFT ] ) menu->linkLeft();
		if ( joy[GP2X_BUTTON_RIGHT] ) menu->linkRight();
		if ( joy[GP2X_BUTTON_UP   ] ) menu->linkUp();
		if ( joy[GP2X_BUTTON_DOWN ] ) menu->linkDown();
		// CLOCK DOWN
		if ( joy[GP2X_BUTTON_VOLDOWN] && !joy[GP2X_BUTTON_VOLUP] ) {
			if (menu->selLink()->clock()==0)
				menu->selLink()->setClock(200);
			else if (menu->selLink()->clock()>100)
				menu->selLink()->setClock( menu->selLink()->clock()-1 );
		}
		// CLOCK UP
		if ( joy[GP2X_BUTTON_VOLUP] && !joy[GP2X_BUTTON_VOLDOWN] ) {
			if (menu->selLink()->clock()==0)
				menu->selLink()->setClock(200);
			else if (menu->selLink()->clock()<300)
				menu->selLink()->setClock( menu->selLink()->clock()+1 );
		}
		if ( joy[GP2X_BUTTON_VOLUP] && joy[GP2X_BUTTON_VOLDOWN] ) {
			menu->selLink()->setClock(0);
		}
		if ( joy[GP2X_BUTTON_L     ] ) {
			menu->decSectionIndex();
			offset = menu->links.size()>24 ? 0 : 4;
		}
		if ( joy[GP2X_BUTTON_R     ] ) {
			menu->incSectionIndex();
			offset = menu->links.size()>24 ? 0 : 4;
		}
		if ( joy[GP2X_BUTTON_B] || joy[GP2X_BUTTON_CLICK] && menu->selLink()!=NULL ) runLink();
		if ( joy[GP2X_BUTTON_SELECT] ) contextMenu();
#else
		while (SDL_PollEvent(&event)) {
			if ( event.type == SDL_QUIT ) quit = true;
			if ( event.type==SDL_KEYDOWN ) {
				if ( event.key.keysym.sym==SDLK_ESCAPE ) quit = true;
				// LINK NAVIGATION
				if ( event.key.keysym.sym==SDLK_LEFT   ) menu->linkLeft();
				if ( event.key.keysym.sym==SDLK_RIGHT  ) menu->linkRight();
				if ( event.key.keysym.sym==SDLK_UP     ) menu->linkUp();
				if ( event.key.keysym.sym==SDLK_DOWN   ) menu->linkDown();
				// CLOCK DOWN
				if ( event.key.keysym.sym==SDLK_z      ) {
					if (menu->selLink()->clock()==0)
						menu->selLink()->setClock(200);
					else if (menu->selLink()->clock()>100)
						menu->selLink()->setClock( menu->selLink()->clock()-1 );
				}
				// CLOCK UP
				if ( event.key.keysym.sym==SDLK_x      ) {
					if (menu->selLink()->clock()==0)
						menu->selLink()->setClock(200);
					else if (menu->selLink()->clock()<300)
						menu->selLink()->setClock( menu->selLink()->clock()+1 );
				}
				if ( event.key.keysym.sym==SDLK_q      ) {
					menu->decSectionIndex();
					offset = menu->links.size()>24 ? 0 : 4;
				}
				if ( event.key.keysym.sym==SDLK_w      ) {
					menu->incSectionIndex();
					offset = menu->links.size()>24 ? 0 : 4;
				}
				if ( event.key.keysym.sym==SDLK_s      ) options();
				if ( event.key.keysym.sym==SDLK_RETURN && menu->selLink()!=NULL ) runLink();
				if ( event.key.keysym.sym==SDLK_SPACE  ) contextMenu();
			}
		}
#endif

		s->flip();
	}

	return -1;
}

void GMenu2X::options() {
#ifdef TARGET_GP2X
	joy.setInterval(30,  GP2X_BUTTON_LEFT );
	joy.setInterval(30,  GP2X_BUTTON_RIGHT);
#endif

	Surface bg ("imgs/bg.png");

	vector<MenuSetting *> voices;
	voices.resize(4);
	voices[0] = new MenuSettingInt(this,"Color (Red)","Red part of the color of the interface",&colorR,0,255);
	voices[1] = new MenuSettingInt(this,"Color (Green)","Green part of the color of the interface",&colorG,0,255);
	voices[2] = new MenuSettingInt(this,"Color (Blue)","Blue part of the color of the interface",&colorB,0,255);
	voices[3] = new MenuSettingInt(this,"Color (Alpha)","Transparency of the interface",&alphablend,0,255);

	bool close = false;
	uint i, sel = 0, iY;

	while (!close) {
		bg.blit(s,0,0);
		//top bar
		boxRGBA(s->raw, 0, 0, 320, 15, colorR,colorG,colorB,alphablend);
		writeCenter(s->raw, "Settings", 160, 1);
	//bottom bar
		boxRGBA(s->raw, 0, 225, 320, 240, colorR,colorG,colorB,alphablend);

		//selection
		iY = 18+(sel*17);
		boxRGBA(s->raw, 2, iY, 318, iY+16, colorR,colorG,colorB,alphablend);

		for (i=0; i<voices.size(); i++) {
			voices[i]->draw(i*17+20);
		}

		//description at bottom
		writeCenter(s->raw, voices[sel]->description, 160, 226);

#ifdef TARGET_GP2X
		joy.update();
		if ( joy[GP2X_BUTTON_START] ) close = true;
		if ( joy[GP2X_BUTTON_UP    ] ) sel = max(0, sel-1);
		if ( joy[GP2X_BUTTON_DOWN  ] ) sel = min(voices.size()-1, sel+1);
		voices[sel]->manageInput();
#else
		while (SDL_PollEvent(&event)) {
			if ( event.type == SDL_QUIT ) return;
			if ( event.type==SDL_KEYDOWN ) {
				if ( event.key.keysym.sym==SDLK_ESCAPE ) close = true;
				if ( event.key.keysym.sym==SDLK_UP ) sel = max(0, sel-1);
				if ( event.key.keysym.sym==SDLK_DOWN ) sel = min(voices.size()-1, sel+1);
				voices[sel]->manageInput();
			}
		}
#endif

		s->flip();
	}

	for (i=0; i<voices.size(); i++) {
		free(voices[i]);
	}
	writeConfig();
	initBG();
	setInputSpeed();
}

void GMenu2X::contextMenu() {
	Surface bg(s);
	//Darken background
	boxRGBA(bg.raw, 0, 0, 320, 240, 0,0,0,150);

	vector<MenuOption> voices;
	{
	MenuOption opt = {"Add link in '"+menu->selSection()+"'", MakeDelegate(this, &GMenu2X::fileBrowser)};
	voices.push_back(opt);
	}

	if (menu->selLink()!=NULL) {
		{
		MenuOption opt = {"Rename link '"+menu->selLink()->getTitle()+"'", MakeDelegate(this, &GMenu2X::renameLink)};
		voices.push_back(opt);
		}
		{
		MenuOption opt = {"Edit description for '"+menu->selLink()->getTitle()+"'", MakeDelegate(this, &GMenu2X::editDescriptionLink)};
		voices.push_back(opt);
		}
		{
		MenuOption opt = {"Delete link '"+menu->selLink()->getTitle()+"'", MakeDelegate(this, &GMenu2X::deleteLink)};
		voices.push_back(opt);
		}
	}

	bool close = false;
	uint i, sel = 0;

	int h = font->getHeight();
	SDL_Rect box;
	box.h = (h+2)*voices.size()+8;
	box.w = 0;
	for (i=0; i<voices.size(); i++) {
		int w = font->getTextWidth(voices[i].text);
		if (w>box.w) box.w = w;
	}
	box.w += 23;
	box.x = 160 - box.w/2;
	box.y = 120 - box.h/2;

	SDL_Rect selbox = {box.x+4, 0, box.w-8, h+2};

	while (!close) {
		bg.blit(s,0,0);
		SDL_FillRect( s->raw, &box, SDL_MapRGB(s->format(),255,255,255) );
		selbox.y = box.y+4+(h+2)*sel;
		SDL_FillRect( s->raw, &selbox, SDL_MapRGB(s->format(),160,160,160) );
		rectangleColor( s->raw, box.x+2, box.y+2, box.x+box.w-3, box.y+box.h-3, SDL_MapRGB(s->format(),80,80,80) );
		for (i=0; i<voices.size(); i++) {
			write( s->raw, voices[i].text, box.x+12, box.y+5+(h+2)*i );
		}

#ifdef TARGET_GP2X
		joy.update();
		if ( joy[GP2X_BUTTON_SELECT] ) close = true;
		if ( joy[GP2X_BUTTON_UP    ] ) sel = max(0, sel-1);
		if ( joy[GP2X_BUTTON_DOWN  ] ) sel = min(voices.size()-1, sel+1);
		if ( joy[GP2X_BUTTON_B] || joy[GP2X_BUTTON_CLICK] ) { voices[sel].action(); return; }
#else
		while (SDL_PollEvent(&event)) {
			if ( event.type == SDL_QUIT ) return;
			if ( event.type==SDL_KEYDOWN ) {
				if ( event.key.keysym.sym==SDLK_ESCAPE ) close = true;
				if ( event.key.keysym.sym==SDLK_UP ) sel = max(0, sel-1);
				if ( event.key.keysym.sym==SDLK_DOWN ) sel = min(voices.size()-1, sel+1);
				if ( event.key.keysym.sym==SDLK_RETURN ) { voices[sel].action(); return; }
			}
		}
#endif

		s->flip();
	}
}

void GMenu2X::deleteLink() {
	unlink(menu->selLink()->file.c_str());
	menu->setSectionIndex( menu->selSectionIndex() ); //Force a reload of current section links
	system("sync");
}

void GMenu2X::renameLink() {
	InputDialog id(this,"Select a title for the link",menu->selLink()->getTitle());
	if (id.exec()) {
		menu->selLink()->setTitle( id.input );
		menu->selLink()->save();
		system("sync");
	}
}

void GMenu2X::editDescriptionLink() {
	InputDialog id(this,"Insert link description",menu->selLink()->getDescription());
	if (id.exec()) {
		menu->selLink()->setDescription( id.input );
		menu->selLink()->save();
		system("sync");
	}
}

void GMenu2X::fileBrowser() {
	bool close = false;

#ifdef TARGET_GP2X
	string curpath = "/mnt/sd";
#else
	string curpath = "/home/ryo";
#endif
	vector<string> directories;
	vector<string> files;
	browsePath(curpath,&directories,&files);

	Surface bg("imgs/bg.png");
	boxRGBA(bg.raw, 0, 0, 320, 15, colorR,colorG,colorB,alphablend);

	//A Button
	filledCircleRGBA(bg.raw, 12, 228, 7, 0,0,0,255);
	writeCenter(bg.raw, "A", 13, 222);
	write(bg.raw, "Up one folder", 23, 222);

	//B Button
	filledCircleRGBA(bg.raw, 100, 228, 7, 0,0,0,255);
	writeCenter(bg.raw, "B", 101, 222);
	write(bg.raw, "Enter folder/Confirm", 111, 222);

	uint i, selected = 0, firstElement = 0, iY, ds;

	while (!close) {
		bg.blit(s,0,0);
		writeCenter(s->raw,"File Browser",160,1);

		if (selected>firstElement+10) firstElement=selected-10;
		if (selected<firstElement) firstElement=selected;

		//Selection
		iY = selected-firstElement;
		iY = 20+(iY*18);
		boxRGBA(s->raw, 2, iY, 310, iY+16, colorR,colorG,colorB,alphablend);

		//Directories
		for (i=firstElement; i<directories.size() && i<firstElement+11; i++) {
			iY = i-firstElement;
			sc["imgs/folder.png"]->blit(s, 5, 21+(iY*18));
			write(s->raw, directories[i], 24, 22+(iY*18));
		}

		//Files
		ds = directories.size();
		for (; i<files.size()+ds && i<firstElement+11; i++) {
			iY = i-firstElement;
			sc["imgs/file.png"]->blit(s, 5, 21+(iY*18));
			write(s->raw, files[i-ds], 24, 22+(iY*18));
		}

		drawScrollBar(11,directories.size()+files.size(),firstElement,20,196);
		s->flip();


#ifdef TARGET_GP2X
		joy.update();
		if ( joy[GP2X_BUTTON_SELECT] ) close = true;
		if ( joy[GP2X_BUTTON_UP    ] ) {
			if ((int)(selected-1)<0)
				selected = directories.size()+files.size()-1;
			else
				selected -= 1;
		}
		if ( joy[GP2X_BUTTON_DOWN  ] ) {
			if (selected+1>=directories.size()+files.size())
				selected = 0;
			else
				selected += 1;
		}
		if ( joy[GP2X_BUTTON_A     ] ) {
			string::size_type p = curpath.rfind("/");
			if (p==string::npos || curpath.substr(0,7)!="/mnt/sd" || p<7)
				return;
			else
				curpath = curpath.substr(0,p);
			selected = 0;
			browsePath(curpath,&directories,&files);
		}
		if ( joy[GP2X_BUTTON_B] || joy[GP2X_BUTTON_CLICK] ) {
			if (selected<directories.size()) {
				curpath += "/"+directories[selected];
				selected = 0;
				browsePath(curpath,&directories,&files);
			} else {
				if (selected-directories.size()<files.size()) {
					createLink(curpath, files[selected-directories.size()]);
					menu->setSectionIndex( menu->selSectionIndex() ); //Force a reload of current section links
					close = true;
				}
			}
		}
#else
		while (SDL_PollEvent(&event)) {
			if ( event.type == SDL_QUIT ) return;
			if ( event.type==SDL_KEYDOWN ) {
				if ( event.key.keysym.sym==SDLK_ESCAPE ) close = true;
				if ( event.key.keysym.sym==SDLK_UP ) {
					if ((int)(selected-1)<0) {
						selected = directories.size()+files.size()-1;
					} else
						selected -= 1;
				}
				if ( event.key.keysym.sym==SDLK_DOWN ) {
					if (selected+1>=directories.size()+files.size())
						selected = 0;
					else
						selected += 1;
				}
				if ( event.key.keysym.sym==SDLK_BACKSPACE ) {
					string::size_type p = curpath.rfind("/");
					if (p==string::npos || curpath.substr(0,9)!="/home/ryo" || p<9)
						return;
					else
						curpath = curpath.substr(0,p);
					selected = 0;
					browsePath(curpath,&directories,&files);
				}
				if ( event.key.keysym.sym==SDLK_RETURN ) {
					if (selected<directories.size()) {
						curpath += "/"+directories[selected];
						selected = 0;
						browsePath(curpath,&directories,&files);
					} else {
						if (selected-directories.size()<files.size()) {
							createLink(curpath, files[selected-directories.size()]);
							menu->setSectionIndex( menu->selSectionIndex() ); //Force a reload of current section links
							close = true;
						}
					}
				}
			}
		}
#endif
	}

	return;
}

void GMenu2X::createLink(string path, string file) {
	if (path[path.length()-1]!='/') path += "/";

	string title = file;
	string::size_type pos = title.rfind(".");
	if (pos!=string::npos && pos>0)
		title = title.substr(0, pos);

	cout << "GMENU2X: Creating link " << title << endl;

	string linkpath = "sections/"+menu->selSection()+"/"+title;

	if (title.length()>9) {
		title = title.substr(0,7)+"..";
	}

	ofstream f(linkpath.c_str());
	if (f.is_open()) {
		f << "title=" << title << endl;
		if (fileExists(path+title+".png"))
			f << "icon=" << path << title << ".png" << endl;
		f << "exec=" << path << file << endl;
		f.close();
		system("sync");
	} else
		cout << "GMENU2X: Error while opening the file '" << linkpath << "' for write" << endl;
}

void GMenu2X::browsePath(string path, vector<string>* directories, vector<string>* files) {
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
		if (S_ISDIR(st.st_mode))
			directories->push_back((string)dptr->d_name);
		else
			files->push_back((string)dptr->d_name);
	}

	closedir(dirp);

	sort(directories->begin(),directories->end());
	sort(files->begin(),files->end());
}

GMenu2X::~GMenu2X() {
	free(menu);
	free(s);
	free(font);
}

unsigned short GMenu2X::getBatteryLevel() {
#ifdef TARGET_GP2X
	int devbatt = open ("/dev/batt", O_RDONLY);
	if (devbatt<0) return 0;

	int battval = 0;
	unsigned short cbv;
	int v;

	for (int i = 0; i < BATTERY_READS; i ++) {
		if (read (devbatt, &cbv, 2) == 2)
			battval += cbv;
	}
 	close(devbatt);

 	battval /= BATTERY_READS;
 	battval -= 645; //645 ~= 2.3v (0%) , 745 ~= 2.6v (100%)
 	if (battval<0) battval = 0;
 	//battval = battval*100/xxx; //max-min=xxx
 	if (battval>100) battval = 100;

 	return battval;
#else
	return 100;
#endif
}

void GMenu2X::setInputSpeed() {
#ifdef TARGET_GP2X
	joy.setInterval(150);
	joy.setInterval(30,  GP2X_BUTTON_VOLDOWN);
	joy.setInterval(30,  GP2X_BUTTON_VOLUP  );
	joy.setInterval(500, GP2X_BUTTON_START  );
	joy.setInterval(500, GP2X_BUTTON_SELECT );
	joy.setInterval(300, GP2X_BUTTON_A      );
	joy.setInterval(1000,GP2X_BUTTON_B      );
	joy.setInterval(1000,GP2X_BUTTON_CLICK  );
	joy.setInterval(300, GP2X_BUTTON_L      );
	joy.setInterval(300, GP2X_BUTTON_R      );
#else
	SDL_EnableKeyRepeat(1,150);
#endif
}

void GMenu2X::initBG() {
	sc.del("imgs/bg.png");

	//Top Bar
	boxRGBA(sc["imgs/bg.png"]->raw, 0, 0, 320, 40, colorR,colorG,colorB,alphablend);
	//Bottom Bar
	boxRGBA(sc["imgs/bg.png"]->raw, 0, 220, 320, 240, colorR,colorG,colorB,alphablend);

	Surface sd("imgs/sd.png");
	Surface cpu("imgs/cpu.png");
	Surface battery("imgs/battery.png");
	string df = getDiskFree();

	sd.blit( sc["imgs/bg.png"], 3, 222 );
	write( sc["imgs/bg.png"]->raw, df, 22, 223 );
	batX = 27+font->getTextWidth(df);
	battery.blit( sc["imgs/bg.png"], batX, 222 );
	batX += 19;
	cpuX = batX+5+font->getTextWidth("100%");
	cpu.blit( sc["imgs/bg.png"], cpuX, 222 );
	cpuX += 19;
}

void GMenu2X::drawScrollBar(uint pagesize, uint totalsize, uint pagepos, uint top, uint height) {
	if (totalsize<=pagesize) return;

	rectangleRGBA(s->raw, 312, top, 317, top+height, colorR,colorG,colorB,150);
	//internal bar total height = height-2
	//bar size
	uint bs = (height-2) * pagesize / totalsize;
	//bar y position
	uint by = (height-2) * pagepos / totalsize;
	by = top+2+by;
	if (by+bs>top+height-2) by = top+height-2-bs;

	boxRGBA(s->raw, 314, by, 315, by+bs, colorR,colorG,colorB,150);
}

void GMenu2X::write(SDL_Surface *s, string text, int x, int y) {
	font->write(s,text.c_str(),x,y);
}

void GMenu2X::writeCenter(SDL_Surface *s, string text, int x, int y) {
	font->writeCenter(s,text.c_str(),x,y);
}

void GMenu2X::drawRun() {
	//Darkened background
	boxRGBA(s->raw, 0, 0, 320, 240, 0,0,0,150);

	string text = "Launching "+menu->selLink()->getTitle();
	int textW = font->getTextWidth(text);
	int boxW = 62+textW;
	int halfBoxW = boxW/2;

	//outer box
	SDL_Rect r = {158-halfBoxW, 97, halfBoxW*2+5, 47};
	SDL_FillRect(s->raw, &r, SDL_MapRGB(s->format(),255,255,255));
	//draw inner rectangle
	rectangleColor(s->raw, 160-halfBoxW, 99, 160+halfBoxW, 141, SDL_MapRGB(s->format(),80,80,80));

	int x = 170-halfBoxW;
	if (menu->selLink()->getIcon()!="")
		sc[menu->selLink()->getIcon()]->blit(s,x,104);
	else
		sc["icons/generic.png"]->blit(s,x,104);
	write( s->raw, text, x+42, 114 );
	s->flip();
}

void GMenu2X::setClock(int mhz) {
	string command = "";
	stringstream ss;
	ss << mhz;
	ss >> command;
	cout << "GMENU2X: Setting clock speed at " << command << "MHZ" << endl;
	command = path + "scripts/cpuspeed.sh " + command;
	cout << "GMENU2X: " << command << endl;
#ifdef TARGET_GP2X
	system(command.c_str());
#endif
}

void GMenu2X::runLink() {
	drawRun();
#ifndef TARGET_GP2X
	//delay for testing
	SDL_Delay(2000);
#endif
	for (uint i=0; i<menu->links.size(); i++)
		menu->links[i]->save();
	writeConfig();
	if (menu->selLink()->clock()>0)
		setClock(menu->selLink()->clock());
	menu->selLink()->run();
}

string GMenu2X::getExePath() {
	stringstream ss;
	ss << "/proc/" << getpid() << "/exe";
	string p;
	ss >> p;
	char buf[255];
	int l = readlink(p.c_str(),buf,255);
	p = buf;
	p = p.substr(0,l);
	l = p.rfind("/");
	return p.substr(0,l+1);
}

string GMenu2X::getDiskFree() {
	stringstream ss;
	string df = "";
	struct statfs b;

#ifdef TARGET_GP2X
	int ret = statfs("/mnt/sd", &b);
#else
	int ret = statfs("/mnt/usb", &b);
#endif
	if (ret==0) {
		ss << b.f_bfree*b.f_bsize/1048576 << "/" << b.f_blocks*b.f_bsize/1048576 << "MB";
		ss >> df;
	} else cout << "GMENU2X: statfs failed with error '" << strerror(errno) << "'" << endl;
	return df;
}
