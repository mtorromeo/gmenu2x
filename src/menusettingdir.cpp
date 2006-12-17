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
#include "menusettingdir.h"
#include "dirdialog.h"
#include "utilities.h"

using namespace std;

MenuSettingDir::MenuSettingDir(GMenu2X *gmenu2x, string name, string description, string *value)
	: MenuSetting(gmenu2x,name,description) {
	this->gmenu2x = gmenu2x;
	_value = value;
	originalValue = *value;
}

void MenuSettingDir::draw(int y) {
	MenuSetting::draw(y);
	gmenu2x->s->write( gmenu2x->font, value(), 155, y+9, SFontHAlignLeft, SFontVAlignMiddle );
}

#ifdef TARGET_GP2X
#include "gp2x.h"

void MenuSettingDir::manageInput() {
	if ( gmenu2x->joy[GP2X_BUTTON_X] ) setValue("");
	if ( gmenu2x->joy[GP2X_BUTTON_B] ) {
		DirDialog dd(gmenu2x,description);
		if (dd.exec()) setValue( dd.path );
	}
}
#else
void MenuSettingDir::manageInput() {
	if ( gmenu2x->event.key.keysym.sym==SDLK_BACKSPACE ) setValue("");
	if ( gmenu2x->event.key.keysym.sym==SDLK_RETURN ) {
		DirDialog dd(gmenu2x,description);
		if (dd.exec()) setValue( dd.path );
	}
}
#endif

void MenuSettingDir::setValue(string value) {
	*_value = value;
}

string MenuSettingDir::value() {
	return *_value;
}

void MenuSettingDir::adjustInput() {}

void MenuSettingDir::drawSelected(int) {
	gmenu2x->drawButton(gmenu2x->s, "x", "Clear",
	gmenu2x->drawButton(gmenu2x->s, "b", "Select a directory", 5));
}

bool MenuSettingDir::edited() {
	return originalValue != value();
}
