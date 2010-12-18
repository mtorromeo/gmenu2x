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

#include "debug.h"
#include "inputmanager.h"
#include "utilities.h"

#include <iostream>
#include <fstream>

using namespace std;


InputManager::~InputManager() {
	for (uint x=0; x<joysticks.size(); x++)
		if(SDL_JoystickOpened(x))
			SDL_JoystickClose(joysticks[x]);
}


void InputManager::init(const string &conffile) {
	initJoysticks();
	if (!readConfFile(conffile))
		ERROR("InputManager initialization from config file failed.\n");
}


void InputManager::initJoysticks() {
	//SDL_JoystickEventState(SDL_IGNORE);

	int numJoy = SDL_NumJoysticks();
	INFO("%d joysticks found\n", numJoy);
	for (int x=0; x<numJoy; x++) {
		SDL_Joystick *joy = SDL_JoystickOpen(x);
		if (joy) {
			INFO("Initialized joystick: '%s'\n", SDL_JoystickName(x));
			joysticks.push_back(joy);
		}
		else WARNING("Failed to initialize joystick: %i\n", x);
	}
}


bool InputManager::readConfFile(const string &conffile) {
	setActionsCount(18);

	if (!fileExists(conffile)) {
		ERROR("File not found: %s\n", conffile.c_str());
		return false;
	}

	ifstream inf(conffile.c_str(), ios_base::in);
	if (!inf.is_open()) {
		ERROR("Could not open %s\n", conffile.c_str());
		return false;
	}

	int action, linenum = 0;
	string line, name, value;
	string::size_type pos;
	vector<string> values;

	while (getline(inf, line, '\n')) {
		linenum++;
		pos = line.find("=");
		name = trim(line.substr(0,pos));
		value = trim(line.substr(pos+1,line.length()));

		if (name=="up")                action = UP;
		else if (name=="down")         action = DOWN;
		else if (name=="left")         action = LEFT;
		else if (name=="right")        action = RIGHT;
		else if (name=="modifier")     action = MODIFIER;
		else if (name=="confirm")      action = CONFIRM;
		else if (name=="cancel")       action = CANCEL;
		else if (name=="manual")       action = MANUAL;
		else if (name=="dec")          action = DEC;
		else if (name=="inc")          action = INC;
		else if (name=="section_prev") action = SECTION_PREV;
		else if (name=="section_next") action = SECTION_NEXT;
		else if (name=="pageup")       action = PAGEUP;
		else if (name=="pagedown")     action = PAGEDOWN;
		else if (name=="settings")     action = SETTINGS;
		else if (name=="menu")         action = MENU;
		else if (name=="volup")        action = VOLUP;
		else if (name=="voldown")      action = VOLDOWN;
		else {
			ERROR("%s:%d Unknown action '%s'.\n", conffile.c_str(), linenum, name.c_str());
			return false;
		}

		split(values, value, ",");
		if (values.size() >= 2) {

			if (values[0] == "joystickbutton" && values.size()==3) {
				InputMap map;
				map.type = InputManager::MAPPING_TYPE_BUTTON;
				map.num = atoi(values[1].c_str());
				map.value = atoi(values[2].c_str());
				map.treshold = 0;
				actions[action].maplist.push_back(map);
			} else if (values[0] == "joystickaxis" && values.size()==4) {
				InputMap map;
				map.type = InputManager::MAPPING_TYPE_AXIS;
				map.num = atoi(values[1].c_str());
				map.value = atoi(values[2].c_str());
				map.treshold = atoi(values[3].c_str());
				actions[action].maplist.push_back(map);
			} else if (values[0] == "keyboard") {
				InputMap map;
				map.type = InputManager::MAPPING_TYPE_KEYPRESS;
				map.value = atoi(values[1].c_str());
				actions[action].maplist.push_back(map);
			} else {
				ERROR("%s:%d Invalid syntax or unsupported mapping type '%s'.\n", conffile.c_str(), linenum, value.c_str());
				return false;
			}

		} else {
			ERROR("%s:%d Every definition must have at least 2 values (%s).\n", conffile.c_str(), linenum, value.c_str());
			return false;
		}
	}
	inf.close();
	return true;
}


void InputManager::setActionsCount(int count) {
	actions.clear();
	for (int x=0; x<count; x++) {
		InputManagerAction action;
		action.active = false;
		action.pressed = false;
		action.interval = 0;
		action.timer = NULL;
		actions.push_back(action);
	}
}


bool InputManager::update(bool wait) {
	bool anyactions = false;
	SDL_JoystickUpdate();

	events.clear();
	SDL_Event event;

	if (wait) {
		SDL_WaitEvent(&event);
		SDL_Event evcopy = event;
		events.push_back(evcopy);
	}
	while (SDL_PollEvent(&event)) {
		SDL_Event evcopy = event;
		events.push_back(evcopy);
	}

	for (uint x=0; x<actions.size(); x++) {
		int status = actionStatus(x);
		actions[x].active = false;
		if (status == IM_ACTIVE) {
			actions[x].active = true;
			actions[x].pressed = true;
			anyactions = true;

			if (actions[x].timer == NULL) {
				// Set a timer to repeat the event in actions[x].interval milliseconds
				RepeatEventData *data = new RepeatEventData();
				data->im = this;
				data->action = x;
				actions[x].timer = SDL_AddTimer(actions[x].interval, checkRepeat, data);
			}
		} else if (status == IM_INACTIVE) {
			actions[x].pressed = false;
			actions[x].timer = NULL;
		}
	}

	return anyactions;
}


void InputManager::dropEvents() {
	for (uint x=0; x<actions.size(); x++) {
		actions[x].active = false;
		actions[x].pressed = false;
		if (actions[x].timer != NULL) {
			SDL_RemoveTimer(actions[x].timer);
			actions[x].timer = NULL;
		}
	}
}


Uint32 InputManager::checkRepeat(Uint32 interval, void *_data) {
	RepeatEventData *data = (RepeatEventData *)_data;
	InputManager *im = (class InputManager*)data->im;
	SDL_JoystickUpdate();
	if (im->actions[data->action].pressed) {
		im->actions[data->action].pressed = false;
		SDL_PushEvent( im->fakeEventForAction(data->action) );
		return interval;
	} else {
		im->actions[data->action].timer = NULL;
		return 0;
	}
}


SDL_Event *InputManager::fakeEventForAction(int action) {
	MappingList mapList = actions[action].maplist;
	// Take the first mapping. We only need one of them.
	InputMap map = *mapList.begin();

	SDL_Event *event = new SDL_Event();
	switch (map.type) {
		case InputManager::MAPPING_TYPE_BUTTON:
			event->type = SDL_JOYBUTTONDOWN;
			event->jbutton.type = SDL_JOYBUTTONDOWN;
			event->jbutton.which = map.num;
			event->jbutton.button = map.value;
			event->jbutton.state = SDL_PRESSED;
		break;
		case InputManager::MAPPING_TYPE_AXIS:
			event->type = SDL_JOYAXISMOTION;
			event->jaxis.type = SDL_JOYAXISMOTION;
			event->jaxis.which = map.num;
			event->jaxis.axis = map.value;
			event->jaxis.value = map.treshold;
		break;
		case InputManager::MAPPING_TYPE_KEYPRESS:
			event->type = SDL_KEYDOWN;
			event->key.keysym.sym = (SDLKey)map.value;
		break;
	}
	return event;
}


int InputManager::count() {
	return actions.size();
}


void InputManager::setInterval(int ms, int action) {
	if (action<0)
		for (uint x=0; x<actions.size(); x++)
			actions[x].interval = ms;
	else if ((uint)action < actions.size())
		actions[action].interval = ms;
}


bool InputManager::operator[](int action) {
	if (action<0 || (uint)action>=actions.size()) return false;
	return actions[action].active;
}


int InputManager::actionStatus(int action) {
	MappingList mapList = actions[action].maplist;
	for (MappingList::const_iterator it = mapList.begin(); it !=mapList.end(); ++it) {
		InputMap map = *it;

		switch (map.type) {
			case InputManager::MAPPING_TYPE_BUTTON:
				if (map.num < joysticks.size())
					for (uint ex=0; ex<events.size(); ex++) {
						if ((events[ex].type == SDL_JOYBUTTONDOWN || events[ex].type == SDL_JOYBUTTONUP) && events[ex].jbutton.which == map.num && events[ex].jbutton.button == map.value)
							return events[ex].type == SDL_JOYBUTTONDOWN ? IM_ACTIVE : IM_INACTIVE;
					}
			break;
			case InputManager::MAPPING_TYPE_AXIS:
				if (map.num < joysticks.size())
					for (uint ex=0; ex<events.size(); ex++) {
						if (events[ex].type == SDL_JOYAXISMOTION && events[ex].jaxis.which == map.num && events[ex].jaxis.axis == map.value) {
							if (map.treshold<0 && events[ex].jaxis.value <= map.treshold) return actions[action].pressed ? IM_UNCHANGED : IM_ACTIVE;
							if (map.treshold>0 && events[ex].jaxis.value >= map.treshold) return actions[action].pressed ? IM_UNCHANGED : IM_ACTIVE;
							return IM_INACTIVE;
						}
					}
			break;
			case InputManager::MAPPING_TYPE_KEYPRESS:
					//INFO("KEYPRESS: %d\n", events[ex].key.keysym.sym);
				for (uint ex=0; ex<events.size(); ex++) {
					if ((events[ex].type == SDL_KEYDOWN || events[ex].type == SDL_KEYUP) && events[ex].key.keysym.sym == map.value)
						return events[ex].type == SDL_KEYDOWN ? IM_ACTIVE : IM_INACTIVE;
				}
			break;
		}
	}

	return IM_UNCHANGED;
}


bool InputManager::isActive(int action) {
	switch (actionStatus(action)) {
		case IM_ACTIVE:
			return true;
		case IM_INACTIVE:
			return false;
		default:
			return actions[action].active;
	}
}
