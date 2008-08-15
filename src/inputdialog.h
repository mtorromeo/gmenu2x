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

#define KEY_WIDTH 20
#define KEY_HEIGHT 20
#define KB_TOP 90

#define ID_NO_ACTION 0
#define ID_ACTION_CLOSE 1
#define ID_ACTION_UP 2
#define ID_ACTION_DOWN 3
#define ID_ACTION_LEFT 4
#define ID_ACTION_RIGHT 5
#define ID_ACTION_BACKSPACE 6
#define ID_ACTION_SPACE 7
#define ID_ACTION_GOUP 8
#define ID_ACTION_SELECT 9
#define ID_ACTION_KB_CHANGE 10

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
	stringlist *kb;
	int kbLength, kbWidth, kbHeight, kbLeft;
	SDL_Rect kbRect;

	int drawVirtualKeyboard();
	void setKeyboard(int);

public:
	InputDialog(GMenu2X *gmenu2x, string text, string startvalue="");

	string input;
	bool exec();
};

#endif /*INPUTDIALOG_H_*/
