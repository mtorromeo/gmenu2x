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

	//Events
#ifdef TARGET_GP2X
	Joystick joy(0);
	joy.setInterval(150);
#else
	SDL_Event event;
	SDL_EnableKeyRepeat(1,150);
#endif

	bool quit = false, showFPS = false;
	int x, i, firstIcon = 0, lastIcon = 0;
	Uint32 lastFrame = SDL_GetTicks(), thisFrame, numFrames = 0;

	while (!quit) {
		menu->bg.blit(s,0,0);

		firstIcon = menu->selLinkIndex()-1;
		lastIcon = menu->selLinkIndex()+6;

		if (menu->selLink()!=NULL) {
			for (x=firstIcon; x<=lastIcon; x++) {
				i = x;
				while (i>=(int)menu->links.size()) i-=menu->links.size();
				while (i<0) i+=menu->links.size();
				if (menu->links[i]->icon.raw!=NULL)
					menu->links[i]->icon.blit(s,12,196-(x-menu->selLinkIndex())*36);
				else
					generic.blit(s,12,196-(x-menu->selLinkIndex())*36);
			}
			if (menu->selLink()->screen.raw!=NULL)
				menu->selLink()->screen.blit(s,55,10);
			menu->write( s->raw, menu->selLink()->title, 50, 199 );
			menu->write( s->raw, menu->selLink()->description, 50, 213 );
		}

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
		if ( joy[GP2X_BUTTON_DOWN  ] ) menu->decLinkIndex();
		if ( joy[GP2X_BUTTON_UP    ] ) menu->incLinkIndex();
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
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_SPACE ) showFPS = !showFPS;
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_DOWN   ) menu->decLinkIndex();
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_UP     ) menu->incLinkIndex();
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_q     ) menu->decSectionIndex();
			if ( event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_w     ) menu->incSectionIndex();
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
