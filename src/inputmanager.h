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
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

enum actions {
	UP, DOWN, LEFT, RIGHT,
	CONFIRM, CANCEL, MANUAL, MODIFIER,
	SECTION_PREV, SECTION_NEXT,
	INC, DEC,
	PAGEUP, PAGEDOWN,
	SETTINGS, MENU,
	VOLUP, VOLDOWN
};

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>

using std::vector;
using std::string;

typedef struct {
	int type;
	uint num;
	int value;
	int treshold;
} InputMap;

typedef vector<InputMap> MappingList;
typedef vector<SDL_Event> SDLEventList;

typedef struct {
	bool active;
	int interval;
	long last;
	MappingList maplist;
	SDL_TimerID timer;
} InputManagerAction;

enum InputManagerActionState {
	IM_INACTIVE,
	IM_ACTIVE,
	IM_UNCHANGED
};

/**
Manages all input peripherals
@author Massimiliano Torromeo <massimiliano.torromeo@gmail.com>
*/
class InputManager {
private:
	InputMap getInputMapping(int action);
	SDLEventList events;
	SDL_TimerID wakeUpTimer;

	vector <SDL_Joystick*> joysticks;
	vector <InputManagerAction> actions;

	static Uint32 checkRepeat(Uint32 interval, void *_data);
	static Uint32 wakeUp(Uint32 interval, void *_data);
	SDL_Event *fakeEventForAction(int action);

public:
	static const int MAPPING_TYPE_UNDEFINED = -1;
	static const int MAPPING_TYPE_BUTTON = 0;
	static const int MAPPING_TYPE_AXIS = 1;
	static const int MAPPING_TYPE_KEYPRESS = 2;

	static const int SDL_WAKEUPEVENT = SDL_USEREVENT+1;

	InputManager();
	~InputManager();
	void init(const string &conffile);
	void initJoysticks();
	bool readConfFile(const string &conffile = "input.conf");

	bool update(bool wait=true);
	void dropEvents();
	int count();
	void setActionsCount(int count);
	void setInterval(int ms, int action = -1);
	void setWakeUpInterval(int ms);
	bool operator[](int action);
	bool isActive(int action);
};

typedef struct {
	int action;
	InputManager *im;
} RepeatEventData;

#endif
