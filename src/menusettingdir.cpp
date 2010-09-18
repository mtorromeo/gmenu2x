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
#include "iconbutton.h"
#include "dirdialog.h"

using std::string;
using fastdelegate::MakeDelegate;

MenuSettingDir::MenuSettingDir(
		GMenu2X *gmenu2x, const string &name,
		const string &description, string *value)
	: MenuSettingStringBase(gmenu2x, name, description, value)
{
	IconButton *btn;

	btn = new IconButton(gmenu2x, "skin:imgs/buttons/x.png", gmenu2x->tr["Clear"]);
	btn->setAction(MakeDelegate(this, &MenuSettingDir::clear));
	buttonBox.add(btn);

	btn = new IconButton(gmenu2x, "skin:imgs/buttons/b.png", gmenu2x->tr["Select a directory"]);
	btn->setAction(MakeDelegate(this, &MenuSettingDir::edit));
	buttonBox.add(btn);
}

void MenuSettingDir::edit()
{
	DirDialog dd(gmenu2x, description, value());
	if (dd.exec()) setValue( dd.getPath() );
}
