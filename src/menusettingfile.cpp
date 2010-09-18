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
#include "menusettingfile.h"
#include "filedialog.h"

using namespace std;
using namespace fastdelegate;

MenuSettingFile::MenuSettingFile(
		GMenu2X *gmenu2x, const string &name,
		const string &description, string *value, const string &filter_)
	: MenuSettingStringBase(gmenu2x, name, description, value)
	, filter(filter_)
{
	IconButton *btn;

	btn = new IconButton(gmenu2x, "skin:imgs/buttons/x.png", gmenu2x->tr["Clear"]);
	btn->setAction(MakeDelegate(this, &MenuSettingFile::clear));
	buttonBox.add(btn);

	btn = new IconButton(gmenu2x, "skin:imgs/buttons/b.png", gmenu2x->tr["Select a file"]);
	btn->setAction(MakeDelegate(this, &MenuSettingFile::edit));
	buttonBox.add(btn);
}

void MenuSettingFile::edit()
{
	FileDialog fd(gmenu2x, description, filter, value());
	if (fd.exec()) {
		setValue(fd.getPath() + "/" + fd.getFile());
	}
}
