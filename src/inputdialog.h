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

#ifndef INPUTDIALOG_H_
#define INPUTDIALOG_H_

#include <string>
#include "gmenu2x.h"

using std::string;
using std::vector;

typedef vector<string> stringlist;

class InputDialog {
private:
	int selRow, selCol;
	string text;
	GMenu2X *gmenu2x;
	short curKeyboard;
	vector<stringlist> keyboard;

	void drawVirtualKeyboard();

public:
	InputDialog(GMenu2X *gmenu2x, string text, string startvalue="");

	string input;
	bool exec();
};

#endif /*INPUTDIALOG_H_*/
