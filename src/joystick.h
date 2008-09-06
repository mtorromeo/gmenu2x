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
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

using std::vector;

typedef struct {
	int type;
	int num;
	int treshold;
} JoyMap;

/**
Manages the joystick

	@author Massimiliano Torromeo <massimiliano.torromeo@gmail.com>
*/
class Joystick {
private:
	void initSecondJoy(int joyNum);
	JoyMap getButtonMapping(int button);    //  returns the USBJoy button mapped at this GP2X button
	int secondJoyID;
	int numButtons[2];
	vector<Uint32> joyTick;
	vector<Uint32> interval;

public:
	static const int MAPPING_TYPE_UNDEFINED = -1;
	static const int MAPPING_TYPE_BUTTON = 0;
	static const int MAPPING_TYPE_AXYS = 1;

	Joystick();
	Joystick(int joynum, int joynum2 = -1);
	~Joystick();

	void init(int joynum, int joynum2 = -1);

	SDL_Joystick *joystick[2];
	vector<bool> buttons;   //  We only need the one set of buttons since we want the USBJoy to complement the GP2XJoy
	vector<JoyMap> mappings; //  Stores the mapped buttons of USBJoy

	void update();
	int count();
	void setInterval(int ms, int button = -1);
	bool operator[](int button);
	bool isDown(int button);
};

#endif
