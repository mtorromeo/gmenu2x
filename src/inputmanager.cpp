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
#include "inputmanager.h"
#include "utilities.h"

using namespace std;

InputManager::InputManager() {}

InputManager::~InputManager() {
	for (uint x=0; x<joysticks.size(); x++)
		if(SDL_JoystickOpened(x))
			SDL_JoystickClose(joysticks[x]);
}

void InputManager::init(string conffile) {
	SDL_JoystickEventState(SDL_IGNORE);

	int numJoy = SDL_NumJoysticks();
	for (int x=0; x<numJoy; x++) {
		SDL_Joystick *joy = SDL_JoystickOpen(x);
		if (joy) {
#ifdef DEBUG
			cout << "Initialized joystick: " << SDL_JoystickName(x) << endl;
#endif
			joysticks.push_back(joy);
		}
#ifdef DEBUG
		else cout << "Failed to initialize joystick: " << x << endl;
#endif
	}

	setActionsCount(14);

	if (fileExists(conffile)) {
		ifstream inf(conffile.c_str(), ios_base::in);
		if (inf.is_open()) {
			string line, name, value;
			stringstream ss;
			string::size_type pos;
			vector<string> values;

			while (getline(inf, line, '\n')) {
				pos = line.find("=");
				name = trim(line.substr(0,pos));
				value = trim(line.substr(pos+1,line.length()));
				int action = -1;

				if (name=="up") action = ACTION_UP;
				else if (name=="down") action = ACTION_DOWN;
				else if (name=="left") action = ACTION_LEFT;
				else if (name=="right") action = ACTION_RIGHT;
				else if (name=="a") action = ACTION_A;
				else if (name=="b") action = ACTION_B;
				else if (name=="x") action = ACTION_X;
				else if (name=="y") action = ACTION_Y;
				else if (name=="l") action = ACTION_L;
				else if (name=="r") action = ACTION_R;
				else if (name=="start") action = ACTION_START;
				else if (name=="select") action = ACTION_SELECT;
				else if (name=="volup") action = ACTION_VOLUP;
				else if (name=="voldown") action = ACTION_VOLDOWN;

				if (action >= 0) {
					split(values, value, ",");
					if (values.size() >= 3) {

						if (values[0] == "joystickbutton") {
							InputMap map;
							map.type = InputManager::MAPPING_TYPE_BUTTON;
							map.num = atoi(values[1].c_str());
							map.value = atoi(values[2].c_str());
							map.treshold = 0;
							mappings[action].push_back(map);
						} else if (values[0] == "joystickaxys" && values.size()==4) {
							InputMap map;
							map.type = InputManager::MAPPING_TYPE_AXYS;
							map.num = atoi(values[1].c_str());
							map.value = atoi(values[2].c_str());
							map.treshold = atoi(values[3].c_str());
							mappings[action].push_back(map);
						}

					}
				}
			}
			inf.close();
		}
	}
}

void InputManager::setActionsCount(int count) {
	actions.clear();
	actionTick.clear();
	interval.clear();
	for (int x=0; x<count; x++) {
		actions.push_back(false);
		actionTick.push_back(0);
		interval.push_back(0);
		MappingList maplist;
		mappings.push_back(maplist);
	}
}

void InputManager::update() {
	SDL_JoystickUpdate();
	Uint32 tick = SDL_GetTicks();
	for (uint x=0; x<actions.size(); x++) {
		actions[x] = false;
		if (isActive(x)) {
			if (tick-actionTick[x]>interval[x]) {
				actions[x] = true;
				actionTick[x] = tick;
			}
		} else {
			actionTick[x] = 0;
		}
	}
}

int InputManager::count() {
	return actions.size();
}

void InputManager::setInterval(int ms, int action) {
	if (action<0)
		for (uint x=0; x<interval.size(); x++)
			interval[x] = ms;
	else if ((uint)action < interval.size())
		interval[action] = ms;
}

bool InputManager::operator[](int action) {
	if (action<0 || (uint)action>=actions.size()) return false;
	return actions[action];
}

bool InputManager::isActive(int action) {
	for (uint x=0; x<mappings[action].size(); x++) {
		InputMap map = mappings[action][x];

		switch (map.type) {
			case InputManager::MAPPING_TYPE_BUTTON:
				return map.num < joysticks.size() && SDL_JoystickGetButton(joysticks[map.num], map.value);
			break;
			case InputManager::MAPPING_TYPE_AXYS:
				if (map.num < joysticks.size()) {
					int axyspos = SDL_JoystickGetAxis(joysticks[map.num], map.value);
					if (map.treshold<0 && axyspos < map.treshold) return true;
					if (map.treshold>0 && axyspos > map.treshold) return true;
				}
			break;
		}
	}

	return false;
}
