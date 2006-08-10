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

using std::string;

class GMenu2X {
private:
	string path;
	string getExePath();
	string getDiskFree();
	SurfaceCollection sc;
	Surface *s;
	SFont *font;
	string fps;
	int cpuX;
	void drawFPS();
	void drawRun();
	void setClock(int mhz);
	void runLink();

public:
	GMenu2X();
	~GMenu2X();

	void initBG();
	void write(SDL_Surface *s, string text, int x, int y);
	void writeCenter(SDL_Surface *s, string text, int x, int y);

	Menu* menu;
};

#endif
