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
using namespace fastdelegate;

Link::Link(GMenu2X *gmenu2x) : Button(gmenu2x, true) {
	this->gmenu2x = gmenu2x;
	action = MakeDelegate(this, &Link::run);
	edited = false;
	iconPath = gmenu2x->sc.getSkinFilePath("icons/generic.png");
}

void Link::run() {}

void Link::paint() {
	int ix = rect.x+((rect.w-32)/2);
	gmenu2x->sc[getIconPath()]->blit(gmenu2x->s,ix,rect.y,32,32);
	gmenu2x->s->write( gmenu2x->font, getTitle(), ix+16, rect.y+42, SFontHAlignCenter, SFontVAlignBottom );
}

bool Link::paintHover() {
	if (gmenu2x->useSelectionPng)
		gmenu2x->sc["imgs/selection.png"]->blit(gmenu2x->s,rect,SFontHAlignCenter,SFontVAlignMiddle);
	else
		gmenu2x->s->box(rect.x, rect.y, rect.w, rect.h, gmenu2x->selectionColor);
	return true;
}

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
		if (!fileExists(iconPath)) searchIcon();
	}

	this->icon = icon;
	edited = true;
}

string Link::searchIcon() {
	iconPath = gmenu2x->sc.getSkinFilePath("icons/generic.png");
	return iconPath;
}

string Link::getIconPath() {
	if (iconPath.empty()) searchIcon();
	return iconPath;
}

void Link::setIconPath(string icon) {
	if (fileExists(icon))
		iconPath = icon;
	else
		iconPath = gmenu2x->sc.getSkinFilePath("icons/generic.png");
}
