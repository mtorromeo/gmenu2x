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
#include "joystick.h"

using namespace std;

Joystick::Joystick(int joynum) {
	SDL_JoystickEventState(SDL_IGNORE);
	joystick = SDL_JoystickOpen(joynum);
	cout << "GMENU2X: Joystick " << (joystick!=NULL) << endl;
	numButtons = SDL_JoystickNumButtons(joystick);
	cout << "GMENU2X: " << numButtons << " buttons" << endl;
	for (int x=0; x<numButtons; x++) {
		buttons.push_back(false);
		joyTick.push_back(0);
		interval.push_back(0);
	}
	cout << "GMENU2X: Joystick initialized" << endl;
}

Joystick::~Joystick() {
	SDL_JoystickClose(joystick);
}

void Joystick::update() {
	SDL_JoystickUpdate();
	Uint32 tick = SDL_GetTicks();
	for (int x=0; x<numButtons; x++) {
		buttons[x] = false;
		if (SDL_JoystickGetButton(joystick,x)) {
			if (tick-joyTick[x]>interval[x]) {
				buttons[x] = true;
				joyTick[x] = tick;
			}
		} else {
			joyTick[x] = 0;
		}
	}
}

int Joystick::count() {
	return numButtons;
}

void Joystick::setInterval(int ms, int button) {
	if (button<0)
		for (int x=0; x<numButtons; x++)
			interval[x] = ms;
	else
		interval[button] = ms;
}

bool Joystick::operator [](int button) {
	if (button<0 || button>=numButtons) return false;
	return buttons[button];
}
