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
#ifndef MENUSETTINGBOOL_H
#define MENUSETTINGBOOL_H

#include "iconbutton.h"
#include "menusetting.h"

using std::string;
class GMenu2X;

class MenuSettingBool : public MenuSetting {
private:
	bool originalValue;
	bool *_value;
	string strvalue;
	GMenu2X *gmenu2x;
	IconButton *btnToggle;

	void toggle();

public:
	MenuSettingBool(GMenu2X *gmenu2x, string name, string description, bool *value);
	virtual ~MenuSettingBool() {};

	virtual void draw(int y);
	virtual void handleTS();
	virtual void manageInput();
	virtual void adjustInput();
	virtual void drawSelected(int y);
	virtual bool edited();

	void setValue(bool value);
	bool value();
};

#endif
