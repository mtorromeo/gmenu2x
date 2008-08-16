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
#include "menusettingrgba.h"
#include <sstream>

using namespace std;
using namespace fastdelegate;

MenuSettingRGBA::MenuSettingRGBA(GMenu2X *gmenu2x, string name, string description, RGBAColor *value)
	: MenuSetting(gmenu2x,name,description) {
	selPart = 0;
	this->gmenu2x = gmenu2x;
	_value = value;
	originalValue = *value;
	this->setR(this->value().r);
	this->setG(this->value().g);
	this->setB(this->value().b);
	this->setA(this->value().a);

	btnDec = new IconButton(gmenu2x, "skin:imgs/buttons/x.png", gmenu2x->tr["Decrease"]);
	btnDec->setAction(MakeDelegate(this, &MenuSettingRGBA::dec));

	btnInc = new IconButton(gmenu2x, "skin:imgs/buttons/y.png", gmenu2x->tr["Increase"]);
	btnInc->setAction(MakeDelegate(this, &MenuSettingRGBA::inc));

	btnLeftComponent = new IconButton(gmenu2x, "skin:imgs/buttons/left.png");
	btnLeftComponent->setAction(MakeDelegate(this, &MenuSettingRGBA::leftComponent));

	btnRightComponent = new IconButton(gmenu2x, "skin:imgs/buttons/right.png", gmenu2x->tr["Change color component"]);
	btnRightComponent->setAction(MakeDelegate(this, &MenuSettingRGBA::rightComponent));
}

void MenuSettingRGBA::draw(int y) {
	this->y = y;
	MenuSetting::draw(y);
	gmenu2x->s->rectangle( 153, y+1, 11, 11, 0,0,0,255 );
	gmenu2x->s->box( 154, y+2, 9, 9, value() );
	gmenu2x->s->write( gmenu2x->font, "R: "+strR, 169, y+6, SFontHAlignLeft, SFontVAlignMiddle );
	gmenu2x->s->write( gmenu2x->font, "G: "+strG, 205, y+6, SFontHAlignLeft, SFontVAlignMiddle );
	gmenu2x->s->write( gmenu2x->font, "B: "+strB, 241, y+6, SFontHAlignLeft, SFontVAlignMiddle );
	gmenu2x->s->write( gmenu2x->font, "A: "+strA, 277, y+6, SFontHAlignLeft, SFontVAlignMiddle );
}

void MenuSettingRGBA::handleTS() {
	if (gmenu2x->ts.pressed())
		for (int i=0; i<4; i++)
			if (i!=selPart && gmenu2x->ts.inRect(166+i*36,y,36,14)) {
				selPart = i;
				i = 4;
			}

	btnDec->handleTS();
	btnInc->handleTS();
	btnLeftComponent->handleTS();
	btnRightComponent->handleTS();
}

#ifdef TARGET_GP2X
#include "gp2x.h"

void MenuSettingRGBA::manageInput() {
	if ( gmenu2x->joy[GP2X_BUTTON_Y    ]) inc();
	if ( gmenu2x->joy[GP2X_BUTTON_X    ]) dec();
	if ( gmenu2x->joy[GP2X_BUTTON_LEFT ]) leftComponent();
	if ( gmenu2x->joy[GP2X_BUTTON_RIGHT]) rightComponent();
}
#else
void MenuSettingRGBA::manageInput() {
	if ( gmenu2x->event.key.keysym.sym==SDLK_y    ) inc();
	if ( gmenu2x->event.key.keysym.sym==SDLK_x    ) dec();
	if ( gmenu2x->event.key.keysym.sym==SDLK_LEFT ) leftComponent();
	if ( gmenu2x->event.key.keysym.sym==SDLK_RIGHT) rightComponent();
}
#endif

void MenuSettingRGBA::dec() {
	setSelPart( constrain(getSelPart()-1,0,255) );
}

void MenuSettingRGBA::inc() {
	setSelPart( constrain(getSelPart()+1,0,255) );
}

void MenuSettingRGBA::leftComponent() {
	selPart = constrain(selPart-1,0,3);
}

void MenuSettingRGBA::rightComponent() {
	selPart = constrain(selPart+1,0,3);
}

void MenuSettingRGBA::setR(unsigned short r) {
	_value->r = r;
	stringstream ss;
	ss << r;
	ss >> strR;
}

void MenuSettingRGBA::setG(unsigned short g) {
	_value->g = g;
	stringstream ss;
	ss << g;
	ss >> strG;
}

void MenuSettingRGBA::setB(unsigned short b) {
	_value->b = b;
	stringstream ss;
	ss << b;
	ss >> strB;
}

void MenuSettingRGBA::setA(unsigned short a) {
	_value->a = a;
	stringstream ss;
	ss << a;
	ss >> strA;
}

void MenuSettingRGBA::setSelPart(unsigned short value) {
	switch (selPart) {
		default: case 0: setR(value); break;
		case 1: setG(value); break;
		case 2: setB(value); break;
		case 3: setA(value); break;
	}
}

RGBAColor MenuSettingRGBA::value() {
	return *_value;
}

unsigned short MenuSettingRGBA::getSelPart() {
	switch (selPart) {
		default: case 0: return value().r;
		case 1: return value().g;
		case 2: return value().b;
		case 3: return value().a;
	}
}

void MenuSettingRGBA::adjustInput() {
#ifdef TARGET_GP2X
	gmenu2x->joy.setInterval(30, GP2X_BUTTON_Y );
	gmenu2x->joy.setInterval(30, GP2X_BUTTON_X );
	gmenu2x->joy.setInterval(30, GP2X_BUTTON_L );
#endif
}

void MenuSettingRGBA::drawSelected(int y) {
	int x = 166+selPart*36;
	gmenu2x->s->box( x, y, 36, 14, gmenu2x->selectionColor );

	gmenu2x->drawButton(btnDec,
	gmenu2x->drawButton(btnInc,
	gmenu2x->drawButton(btnRightComponent,
	gmenu2x->drawButton(btnLeftComponent)-6)));
}

bool MenuSettingRGBA::edited() {
	return originalValue.r != value().r || originalValue.g != value().g || originalValue.b != value().b || originalValue.a != value().a;
}
