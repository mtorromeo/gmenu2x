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
#include "menusettingint.h"
#include "utilities.h"
#include <sstream>

using namespace std;

MenuSettingInt::MenuSettingInt(GMenu2X *gmenu2x, string name, string description, int *value, int min, int max)
	: MenuSetting(gmenu2x,name,description) {
	this->gmenu2x = gmenu2x;
	_value = value;
	this->min = min;
	this->max = max;
	this->setValue(this->value());
}

void MenuSettingInt::draw(int y) {
	MenuSetting::draw(y);
	gmenu2x->write( gmenu2x->s->raw, strvalue, 165, y );
}

#ifdef TARGET_GP2X
#include "gp2x.h"

void MenuSettingInt::manageInput() {
	if ( gmenu2x->joy[GP2X_BUTTON_LEFT ] || gmenu2x->joy[GP2X_BUTTON_X] ) setValue(value()-1);
	if ( gmenu2x->joy[GP2X_BUTTON_RIGHT] || gmenu2x->joy[GP2X_BUTTON_Y] ) setValue(value()+1);
}
#else
void MenuSettingInt::manageInput() {
	if ( gmenu2x->event.key.keysym.sym==SDLK_LEFT ) setValue(value()-1);
	if ( gmenu2x->event.key.keysym.sym==SDLK_RIGHT ) setValue(value()+1);
}
#endif

void MenuSettingInt::setValue(int value) {
	*_value = constrain(value,min,max);
	stringstream ss;
	ss << *_value;
	strvalue = "";
	ss >> strvalue;
}

int MenuSettingInt::value() {
	return *_value;
}

void MenuSettingInt::adjustInput() {
#ifdef TARGET_GP2X
	gmenu2x->joy.setInterval(30, GP2X_BUTTON_LEFT );
	gmenu2x->joy.setInterval(30, GP2X_BUTTON_RIGHT);
#endif
}

void MenuSettingInt::drawSelected(int) {
	gmenu2x->drawButton(gmenu2x->s, "Y", "Increase value",
	gmenu2x->drawButton(gmenu2x->s, ">", "/",
	gmenu2x->drawButton(gmenu2x->s, "X", "Decrease value",
	gmenu2x->drawButton(gmenu2x->s, "<", "/", 10)-4))-4);
}
