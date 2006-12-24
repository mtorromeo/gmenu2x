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
#include "menusettingstring.h"
#include "inputdialog.h"
#include "utilities.h"

using namespace std;

MenuSettingString::MenuSettingString(GMenu2X *gmenu2x, string name, string description, string *value)
	: MenuSetting(gmenu2x,name,description) {
	this->gmenu2x = gmenu2x;
	_value = value;
	originalValue = *value;
}

void MenuSettingString::draw(int y) {
	MenuSetting::draw(y);
	gmenu2x->s->write( gmenu2x->font, value(), 155, y+9, SFontHAlignLeft, SFontVAlignMiddle );
}

#ifdef TARGET_GP2X
#include "gp2x.h"

void MenuSettingString::manageInput() {
	if ( gmenu2x->joy[GP2X_BUTTON_X] ) setValue("");
	if ( gmenu2x->joy[GP2X_BUTTON_B] ) {
		InputDialog id(gmenu2x,description,value());
		if (id.exec()) setValue(id.input);
	}
}
#else
void MenuSettingString::manageInput() {
	if ( gmenu2x->event.key.keysym.sym==SDLK_BACKSPACE ) setValue("");
	if ( gmenu2x->event.key.keysym.sym==SDLK_RETURN ) {
		InputDialog id(gmenu2x,description,value());
		if (id.exec()) setValue(id.input);
	}
}
#endif

void MenuSettingString::setValue(string value) {
	*_value = value;
}

string MenuSettingString::value() {
	return *_value;
}

void MenuSettingString::adjustInput() {}

void MenuSettingString::drawSelected(int) {
	gmenu2x->drawButton(gmenu2x->s, "x", gmenu2x->tr["Clear"],
	gmenu2x->drawButton(gmenu2x->s, "b", gmenu2x->tr["Edit"], 5));
}

bool MenuSettingString::edited() {
	return originalValue != value();
}
