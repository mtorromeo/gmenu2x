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

MenuSettingRGBA::MenuSettingRGBA(GMenu2X *gmenu2x, string name, string description, RGBAColor *value)
	: MenuSetting(gmenu2x,name,description) {
	selPart = 0;
	this->gmenu2x = gmenu2x;
	_value = value;
	this->setR(this->value().r);
	this->setG(this->value().g);
	this->setB(this->value().b);
	this->setA(this->value().a);
}

void MenuSettingRGBA::draw(int y) {
	MenuSetting::draw(y);
	rectangleRGBA( gmenu2x->s->raw, 165, y, 177, y+12, 0,0,0,255 );
	boxRGBA( gmenu2x->s->raw, 165, y, 177, y+12, value() );
	gmenu2x->write( gmenu2x->s->raw, "R: "+strR, 183, y );
	gmenu2x->write( gmenu2x->s->raw, "G: "+strG, 218, y );
	gmenu2x->write( gmenu2x->s->raw, "B: "+strB, 253, y );
	gmenu2x->write( gmenu2x->s->raw, "A: "+strA, 288, y );
}

#ifdef TARGET_GP2X
#include "gp2x.h"

void MenuSettingRGBA::manageInput() {
	if ( gmenu2x->joy[GP2X_BUTTON_Y    ]) setSelPart( constrain(getSelPart()+1,0,255) );
	if ( gmenu2x->joy[GP2X_BUTTON_X    ]) setSelPart( constrain(getSelPart()-1,0,255) );
	if ( gmenu2x->joy[GP2X_BUTTON_LEFT ]) selPart = constrain(selPart-1,0,3);
	if ( gmenu2x->joy[GP2X_BUTTON_RIGHT]) selPart = constrain(selPart+1,0,3);
}
#else
void MenuSettingRGBA::manageInput() {
	if ( gmenu2x->event.key.keysym.sym==SDLK_y    ) setSelPart( constrain(getSelPart()+1,0,255) );
	if ( gmenu2x->event.key.keysym.sym==SDLK_x    ) setSelPart( constrain(getSelPart()-1,0,255) );
	if ( gmenu2x->event.key.keysym.sym==SDLK_LEFT ) selPart = constrain(selPart-1,0,3);
	if ( gmenu2x->event.key.keysym.sym==SDLK_RIGHT) selPart = constrain(selPart+1,0,3);
}
#endif

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
#endif
}

void MenuSettingRGBA::drawSelected(int y) {
	int x = 180+selPart*35;
	boxRGBA( gmenu2x->s->raw, x, y, x+34, y+16, gmenu2x->selectionColor );

	gmenu2x->drawButton(gmenu2x->s, "Y", "Increase value",
	gmenu2x->drawButton(gmenu2x->s, "X", "Decrease value",
	gmenu2x->drawButton(gmenu2x->s, ">", "Change color part",
	gmenu2x->drawButton(gmenu2x->s, "<", "/", 10)-4)));
}
