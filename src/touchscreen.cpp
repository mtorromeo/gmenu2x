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

#include <unistd.h>
#include <iostream>

#include "touchscreen.h"

using namespace std;

Touchscreen::Touchscreen() {
	wm97xx = 0;
	calibrated = false;
	wasPressed = false;
	handled = false;
	x = 0;
	y = 0;
}

Touchscreen::~Touchscreen() {
	if (wm97xx) deinit();
}

bool Touchscreen::init() {
#ifdef TARGET_GP2X
	wm97xx = open("/dev/touchscreen/wm97xx", O_RDONLY|O_NOCTTY);
#endif
	return initialized();
}

bool Touchscreen::initialized() {
#ifdef TARGET_GP2X
	return wm97xx>0;
#else
	return true;
#endif
}

void Touchscreen::deinit() {
#ifdef TARGET_GP2X
	close(wm97xx);
	wm97xx = 0;
#endif
}

void Touchscreen::calibrate() {
	if (event.pressure==0) {
		calibX = ((event.x-200)*320/3750)/4;
		calibY = (((event.y-200)*240/3750))/4;
		calibrated = true;
	}
}

bool Touchscreen::poll() {
	wasPressed = pressed();
#ifdef TARGET_GP2X
	read(wm97xx, &event, sizeof(TS_EVENT));
	if (!calibrated) calibrate();

	if (event.pressure>0) {
		x = ((event.x-200)*320/3750)-calibX;
		y = (240 - ((event.y-200)*240/3750))-calibY;
	}
#else
	SDL_PumpEvents();
	int mx, my;
	if (SDL_GetMouseState(&mx,&my) && SDL_BUTTON(1)) {
		x = mx;
		y = my;
		event.pressure = 1;
	} else {
		event.pressure = 0;
	}
#endif
	handled = false;
	return pressed();
}

void Touchscreen::setHandled() {
	wasPressed = false;
	handled = true;
}

bool Touchscreen::pressed() {
	return !handled && event.pressure>0;
}

bool Touchscreen::released() {
	return !pressed() && wasPressed;
}

bool Touchscreen::inRect(SDL_Rect r) {
	return !handled && (y>=r.y) && (y<=r.y+r.h) && (x>=r.x) && (x<=r.x+r.w);
}

bool Touchscreen::inRect(int x, int y, int w, int h) {
	SDL_Rect rect = {x,y,w,h};
	return inRect(rect);
}
