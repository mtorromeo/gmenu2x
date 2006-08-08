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
#include <stdlib.h>
#include <unistd.h>
#include "SDL.h"

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

GMenu2X::GMenu2X() {
	string path = getExePath();
	string df = getDiskFree();

	//Screen
	cout << "GMENU2X: Initializing screen..." << endl;
	if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK)<0 ) {
		fprintf(stdout, "Could not initialize SDL: %s\n", SDL_GetError());
		SDL_Quit();
	}
	s = new Surface(320,240);

	//Menu structure handler
	menu = new Menu(path);

	generic.load("icons/generic.png");
	selection.load("imgs/selection.png");

	//Events
#ifdef TARGET_GP2X
	Joystick joy(0);
	joy.setInterval(150);
#else
	SDL_Event event;
	SDL_EnableKeyRepeat(1,150);
#endif

	bool quit = false, showFPS = false;
	int x,y,ix,iy, i, firstRow = 0;
	Uint32 lastFrame = SDL_GetTicks(), thisFrame, numFrames = 0;

	while (!quit) {
		menu->bg.blit(s,0,0);

		for (i=firstRow*8; i<(firstRow*8)+32 && i<(int)menu->links.size(); i++) {
			x = (i%6)*50;
			y = (i/6+1)*40;
			ix = x+9;
			iy = y+2;

			if (menu->selLink()==menu->links[i])
				selection.blit(s,x,y);

			if (menu->links[i]->icon.raw!=NULL)
				menu->links[i]->icon.blit(s,ix,iy);
			else
				generic.blit(s,ix,iy);

			menu->writeCenter( s->raw, menu->links[i]->title, ix+16, iy+30 );
		}

		menu->writeCenter( s->raw, menu->selLink()->description, 160, 205 );
		menu->write( s->raw, df, 22, 223 );

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
		if ( joy[GP2X_BUTTON_LEFT  ] ) menu->decLinkIndex();
		if ( joy[GP2X_BUTTON_RIGHT ] ) menu->incLinkIndex();
		if ( joy[GP2X_BUTTON_UP  ] ) {
				int l = menu->selLinkIndex()-6;
				if (l<0) {
					int rows = menu->links.size()/6+1;
					l = (rows*6)+l;
					if (l >= (int)menu->links.size())
						l -= 6;
				}
				menu->setLinkIndex(l);
		}
		if ( joy[GP2X_BUTTON_DOWN  ] ) {
			uint l = menu->selLinkIndex()+6;
			if (l >= menu->links.size())
				l %= 6;
			menu->setLinkIndex(l);
		}
		if ( joy[GP2X_BUTTON_L     ] ) menu->decSectionIndex();
		if ( joy[GP2X_BUTTON_R     ] ) menu->incSectionIndex();
		if ( joy[GP2X_BUTTON_B     ] && menu->selLink()!=NULL ) {
			drawRun();
			menu->selLink()->run();
		}
#else
		while (SDL_PollEvent(&event)) {
			if ( event.type == SDL_QUIT ) quit = true;
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE ) quit = true;
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_SPACE  ) showFPS = !showFPS;
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_LEFT   ) menu->decLinkIndex();
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_RIGHT  ) menu->incLinkIndex();
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
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_DOWN   ) {
				uint l = menu->selLinkIndex()+6;
				if (l >= menu->links.size())
					l %= 6;
				menu->setLinkIndex(l);
			}
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_q      ) menu->decSectionIndex();
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_w      ) menu->incSectionIndex();
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_RETURN && menu->selLink()!=NULL ) {
				drawRun();
				//delay for testing
				SDL_Delay(3000);
				menu->selLink()->run();
			}
		}
#endif

		s->flip();
	}
	exit(0);
}

GMenu2X::~GMenu2X() {
	free(menu);
	free(s);
}

void GMenu2X::drawFPS() {
	menu->write( s->raw, fps, 270,5);
}

void GMenu2X::drawRun() {
	Surface launch("launching.png");
	launch.blit(s,27,91);
	if (menu->selLink()->icon.raw!=NULL)
		menu->selLink()->icon.blit(s,45,104);
	else
		generic.blit(s,45,104);
	menu->write( s->raw, "Launching "+menu->selLink()->title, 85, 116 );
	s->flip();
}

string GMenu2X::getExePath() {
	stringstream ss;
	ss << "/proc/" << getpid() << "/exe";
	string path;
	ss >> path;
	char buf[255];
	int l = readlink(path.c_str(),buf,255);
	path = buf;
	path = path.substr(0,l);
	l = path.rfind("/");
	return path.substr(0,l+1);
}

string GMenu2X::getDiskFree() {
	stringstream ss;
	string df = "";
	struct statfs b;

#ifdef GP2XDEV
	int ret = statfs("/mnt/sd", &b);
#else
	int ret = statfs("/mnt/usb", &b);
#endif
	if (ret==0) {
		ss << b.f_bfree*b.f_bsize/1048576 << "/" << b.f_blocks*b.f_bsize/1048576 << "MB";
		ss >> df;
	} else cout << "GMENU2X: statfs failed with error " << errno << endl;
	return df;
}
