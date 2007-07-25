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
#include <fstream>
#include <sstream>
#include "link.h"
#include "menu.h"
#include "selector.h"

using namespace std;

Link::Link(GMenu2X *gmenu2x) {
	this->gmenu2x = gmenu2x;
	edited = false;
	iconPath = gmenu2x->sc.getSkinFilePath("icons/generic.png");
}

void Link::run() {}

string Link::getTitle() {
	return title;
}

void Link::setTitle(string title) {
	this->title = title;
	edited = true;
}

string Link::getDescription() {
	return description;
}

void Link::setDescription(string description) {
	this->description = description;
	edited = true;
}

string Link::getIcon() {
	return icon;
}

void Link::setIcon(string icon) {
	string skinpath = gmenu2x->getExePath()+"skins/"+gmenu2x->skin;
	if (icon.substr(0,skinpath.length()) == skinpath) {
		string tempIcon = icon.substr(skinpath.length(), icon.length());
		string::size_type pos = tempIcon.find("/");
		if (pos != string::npos)
			icon = "skin:"+tempIcon.substr(pos+1,icon.length());
	}

	iconPath = strreplace(icon,"skin:",skinpath+"/");
	if (iconPath.empty() || !fileExists(iconPath)) {
		iconPath = strreplace(icon,"skin:",gmenu2x->getExePath()+"skins/Default/");
		if (iconPath.empty() || !fileExists(iconPath)) searchIcon();
	}

	this->icon = icon;
	edited = true;
}

string Link::searchIcon() {
	iconPath = gmenu2x->sc.getSkinFilePath("icons/generic.png");
	return iconPath;
}

string Link::getIconPath() {
	return iconPath;
}

void Link::setIconPath(string icon) {
	if (fileExists(icon))
		iconPath = icon;
	else
		iconPath = gmenu2x->sc.getSkinFilePath("icons/generic.png");
}
