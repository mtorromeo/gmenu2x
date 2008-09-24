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
#include "menusettingimage.h"
#include "imagedialog.h"
#include "utilities.h"

using namespace std;

MenuSettingImage::MenuSettingImage(GMenu2X *gmenu2x, string name, string description, string *value, string filter)
	: MenuSettingFile(gmenu2x,name,description,value,filter) {
	this->gmenu2x = gmenu2x;
	this->filter = filter;
	_value = value;
	originalValue = *value;
}

void MenuSettingImage::manageInput() {
	if ( gmenu2x->input[ACTION_X] ) setValue("");
	if ( gmenu2x->input[ACTION_B] ) {
		ImageDialog id(gmenu2x, description, filter, value());
		if (id.exec()) setValue( id.path()+"/"+id.file );
	}
}

void MenuSettingImage::setValue(string value) {
	string skinpath = gmenu2x->getExePath()+"skins/"+gmenu2x->skin;
	bool inSkinDir = value.substr(0,skinpath.length()) == skinpath;
	if (!inSkinDir && gmenu2x->skin != "Default") {
		skinpath = gmenu2x->getExePath()+"skins/Default";
		inSkinDir = value.substr(0,skinpath.length()) == skinpath;
	}
	if (inSkinDir) {
		string tempIcon = value.substr(skinpath.length(), value.length());
		string::size_type pos = tempIcon.find("/");
		if (pos != string::npos)
			value = "skin:"+tempIcon.substr(pos+1,value.length());
	}
	*_value = value;
}
