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
#ifndef MENUSETTINGRGBA_H
#define MENUSETTINGRGBA_H

#include "menusetting.h"
#include "surface.h"

class GMenu2X;

class MenuSettingRGBA : public MenuSetting {
private:
	unsigned short selPart;
	int y;
	std::string strR, strG, strB, strA;
	RGBAColor originalValue;
	RGBAColor *_value;

	void dec();
	void inc();
	void leftComponent();
	void rightComponent();

public:
	MenuSettingRGBA(GMenu2X *gmenu2x, const std::string &name, const std::string &description, RGBAColor *value);
	virtual ~MenuSettingRGBA() {};

	virtual void draw(int y);
	virtual void handleTS();
	virtual void manageInput();
	virtual void adjustInput();
	virtual void drawSelected(int y);
	virtual bool edited();

	void setSelPart(Uint8 value);
	void setR(Uint8 r);
	void setG(Uint8 g);
	void setB(Uint8 b);
	void setA(Uint8 a);
	Uint8 getSelPart();
	RGBAColor value();
};

#endif
