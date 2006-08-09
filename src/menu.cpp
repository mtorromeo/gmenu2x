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

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "menu.h"

using namespace std;

Menu::Menu(string path) {
	this->path = path;

	DIR *dirp;
	struct stat st;
	struct dirent *dptr;
	string filepath;

	if ((dirp = opendir("sections")) == NULL) return;

	while ((dptr = readdir(dirp))) {
		/*if ((strcmp(dptr->d_name, ".") == 0 ||  strcmp(dptr->d_name, "..") == 0)) continue;*/
		if (dptr->d_name[0]=='.') continue;
		filepath = (string)"sections/"+dptr->d_name;
		int statRet = stat(filepath.c_str(), &st);
		if (!S_ISDIR(st.st_mode)) continue;
		if (statRet != -1) sections.push_back((string)dptr->d_name);
	}
	setSectionIndex(0);
}

Menu::~Menu() {
	freeLinks();
}

void Menu::freeLinks() {
	for (vector<Link*>::iterator link = links.begin(); link<links.end(); link++) {
		free(*link);
	}
}

int Menu::selSectionIndex() {
	return iSection;
}

string Menu::selSection() {
	return sections[iSection];
}

void Menu::decSectionIndex() {
	setSectionIndex(iSection-1);
}

void Menu::incSectionIndex() {
	setSectionIndex(iSection+1);
}

void Menu::setSectionIndex(int i) {
	if (i<0) i=sections.size()-1;
	else if (i>=(int)sections.size()) i=0;
	iSection = i;
	readLinks();
}

int Menu::selLinkIndex() {
	return iLink;
}

Link *Menu::selLink() {
	if (links.size()==0) return NULL;
	return links[iLink];
}

void Menu::decLinkIndex() {
	setLinkIndex(iLink-1);
}

void Menu::incLinkIndex() {
	setLinkIndex(iLink+1);
}

void Menu::setLinkIndex(int i) {
	if (i<0) i=links.size()-1;
	else if (i>=(int)links.size()) i=0;
	iLink = i;
}

string Menu::sectionPath(int section) {
	if (section<0 || section>(int)sections.size()) section = iSection;
	return "sections/"+sections[section]+"/";
}

void Menu::readLinks() {
	links.clear();
	iLink = 0;

	DIR *dirp;
	struct stat st;
	struct dirent *dptr;
	string filepath;

	if ((dirp = opendir(sectionPath().c_str())) == NULL) return;

	while ((dptr = readdir(dirp))) {
		/*if ((strcmp(dptr->d_name, ".") == 0 ||  strcmp(dptr->d_name, "..") == 0)) continue;*/
		if (dptr->d_name[0]=='.') continue;
		filepath = sectionPath()+dptr->d_name;
		int statRet = stat(filepath.c_str(), &st);
		if (S_ISDIR(st.st_mode)) continue;
		if (statRet != -1) {
			Link *link = new Link(path, filepath.c_str());
			if (link->targetExists())
				links.push_back( link );
			else
				free(link);
		}
	}
}
