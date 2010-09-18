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
using namespace fastdelegate;

MenuSettingDir::MenuSettingDir(GMenu2X *gmenu2x, const string &name, const string &description, string *value)
	: MenuSetting(gmenu2x,name,description) {
	IconButton *btn;

	_value = value;
	originalValue = *value;

	btn = new IconButton(gmenu2x, "skin:imgs/buttons/x.png", gmenu2x->tr["Clear"]);
	btn->setAction(MakeDelegate(this, &MenuSettingDir::clear));
	buttonBox.add(btn);

	btn = new IconButton(gmenu2x, "skin:imgs/buttons/b.png", gmenu2x->tr["Select a directory"]);
	btn->setAction(MakeDelegate(this, &MenuSettingDir::select));
	buttonBox.add(btn);
}

void MenuSettingDir::draw(int y)
{
	MenuSetting::draw(y);
	gmenu2x->s->write( gmenu2x->font, value(), 155, y+gmenu2x->font->getHalfHeight(), SFontHAlignLeft, SFontVAlignMiddle );
}

void MenuSettingDir::manageInput()
{
	if (gmenu2x->input[ACTION_X]) setValue("");
	if (gmenu2x->input[ACTION_B]) select();
}

void MenuSettingDir::clear()
{
	setValue("");
}

void MenuSettingDir::select()
{
	DirDialog dd(gmenu2x, description, value());
	if (dd.exec()) setValue( dd.getPath() );
}

void MenuSettingDir::setValue(const string &value)
{
	*_value = value;
}

const string &MenuSettingDir::value()
{
	return *_value;
}

void MenuSettingDir::adjustInput() {}

bool MenuSettingDir::edited() {
	return originalValue != value();
}
