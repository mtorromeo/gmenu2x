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

Menu::Menu(GMenu2X *gmenu2x, string path) {
	this->gmenu2x = gmenu2x;
	this->path = path;
	iFirstDispSection = 0;

	DIR *dirp;
	struct stat st;
	struct dirent *dptr;
	string filepath;

	if ((dirp = opendir("sections")) == NULL) return;

	while ((dptr = readdir(dirp))) {
		if (dptr->d_name[0]=='.') continue;
		filepath = (string)"sections/"+dptr->d_name;
		int statRet = stat(filepath.c_str(), &st);
		if (!S_ISDIR(st.st_mode)) continue;
		if (statRet != -1) sections.push_back((string)dptr->d_name);
	}
	
	closedir(dirp);
	sort(sections.begin(),sections.end(),case_less());
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

void Menu::setSectionIndex(int i) {
	if (i<0)
		i=sections.size()-1;
	else if (i>=(int)sections.size())
		i=0;
	iSection = i;

	if (i>(int)iFirstDispSection+4)
		iFirstDispSection = i-4;
	else if (i<(int)iFirstDispSection)
		iFirstDispSection = i;

	readLinks();
}

void Menu::decSectionIndex() {
	setSectionIndex(iSection-1);
}

void Menu::incSectionIndex() {
	setSectionIndex(iSection+1);
}

uint Menu::firstDispSection() {
	return iFirstDispSection;
}

void Menu::linkLeft() {
	if (iLink%6 == 0)
		setLinkIndex( (int)links.size()>iLink+5 ? iLink+5 : links.size()-1 );
	else
		setLinkIndex(iLink-1);
}

void Menu::linkRight() {
	if (iLink%6 == 5 || iLink == (int)links.size()-1)
		setLinkIndex(iLink-iLink%6);
	else
		setLinkIndex(iLink+1);
}

void Menu::linkUp() {
	int l = iLink-6;
	if (l<0) {
		int rows = links.size()/6+1;
		l = (rows*6)+l;
		if (l >= (int)links.size())
			l -= 6;
	}
	setLinkIndex(l);
}

void Menu::linkDown() {
	uint l = iLink+6;
	if (l >= links.size())
		l %= 6;
	setLinkIndex(l);
}

uint Menu::firstDispRow() {
	return iFirstDispRow;
}

int Menu::selLinkIndex() {
	return iLink;
}

Link *Menu::selLink() {
	if (links.size()==0) return NULL;
	return links[iLink];
}

void Menu::setLinkIndex(int i) {
	if (i<0)
		i=links.size()-1;
	else if (i>=(int)links.size())
		i=0;

	if (i>=(int)iFirstDispRow*6+24)
		iFirstDispRow = i/6-3;
	else if (i<(int)iFirstDispRow*6)
		iFirstDispRow = i/6;

	iLink = i;
}

string Menu::sectionPath(int section) {
	if (section<0 || section>(int)sections.size()) section = iSection;
	return "sections/"+sections[section]+"/";
}

void Menu::readLinks() {
	vector<string> linkfiles;
	
	links.clear();
	iLink = 0;
	iFirstDispRow = 0;

	DIR *dirp;
	struct stat st;
	struct dirent *dptr;
	string filepath;

	if ((dirp = opendir(sectionPath().c_str())) == NULL) return;

	while ((dptr = readdir(dirp))) {
		if (dptr->d_name[0]=='.') continue;
		filepath = sectionPath()+dptr->d_name;
		int statRet = stat(filepath.c_str(), &st);
		if (S_ISDIR(st.st_mode)) continue;
		if (statRet != -1) {
			linkfiles.push_back(filepath);
		}
	}
	
	sort(linkfiles.begin(), linkfiles.end(),case_less());
	for (uint x=0; x<linkfiles.size(); x++) {
		Link *link = new Link(gmenu2x, path, linkfiles[x].c_str());
		if (link->targetExists())
			links.push_back( link );
		else
			free(link);
	}
	
	closedir(dirp);
}
