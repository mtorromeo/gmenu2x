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
#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "linkaction.h"

using std::string;
using std::vector;

class LinkApp;
class GMenu2X;

typedef vector<Link*> linklist;

/**
Handles the menu structure

	@author Massimiliano Torromeo <massimiliano.torromeo@gmail.com>
*/
class Menu {
private:
	GMenu2X *gmenu2x;
	int iSection, iLink;
	uint iFirstDispSection, iFirstDispRow;
	void readLinks();
	void freeLinks();

public:
	Menu(GMenu2X *gmenu2x);
	~Menu();

	vector<string> sections;
	vector<linklist> links;
	linklist *sectionLinks(int i = -1);

	int selSectionIndex();
	string selSection();
	void decSectionIndex();
	void incSectionIndex();
	void setSectionIndex(int i);
	uint firstDispSection();
	uint firstDispRow();

	bool addActionLink(uint section, string title, LinkRunAction action, string description="", string icon="");
	bool addLink(string path, string file, string section="");
	bool addSection(string sectionName);
	void deleteSelectedLink();
	void deleteSelectedSection();

	bool linkChangeSection(uint linkIndex, uint oldSectionIndex, uint newSectionIndex);

	int selLinkIndex();
	Link *selLink();
	LinkApp *selLinkApp();
	void linkLeft();
	void linkRight();
	void linkUp();
	void linkDown();
	void setLinkIndex(int i);

	string sectionPath(int section = -1);
};

#endif
