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

#ifndef DIRDIALOG_H_
#define DIRDIALOG_H_

#include <string>
#include "gmenu2x.h"

class FileLister;

using std::string;
using std::vector;

class DirDialog {
protected:
	static const uint ACT_NONE = 0;
	static const uint ACT_SELECT = 1;
	static const uint ACT_CLOSE = 2;
	static const uint ACT_UP = 3;
	static const uint ACT_DOWN = 4;
	static const uint ACT_SCROLLUP = 5;
	static const uint ACT_SCROLLDOWN = 6;
	static const uint ACT_GOUP = 7;
	static const uint ACT_CONFIRM = 8;
	
private:
	int selRow;
	uint selected;
	bool close, result;
	FileLister *fl;
	string text;
	IconButton *btnUp, *btnEnter, *btnConfirm;
	GMenu2X *gmenu2x;
	
	void up();
	void enter();
	void confirm();

public:
	string path;
	DirDialog(GMenu2X *gmenu2x, string text, string dir="");

	bool exec();
};

#endif /*INPUTDIALOG_H_*/
