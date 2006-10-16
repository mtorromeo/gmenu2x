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
#include "menusettingmultistring.h"
#include "utilities.h"

using namespace std;

MenuSettingMultiString::MenuSettingMultiString(GMenu2X *gmenu2x, string name, string description, string *value, vector<string> *choices)
	: MenuSetting(gmenu2x,name,description) {
	this->gmenu2x = gmenu2x;
	this->choices = choices;
	this->value = value;
	originalValue = *value;
	setSel( find(choices->begin(),choices->end(),*value)-choices->begin() );
}

void MenuSettingMultiString::draw(int y) {
	MenuSetting::draw(y);
	gmenu2x->s->write( gmenu2x->font, *value, 155, y+9, SFontHAlignLeft, SFontVAlignMiddle );
}

#ifdef TARGET_GP2X
#include "gp2x.h"

void MenuSettingMultiString::manageInput() {
	if ( gmenu2x->joy[GP2X_BUTTON_LEFT ] ) decSel();
	if ( gmenu2x->joy[GP2X_BUTTON_RIGHT] ) incSel();
}
#else
void MenuSettingMultiString::manageInput() {
	if ( gmenu2x->event.key.keysym.sym==SDLK_LEFT  ) decSel();
	if ( gmenu2x->event.key.keysym.sym==SDLK_RIGHT ) incSel();
}
#endif

void MenuSettingMultiString::incSel() {
	setSel(selected+1);
}

void MenuSettingMultiString::decSel() {
	setSel(selected-1);
}

void MenuSettingMultiString::setSel(int sel) {
	if (sel<0) sel = choices->size()-1;
	else if (sel>=(int)choices->size()) sel = 0;
	selected = sel;
	*value = (*choices)[sel];
}

void MenuSettingMultiString::adjustInput() {}

void MenuSettingMultiString::drawSelected(int) {
	gmenu2x->drawButton(gmenu2x->s, ">", "Change value",
	gmenu2x->drawButton(gmenu2x->s, "<", "/", 10)-4);
}

bool MenuSettingMultiString::edited() {
	return originalValue != *value;
}
