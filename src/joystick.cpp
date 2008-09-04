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

Joystick::Joystick() {secondJoyID = -1;}

Joystick::Joystick(int joynum) {
	init(joynum);
}

Joystick::~Joystick() {
    if(SDL_JoystickOpened(0))
        SDL_JoystickClose(joystick[0]);
    if(secondJoyID != -1)
        if(SDL_JoystickOpened(secondJoyID))
            SDL_JoystickClose(joystick[1]);
}

void Joystick::init( int joynum ) {
    secondJoyID = -1;
	SDL_JoystickEventState(SDL_IGNORE);
	joystick[0] = SDL_JoystickOpen(joynum);
	numButtons[0] = SDL_JoystickNumButtons(joystick[0]);
	for (int x=0; x<numButtons[0]; x++) {
		buttons.push_back(false);
		joyTick.push_back(0);
		interval.push_back(0);
	}
}

void Joystick::initSecondJoy(int joynum){
	joystick[1] = SDL_JoystickOpen(joynum);
	numButtons[1] = SDL_JoystickNumButtons(joystick[0]);
	secondJoyID = joynum;
    for (int x=0; x<numButtons[0]; ++x)
        buttonMaps.push_back(0);
}

void Joystick::init(int joynum, int secondJoy){
    int numJoys = SDL_NumJoysticks();
    if(numJoys >= 1 || secondJoy == -1){
        if(numJoys < secondJoy)
            initSecondJoy(secondJoy);
        else
            initSecondJoy(1);
    }
}

void Joystick::update() {
	SDL_JoystickUpdate();
	Uint32 tick = SDL_GetTicks();
	for (int x=0; x<numButtons[0]; x++) {
		buttons[x] = false;
		if (SDL_JoystickGetButton(joystick[0],x)) {
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

int Joystick::getMappedButton(int button){
    //  Check button exists
    if(button < numButtons[1])
        return buttonMaps[button];
    return -1;  //  Invalid button
}

bool Joystick::operator [](int button) {
	if (button<0 || button>=numButtons[0]) return false;
	return buttons[button];
}

bool Joystick::isDown(int button) {
    if(secondJoyID != -1)
        return SDL_JoystickGetButton(joystick[0],button) || SDL_JoystickGetButton(joystick[1],getMappedButton(button));
    return SDL_JoystickGetButton(joystick[0],button);
}
