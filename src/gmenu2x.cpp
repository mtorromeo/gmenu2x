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
#include "SDL.h"
#include "SDL_gfxPrimitives.h"

//for statfs
#include <sys/vfs.h>
#include <errno.h>

#ifdef TARGET_GP2X
#include "gp2x.h"
#include "joystick.h"
#endif

#include "SFont.h"
#include "surface.h"
#include "gmenu2x.h"

using namespace std;

int main(int argc, char *argv[]) {
	GMenu2X app;
	return 0;
}

bool fileExists(string file) {
	fstream fin;
	fin.open(file.c_str() ,ios::in);
	bool exists = fin.is_open();
	fin.close();

	return exists;
}

GMenu2X::GMenu2X() {
	path = getExePath();

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
	s = new Surface(320,240);

	font = new SFont( sc["imgs/font.png"]->raw );

	//Menu structure handler
	menu = new Menu(path);
	for (uint i=0; i<menu->sections.size(); i++) {
		string sectionIcon = "sections/"+menu->sections[i]+".png";
		if (fileExists(sectionIcon))
			sc.add(sectionIcon);
	}

	blendcolor = SDL_MapRGBA(s->format(), 0xFF, 0xFF, 0xFF, 140);
	initBG();
	//generic.load("icons/generic.png");
	//selection.load("imgs/selection.png");

	//Events
#ifdef TARGET_GP2X
	Joystick joy(0);
	joy.setInterval(150);
	joy.setInterval(30,  GP2X_BUTTON_VOLDOWN);
	joy.setInterval(30,  GP2X_BUTTON_VOLUP  );
	joy.setInterval(500, GP2X_BUTTON_SELECT );
	joy.setInterval(1000,GP2X_BUTTON_B      );
#else
	SDL_Event event;
	SDL_EnableKeyRepeat(1,150);
#endif

	bool quit = false, showFPS = false;
	int x,y,ix,iy,i, offset = menu->links.size()>24 ? 0 : 10, firstRow = 0;
	Uint32 lastFrame = SDL_GetTicks(), thisFrame, numFrames = 0;

	while (!quit) {
		sc["imgs/bg.png"]->blit(s,0,0);

		if (menu->firstDispSection()>0)
			sc["imgs/left.png"]->blit(s,1,16);
		if (menu->firstDispSection()+5<menu->sections.size())
			sc["imgs/right.png"]->blit(s,311,16);
		for (uint ui=menu->firstDispSection(); ui<menu->sections.size() && ui<menu->firstDispSection()+5; ui++) {
			string sectionIcon = "sections/"+menu->sections[ui]+".png";
			x = (ui-menu->firstDispSection())*60+24;
			if (menu->selSectionIndex()==(int)ui)
				boxRGBA(s->raw, x-14, 0, x+46, 40, 255, 255, 255, 130);
			if (sc.exists(sectionIcon))
				sc[sectionIcon]->blit(s,x,0);
			writeCenter( s->raw, menu->sections[ui], x+16, 27 );
		}

		for (i=firstRow*8; i<(firstRow*8)+32 && i<(int)menu->links.size(); i++) {
			x = (i%6)*50+offset;
			y = (i/6+1)*40;
			ix = x+9;
			iy = y+2;

			if (menu->selLink()==menu->links[i])
				sc["imgs/selection.png"]->blit(s,x,y);

			if (menu->links[i]->icon != "")
				sc[menu->links[i]->icon]->blit(s,ix,iy);
			else
				sc["icons/generic.png"]->blit(s,ix,iy);

			writeCenter( s->raw, menu->links[i]->title, ix+16, iy+28 );
		}

		writeCenter( s->raw, menu->selLink()->description, 160, 206 );
		write ( s->raw, menu->selLink()->clockStr(), cpuX, 223 );

		//Frames per second
		numFrames++;
		thisFrame = SDL_GetTicks();
		if (thisFrame-lastFrame>=1000) {
			stringstream ss;
			fps = "";
			ss << (numFrames*1000/(thisFrame-lastFrame)) << "fps";
			//ss << numFrames << "fps";
			ss >> fps;
			lastFrame = thisFrame;
			numFrames = 0;
		}
		if (showFPS) drawFPS();

#ifdef TARGET_GP2X
		joy.update();
		if ( joy[GP2X_BUTTON_START ] ) quit = true;
		if ( joy[GP2X_BUTTON_SELECT] ) showFPS = !showFPS;
		// LINK LEFT
		if ( joy[GP2X_BUTTON_LEFT] ) {
			menu->decLinkIndex();
			offset = menu->links.size()>24 ? 0 : 10;
		}
		// LINK RIGHT
		if ( joy[GP2X_BUTTON_RIGHT] ) {
			menu->incLinkIndex();
			offset = menu->links.size()>24 ? 0 : 10;
		}
		// LINK UP
		if ( joy[GP2X_BUTTON_UP] ) {
				int l = menu->selLinkIndex()-6;
				if (l<0) {
					int rows = menu->links.size()/6+1;
					l = (rows*6)+l;
					if (l >= (int)menu->links.size())
						l -= 6;
				}
				menu->setLinkIndex(l);
		}
		// LINK DOWN
		if ( joy[GP2X_BUTTON_DOWN] ) {
			uint l = menu->selLinkIndex()+6;
			if (l >= menu->links.size())
				l %= 6;
			menu->setLinkIndex(l);
		}
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
		if ( joy[GP2X_BUTTON_L     ] ) menu->decSectionIndex();
		if ( joy[GP2X_BUTTON_R     ] ) menu->incSectionIndex();
		if ( joy[GP2X_BUTTON_B     ] && menu->selLink()!=NULL ) runLink();
#else
		while (SDL_PollEvent(&event)) {
			if ( event.type == SDL_QUIT ) quit = true;
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE ) quit = true;
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_SPACE  ) showFPS = !showFPS;
			// LINK LEFT
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_LEFT   )  {
				menu->decLinkIndex();
				offset = menu->links.size()>24 ? 0 : 10;
			}
			// LINK RIGHT
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_RIGHT  )  {
				menu->incLinkIndex();
				offset = menu->links.size()>24 ? 0 : 10;
			}
			// LINK UP
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_UP     ) {
				int l = menu->selLinkIndex()-6;
				if (l<0) {
					int rows = menu->links.size()/6+1;
					l = (rows*6)+l;
					if (l >= (int)menu->links.size())
						l -= 6;
				}
				menu->setLinkIndex(l);
			}
			// LINK DOWN
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_DOWN   ) {
				uint l = menu->selLinkIndex()+6;
				if (l >= menu->links.size())
					l %= 6;
				menu->setLinkIndex(l);
			}
			// CLOCK DOWN
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_z      ) {
				if (menu->selLink()->clock()==0)
					menu->selLink()->setClock(200);
				else if (menu->selLink()->clock()>100)
					menu->selLink()->setClock( menu->selLink()->clock()-1 );
			}
			// CLOCK UP
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_x      ) {
				if (menu->selLink()->clock()==0)
					menu->selLink()->setClock(200);
				else if (menu->selLink()->clock()<300)
					menu->selLink()->setClock( menu->selLink()->clock()+1 );
			}
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_q      ) menu->decSectionIndex();
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_w      ) menu->incSectionIndex();
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_RETURN && menu->selLink()!=NULL ) runLink();
		}
#endif

		s->flip();
	}

	exit(0);
}

GMenu2X::~GMenu2X() {
	free(menu);
	free(s);
	free(font);
}

void GMenu2X::initBG() {
	//Top Bar
	boxRGBA(sc["imgs/bg.png"]->raw, 0, 0, 320, 40, 255, 255, 255, 130);
	//Bottom Bar
	boxRGBA(sc["imgs/bg.png"]->raw, 0, 220, 320, 240, 255, 255, 255, 130);

	Surface sd("imgs/sd.png");
	Surface cpu("imgs/cpu.png");
	string df = getDiskFree();

	sd.blit( sc["imgs/bg.png"], 3, 222 );
	write( sc["imgs/bg.png"]->raw, df, 22, 223 );
	cpuX = 27+font->getTextWidth(df);
	cpu.blit( sc["imgs/bg.png"], cpuX, 222 );
	cpuX += 19;
}

void GMenu2X::write(SDL_Surface *s, string text, int x, int y) {
	font->write(s,text.c_str(),x,y);
}

void GMenu2X::writeCenter(SDL_Surface *s, string text, int x, int y) {
	font->writeCenter(s,text.c_str(),x,y);
}

void GMenu2X::drawFPS() {
	write( s->raw, fps, 270,5);
}

void GMenu2X::drawRun() {
	string text = "Launching "+menu->selLink()->title;
	int textW = font->getTextWidth(text);
	int boxW = 62+textW;
	int halfBoxW = boxW/2;

	//outer box
	boxRGBA(s->raw, 158-halfBoxW, 97, 162+halfBoxW, 143, 255,255,255,180);
	//draw inner rectangle
	rectangleColor(s->raw, 160-halfBoxW, 99, 160+halfBoxW, 141, SDL_MapRGB(s->format(),80,80,80));

	int x = 170-halfBoxW;
	if (menu->selLink()->icon!="")
		sc[menu->selLink()->icon]->blit(s,x,104);
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
