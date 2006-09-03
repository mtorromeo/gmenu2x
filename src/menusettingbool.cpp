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
#include "menusettingbool.h"
#include "utilities.h"
#include <sstream>

using namespace std;

MenuSettingBool::MenuSettingBool(GMenu2X *gmenu2x, string name, string description, bool *value)
	: MenuSetting(gmenu2x,name,description) {
	this->gmenu2x = gmenu2x;
	_value = value;
	this->setValue(this->value());
}

void MenuSettingBool::draw(int y) {
	MenuSetting::draw(y);
	gmenu2x->write( gmenu2x->s->raw, strvalue, 165, y );
}

#ifdef TARGET_GP2X
#include "gp2x.h"

void MenuSettingBool::manageInput() {
	if ( gmenu2x->joy[GP2X_BUTTON_B] ) setValue(!value());
}
#else
void MenuSettingBool::manageInput() {
	if ( gmenu2x->event.key.keysym.sym==SDLK_RETURN ) setValue(!value());
}
#endif

void MenuSettingBool::setValue(bool value) {
	*_value = value;
	strvalue = value ? "ON" : "OFF";
}

bool MenuSettingBool::value() {
	return *_value;
}

void MenuSettingBool::adjustInput() {}

void MenuSettingBool::drawSelected(int) {
	gmenu2x->drawButton(gmenu2x->s, "B", "Switch", 10);
}
