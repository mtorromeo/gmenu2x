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
	
	btnInc = new IconButton(gmenu2x, "skin:imgs/buttons/y.png");
	btnInc->setSize(16, 16);
	btnInc->setAction(MakeDelegate(this, &MenuSettingInt::inc));
	
	btnDec = new IconButton(gmenu2x, "skin:imgs/buttons/x.png");
	btnDec->setSize(16, 16);
	btnDec->setAction(MakeDelegate(this, &MenuSettingInt::dec));
	
	btnInc2 = new IconButton(gmenu2x, "skin:imgs/buttons/right.png");
	btnInc2->setSize(16, 16);
	btnInc2->setAction(MakeDelegate(this, &MenuSettingInt::inc));
	
	btnDec2 = new IconButton(gmenu2x, "skin:imgs/buttons/left.png");
	btnDec2->setSize(16, 16);
	btnDec2->setAction(MakeDelegate(this, &MenuSettingInt::dec));
}

void MenuSettingInt::draw(int y) {
	MenuSetting::draw(y);
	gmenu2x->s->write( gmenu2x->font, strvalue, 155, y+6, SFontHAlignLeft, SFontVAlignMiddle );
}

void MenuSettingInt::handleTS() {
	btnInc->handleTS();
	btnDec->handleTS();
	btnInc2->handleTS();
	btnDec2->handleTS();
}

void MenuSettingInt::manageInput() {
#ifdef TARGET_GP2X
#include "gp2x.h"
	if ( gmenu2x->joy[GP2X_BUTTON_LEFT ] || gmenu2x->joy[GP2X_BUTTON_X] ) dec();
	if ( gmenu2x->joy[GP2X_BUTTON_RIGHT] || gmenu2x->joy[GP2X_BUTTON_Y] ) inc();
#else
	if ( gmenu2x->event.key.keysym.sym==SDLK_LEFT ) dec();
	if ( gmenu2x->event.key.keysym.sym==SDLK_RIGHT ) inc();
#endif
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
	gmenu2x->joy.setInterval(30, GP2X_BUTTON_LEFT );
	gmenu2x->joy.setInterval(30, GP2X_BUTTON_RIGHT);
#endif
}

void MenuSettingInt::drawSelected(int) {
	gmenu2x->drawButton(btnInc, gmenu2x->tr["Increase value"],
	gmenu2x->drawButton(btnInc2, "",
	gmenu2x->drawButton(btnDec, gmenu2x->tr["Decrease value"],
	gmenu2x->drawButton(btnDec2, "", 5)-10))-10);
}

bool MenuSettingInt::edited() {
	return originalValue != value();
}
