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

Joystick::Joystick() {
	secondJoyID = -1;
}

Joystick::Joystick(int joynum, int joynum2) {
	init(joynum, joynum2);
}

Joystick::~Joystick() {
	if(SDL_JoystickOpened(0))
		SDL_JoystickClose(joystick[0]);
	if (secondJoyID != -1 && SDL_JoystickOpened(secondJoyID))
		SDL_JoystickClose(joystick[1]);
}

void Joystick::init( int joynum, int joynum2 ) {
	SDL_JoystickEventState(SDL_IGNORE);
	joystick[0] = SDL_JoystickOpen(joynum);
	numButtons[0] = SDL_JoystickNumButtons(joystick[0]);
	for (int x=0; x<numButtons[0]; x++) {
		buttons.push_back(false);
		joyTick.push_back(0);
		interval.push_back(0);
	}

	if (joynum2 != -1 && joynum2 < SDL_NumJoysticks()) {
		joystick[1] = SDL_JoystickOpen(joynum2);
		numButtons[1] = SDL_JoystickNumButtons(joystick[0]);
		secondJoyID = joynum2;
		JoyMap undef = {-1,-1,-1};
		for (int x=0; x<numButtons[0]; ++x)
			mappings.push_back(undef);
	} else {
		secondJoyID = -1;
	}
}

void Joystick::update() {
	SDL_JoystickUpdate();
	Uint32 tick = SDL_GetTicks();
	for (int x=0; x<numButtons[0]; x++) {
		buttons[x] = false;
		if (isDown(x)) {
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
	return numButtons[0];
}

void Joystick::setInterval(int ms, int button) {
	if (button<0)
		for (int x=0; x<numButtons[0]; x++)
			interval[x] = ms;
	else
		interval[button] = ms;
}

JoyMap Joystick::getButtonMapping(int button){
	// Check button exists
	if (button < mappings.size())
		return mappings[button];
	JoyMap undef = {-1,-1,-1};
	return undef; //  Invalid button
}

bool Joystick::operator[](int button) {
	if (button<0 || button>=numButtons[0]) return false;
	return buttons[button];
}

bool Joystick::isDown(int button) {
	if (SDL_JoystickGetButton(joystick[0], button)) return true;

	if (secondJoyID != -1) {
		JoyMap map = getButtonMapping(button);

		switch (map.type) {
			case Joystick::MAPPING_TYPE_BUTTON:
				return SDL_JoystickGetButton(joystick[1], map.num);
			break;
			case Joystick::MAPPING_TYPE_AXYS: {
				int axyspos = SDL_JoystickGetAxis(joystick[1], map.num);
				if (map.treshold<0)
					return axyspos < map.treshold;
				else
					return axyspos > map.treshold;
			} break;
			default:
				return false;
		}
	}

	return false;
}
