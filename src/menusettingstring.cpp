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
using namespace fastdelegate;

MenuSettingString::MenuSettingString(GMenu2X *gmenu2x, string name, string description, string *value, string diagTitle, string diagIcon)
	: MenuSetting(gmenu2x,name,description) {
	this->gmenu2x = gmenu2x;
	_value = value;
	originalValue = *value;
	this->diagTitle = diagTitle;
	this->diagIcon = diagIcon;

	btnClear = new IconButton(gmenu2x, "skin:imgs/buttons/x.png", gmenu2x->tr["Clear"]);
	btnClear->setAction(MakeDelegate(this, &MenuSettingString::clear));

	btnEdit = new IconButton(gmenu2x, "skin:imgs/buttons/b.png", gmenu2x->tr["Edit"]);
	btnEdit->setAction(MakeDelegate(this, &MenuSettingString::edit));
}

void MenuSettingString::draw(int y) {
	MenuSetting::draw(y);
	gmenu2x->s->write( gmenu2x->font, value(), 155, y+6, SFontHAlignLeft, SFontVAlignMiddle );
}

void MenuSettingString::handleTS() {
	btnEdit->handleTS();
}

#ifdef TARGET_GP2X
#include "gp2x.h"

void MenuSettingString::manageInput() {
	if ( gmenu2x->joy[GP2X_BUTTON_X] ) clear();
	if ( gmenu2x->joy[GP2X_BUTTON_B] ) edit();
}
#else
void MenuSettingString::manageInput() {
	if ( gmenu2x->event.key.keysym.sym==SDLK_BACKSPACE ) clear();
	if ( gmenu2x->event.key.keysym.sym==SDLK_RETURN ) edit();
}
#endif

void MenuSettingString::setValue(string value) {
	*_value = value;
}

string MenuSettingString::value() {
	return *_value;
}

void MenuSettingString::adjustInput() {}

void MenuSettingString::clear() {
	setValue("");
}

void MenuSettingString::edit() {
	InputDialog id(gmenu2x,description,value(), diagTitle,diagIcon);
	if (id.exec()) setValue(id.input);
}

void MenuSettingString::drawSelected(int) {
	gmenu2x->drawButton(btnClear,
	gmenu2x->drawButton(btnEdit));
}

bool MenuSettingString::edited() {
	return originalValue != value();
}
