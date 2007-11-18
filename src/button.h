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

#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>
#include "gmenu2x.h"
#include "FastDelegate.h"

using std::string;
using fastdelegate::FastDelegate0;

typedef FastDelegate0<> ButtonAction;

class Button {
protected:
	GMenu2X *gmenu2x;
	ButtonAction action;
	SDL_Rect rect;

public:
	string path;
	Button(GMenu2X *gmenu2x);
	virtual ~Button() {};

	void setSize(int w, int h);
	void setPosition(int x, int y);

	virtual void paint();
	virtual bool paintHover();

	bool handleTS();
	void exec();
	void voidAction() {};
	void setAction(ButtonAction action);
};

#endif /*BUTTON_H_*/
