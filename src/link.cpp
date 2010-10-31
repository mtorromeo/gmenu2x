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

Link::Link(GMenu2X *gmenu2x_)
	: Button(gmenu2x_->ts, true)
	, gmenu2x(gmenu2x_)
{
	action = MakeDelegate(this, &Link::run);
	edited = false;
	iconPath = gmenu2x->sc.getSkinFilePath("icons/generic.png");
	iconX = 0;
	padding = 0;

	updateSurfaces();
}

void Link::run() {}

void Link::paint() {
	iconSurface->blit(gmenu2x->s, iconX, rect.y+padding, 32,32);
	gmenu2x->s->write( gmenu2x->font, getTitle(), iconX+16, rect.y+gmenu2x->skinConfInt["linkHeight"]-padding, HAlignCenter, VAlignBottom );
}

bool Link::paintHover() {
	if (gmenu2x->useSelectionPng)
		gmenu2x->sc["imgs/selection.png"]->blit(gmenu2x->s,rect,HAlignCenter,VAlignMiddle);
	else
		gmenu2x->s->box(rect.x, rect.y, rect.w, rect.h, gmenu2x->skinConfColors[COLOR_SELECTION_BG]);
	return true;
}

void Link::updateSurfaces() {
	iconSurface = gmenu2x->sc[getIconPath()];
}

const string &Link::getTitle() {
	return title;
}

void Link::setTitle(const string &title) {
	this->title = title;
	edited = true;
}

const string &Link::getDescription() {
	return description;
}

void Link::setDescription(const string &description) {
	this->description = description;
	edited = true;
}

const string &Link::getIcon() {
	return icon;
}

void Link::setIcon(const string &icon) {
	string skinpath = gmenu2x->getExePath()+"skins/"+gmenu2x->confStr["skin"];

	if (icon.substr(0,skinpath.length()) == skinpath) {
		string tempIcon = icon.substr(skinpath.length(), icon.length());
		string::size_type pos = tempIcon.find("/");
		if (pos != string::npos)
			this->icon = "skin:"+tempIcon.substr(pos+1,icon.length());
		else
			this->icon = icon;
	} else {
		this->icon = icon;
	}

	iconPath = strreplace(this->icon,"skin:",skinpath+"/");
	if (iconPath.empty() || !fileExists(iconPath)) {
		iconPath = strreplace(this->icon,"skin:",gmenu2x->getExePath()+"skins/Default/");
		if (!fileExists(iconPath)) searchIcon();
	}

	edited = true;
	updateSurfaces();
}

const string &Link::searchIcon() {
	iconPath = gmenu2x->sc.getSkinFilePath("icons/generic.png");
	return iconPath;
}

const string &Link::getIconPath() {
	if (iconPath.empty()) searchIcon();
	return iconPath;
}

void Link::setIconPath(const string &icon) {
	if (fileExists(icon))
		iconPath = icon;
	else
		iconPath = gmenu2x->sc.getSkinFilePath("icons/generic.png");
	updateSurfaces();
}

void Link::setSize(int w, int h) {
	Button::setSize(w,h);
	recalcCoordinates();
}

void Link::setPosition(int x, int y) {
	Button::setPosition(x,y);
	recalcCoordinates();
}

void Link::recalcCoordinates() {
	iconX = rect.x+(rect.w-32)/2;
	padding = max(gmenu2x->skinConfInt["linkHeight"] - 32 - gmenu2x->font->getHeight(), 0) / 3;
}
