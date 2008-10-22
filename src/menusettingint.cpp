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
using namespace fastdelegate;

MenuSettingInt::MenuSettingInt(GMenu2X *gmenu2x, string name, string description, int *value, int min, int max)
	: MenuSetting(gmenu2x,name,description) {
	this->gmenu2x = gmenu2x;
	_value = value;
	originalValue = *value;
	this->min = min;
	this->max = max;
	setValue(this->value());

	//Delegates
	ButtonAction actionInc = MakeDelegate(this, &MenuSettingInt::inc);
	ButtonAction actionDec = MakeDelegate(this, &MenuSettingInt::dec);

	btnInc = new IconButton(gmenu2x, "skin:imgs/buttons/y.png", gmenu2x->tr["Increase value"]);
	btnInc->setAction(actionInc);

	btnDec = new IconButton(gmenu2x, "skin:imgs/buttons/x.png", gmenu2x->tr["Decrease value"]);
	btnDec->setAction(actionDec);

	btnInc2 = new IconButton(gmenu2x, "skin:imgs/buttons/right.png");
	btnInc2->setAction(actionInc);

	btnDec2 = new IconButton(gmenu2x, "skin:imgs/buttons/left.png");
	btnDec2->setAction(actionDec);
}

void MenuSettingInt::draw(int y) {
	MenuSetting::draw(y);
	gmenu2x->s->write( gmenu2x->font, strvalue, 155, y+gmenu2x->font->getHalfHeight(), SFontHAlignLeft, SFontVAlignMiddle );
}

void MenuSettingInt::handleTS() {
	btnInc->handleTS();
	btnDec->handleTS();
	btnInc2->handleTS();
	btnDec2->handleTS();
}

void MenuSettingInt::manageInput() {
	if ( gmenu2x->input[ACTION_LEFT ] || gmenu2x->input[ACTION_X] ) dec();
	if ( gmenu2x->input[ACTION_RIGHT] || gmenu2x->input[ACTION_Y] ) inc();
}

void MenuSettingInt::inc() {
	setValue(value()+1);
}

void MenuSettingInt::dec() {
	setValue(value()-1);
}

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
	gmenu2x->input.setInterval(30, ACTION_LEFT );
	gmenu2x->input.setInterval(30, ACTION_RIGHT);
#endif
}

void MenuSettingInt::drawSelected(int) {
	gmenu2x->drawButton(btnInc,
	gmenu2x->drawButton(btnInc2,
	gmenu2x->drawButton(btnDec,
	gmenu2x->drawButton(btnDec2)-10))-10);
}

bool MenuSettingInt::edited() {
	return originalValue != value();
}
