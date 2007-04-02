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

#include "surfacecollection.h"

using namespace std;

SurfaceCollection::SurfaceCollection(bool defaultAlpha, string skin) {
	this->defaultAlpha = defaultAlpha;
	setSkin(skin);
}

SurfaceCollection::~SurfaceCollection() {}

void SurfaceCollection::setSkin(string skin) {
	this->skin = skin;
}

string SurfaceCollection::getSkinFilePath(string file) {
	if (fileExists("skins/"+skin+"/"+file))
		return "skins/"+skin+"/"+file;
	else if (fileExists("skins/Default/"+file))
		return "skins/Default/"+file;
	else
		return "";
}

void SurfaceCollection::debug() {
	hash_map<string, Surface*>::iterator end = surfaces.end();
	for(hash_map<string, Surface*>::iterator curr = surfaces.begin(); curr != end; curr++){
		cout << "key: " << curr->first << endl;
	}
}

bool SurfaceCollection::exists(string path) {
	return surfaces.find(path) != surfaces.end();
}

Surface *SurfaceCollection::add(Surface *s, string path) {
	if (exists(path)) del(path);
	surfaces[path] = s;
	return s;
}

Surface *SurfaceCollection::add(string path, bool alpha) {
#ifdef DEBUG
	cout << "Adding surface: " << path << endl;
#endif
	if (exists(path)) del(path);
	string filePath = path;

	if (filePath.substr(0,5)=="skin:") {
		filePath = getSkinFilePath(filePath.substr(5,filePath.length()));
		if (filePath.empty())
			return NULL;
	} else if (!fileExists(filePath)) return NULL;

	Surface *s = new Surface(filePath,alpha);
	surfaces[path] = s;
	return s;
}

Surface *SurfaceCollection::addSkinRes(string path, bool alpha) {
#ifdef DEBUG
	cout << "Adding skin surface: " << path << endl;
#endif

	if (path.empty()) return NULL;
	if (exists(path)) del(path);

	string skinpath = getSkinFilePath(path);
	if (skinpath.empty())
		return NULL;
	Surface *s = new Surface(skinpath,alpha);
	if (s != NULL)
		surfaces[path] = s;
	return s;
}

void SurfaceCollection::del(string path) {
	hash_map<string, Surface*>::iterator i = surfaces.find(path);
	if (i != surfaces.end()) {
		free(i->second);
		surfaces.erase(i);
	}
}

void SurfaceCollection::clear() {
	while (surfaces.size()>0) {
		free(surfaces.begin()->second);
		surfaces.erase(surfaces.begin());
	}
}

void SurfaceCollection::move(string from, string to) {
	del(to);
	surfaces[to] = surfaces[from];
	surfaces.erase(from);
}

Surface *SurfaceCollection::operator[](string key) {
	hash_map<string, Surface*>::iterator i = surfaces.find(key);
	if (i == surfaces.end())
		return add(key, defaultAlpha);
	else
		return i->second;
}

Surface *SurfaceCollection::skinRes(string key) {
	if (key.empty()) return NULL;

	hash_map<string, Surface*>::iterator i = surfaces.find(key);
	if (i == surfaces.end())
		return addSkinRes(key, defaultAlpha);
	else
		return i->second;
}
