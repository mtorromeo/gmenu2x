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
#include "iconbutton.h"
#include "inputdialog.h"

using std::string;
using fastdelegate::MakeDelegate;

MenuSettingString::MenuSettingString(
		GMenu2X *gmenu2x, const string &name,
		const string &description, string *value,
		const string &diagTitle_, const string &diagIcon_)
	: MenuSettingStringBase(gmenu2x, name, description, value)
	, diagTitle(diagTitle_)
	, diagIcon(diagIcon_)
{
	IconButton *btn;

	btn = new IconButton(gmenu2x, "skin:imgs/buttons/x.png", gmenu2x->tr["Clear"]);
	btn->setAction(MakeDelegate(this, &MenuSettingString::clear));
	buttonBox.add(btn);

	btn = new IconButton(gmenu2x, "skin:imgs/buttons/b.png", gmenu2x->tr["Edit"]);
	btn->setAction(MakeDelegate(this, &MenuSettingString::edit));
	buttonBox.add(btn);
}

void MenuSettingString::edit()
{
	InputDialog id(
			gmenu2x, gmenu2x->input, gmenu2x->ts,
				   description, value(), diagTitle, diagIcon);
	if (id.exec()) setValue(id.getInput());
}
