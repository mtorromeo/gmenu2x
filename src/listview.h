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
#ifndef LISTVIEW_H_
#define LISTVIEW_H_

#include "gmenu2x.h"
#include "listviewitem.h"

using std::vector;

class ListView {
private:
	int firstDisplayItem, selectedItem;
	int itemsPerPage;

protected:
	vector<ListViewItem*> items;
	SDL_Rect rect;

public:
	ListView(GMenu2X *gmenu2x);
	virtual ~ListView();

	GMenu2X *gmenu2x;

	ListViewItem *add(ListViewItem *item);
	ListViewItem *add(string text);
	void     del(ListViewItem *item);
	void     del(int itemIndex);
	void     clear();

	void setPosition(int x, int y);
	void setSize(int w, int h);
	int getWidth();

	virtual void paint();
	virtual void handleInput();

	ListViewItem *operator[](int);
};

#endif
