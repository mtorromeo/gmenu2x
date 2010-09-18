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
#include "gmenu2x.h"
#include "iconbutton.h"
#include "FastDelegate.h"

using std::string;
using std::vector;
using fastdelegate::MakeDelegate;

MenuSettingMultiString::MenuSettingMultiString(
		GMenu2X *gmenu2x, const string &name,
		const string &description, string *value,
		const vector<string> *choices_)
	: MenuSettingStringBase(gmenu2x, name, description, value)
	, choices(choices_)
{
	setSel(find(choices->begin(), choices->end(), *value) - choices->begin());

	IconButton *btn;

	btn = new IconButton(gmenu2x, "skin:imgs/buttons/left.png");
	btn->setAction(MakeDelegate(this, &MenuSettingMultiString::decSel));
	buttonBox.add(btn);

	btn = new IconButton(gmenu2x, "skin:imgs/buttons/right.png", gmenu2x->tr["Change value"]);
	btn->setAction(MakeDelegate(this, &MenuSettingMultiString::incSel));
	buttonBox.add(btn);
}

void MenuSettingMultiString::manageInput()
{
	if (gmenu2x->input[ACTION_LEFT ]) decSel();
	if (gmenu2x->input[ACTION_RIGHT]) incSel();
}

void MenuSettingMultiString::incSel()
{
	setSel(selected + 1);
}

void MenuSettingMultiString::decSel()
{
	setSel(selected - 1);
}

void MenuSettingMultiString::setSel(int sel)
{
	if (sel < 0) {
		sel = choices->size()-1;
	} else if (sel >= (int)choices->size()) {
		sel = 0;
	}
	selected = sel;
	setValue((*choices)[sel]);
}
