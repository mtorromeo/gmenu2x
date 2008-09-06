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

#define ACTION_UP      0
#define ACTION_DOWN    1
#define ACTION_LEFT    2
#define ACTION_RIGHT   3
#define ACTION_A       4
#define ACTION_B       5
#define ACTION_X       6
#define ACTION_Y       7
#define ACTION_L       8
#define ACTION_R       9
#define ACTION_START   10
#define ACTION_SELECT  11
#define ACTION_VOLUP   12
#define ACTION_VOLDOWN 13

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

/**
Manages all input peripherals
@author Massimiliano Torromeo <massimiliano.torromeo@gmail.com>
*/
class InputManager {
private:
	InputMap getInputMapping(int action);
	vector<Uint32> actionTick;
	vector<Uint32> interval;

public:
	static const int MAPPING_TYPE_UNDEFINED = -1;
	static const int MAPPING_TYPE_BUTTON = 0;
	static const int MAPPING_TYPE_AXYS = 1;
	static const int MAPPING_TYPE_KEYPRESS = 2;

	InputManager();
	~InputManager();
	void init(string conffile = "input.conf");

	vector <SDL_Joystick*> joysticks;
	vector<bool> actions;
	vector<MappingList> mappings;

	void update();
	int count();
	void setActionsCount(int count);
	void setInterval(int ms, int action = -1);
	bool operator[](int action);
	bool isActive(int action);
};

#endif
