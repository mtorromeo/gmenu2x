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

#ifndef GMENU2X_H
#define GMENU2X_H

#include <string>
#include <iostream>
#include "menu.h"
#include "surfacecollection.h"

#ifdef TARGET_GP2X
#include "joystick.h"
#endif

using std::string;

class GMenu2X;

typedef int (GMenu2X::*StatusFcn)();

struct MenuOption {
	string text;
	StatusFcn action;
};

class GMenu2X {
private:
	string path;
	string getExePath();
	string getDiskFree();
	SurfaceCollection sc;
	Surface *s;
	SFont *font;
	int cpuX;
	void drawRun();
	void drawScrollBar();
	void setClock(int mhz);
	void runLink();
	StatusFcn status;

#ifdef TARGET_GP2X
	Joystick joy;
	bool startquit;
#else
	SDL_Event event;
#endif

public:
	GMenu2X(int argc, char *argv[]);
	~GMenu2X();

	//Status functions
	int main();
	int options();

	void initBG();
	void write(SDL_Surface *s, string text, int x, int y);
	void writeCenter(SDL_Surface *s, string text, int x, int y);

	Menu* menu;
};

#endif
