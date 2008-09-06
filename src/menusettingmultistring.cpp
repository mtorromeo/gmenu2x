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
using namespace fastdelegate;

MenuSettingMultiString::MenuSettingMultiString(GMenu2X *gmenu2x, string name, string description, string *value, vector<string> *choices)
	: MenuSetting(gmenu2x,name,description) {
	this->gmenu2x = gmenu2x;
	this->choices = choices;
	this->value = value;
	originalValue = *value;
	setSel( find(choices->begin(),choices->end(),*value)-choices->begin() );

	btnDec = new IconButton(gmenu2x, "skin:imgs/buttons/left.png");
	btnDec->setAction(MakeDelegate(this, &MenuSettingMultiString::decSel));

	btnInc = new IconButton(gmenu2x, "skin:imgs/buttons/right.png", gmenu2x->tr["Change value"]);
	btnInc->setAction(MakeDelegate(this, &MenuSettingMultiString::incSel));
}

void MenuSettingMultiString::draw(int y) {
	MenuSetting::draw(y);
	gmenu2x->s->write( gmenu2x->font, *value, 155, y+6, SFontHAlignLeft, SFontVAlignMiddle );
}

void MenuSettingMultiString::handleTS() {
	btnDec->handleTS();
	btnInc->handleTS();
}

void MenuSettingMultiString::manageInput() {
	if ( gmenu2x->joy[ACTION_LEFT ] ) decSel();
	if ( gmenu2x->joy[ACTION_RIGHT] ) incSel();
}

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
	gmenu2x->drawButton(btnInc,
	gmenu2x->drawButton(btnDec)-6);
}

bool MenuSettingMultiString::edited() {
	return originalValue != *value;
}
