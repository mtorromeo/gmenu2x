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

#ifndef FILEDIALOG_H_
#define FILEDIALOG_H_

#include <string>
#include "filelister.h"
#include "gmenu2x.h"

#define FD_NO_ACTION 0
#define FD_ACTION_CLOSE 1
#define FD_ACTION_UP 2
#define FD_ACTION_DOWN 3
#define FD_ACTION_LEFT 4
#define FD_ACTION_RIGHT 5
#define FD_ACTION_SCROLLDOWN 6
#define FD_ACTION_SCROLLUP 7
#define FD_ACTION_GOUP 8
#define FD_ACTION_SELECT 9

using std::string;
using std::vector;

class FileDialog {
protected:
	int selRow;
	string text, title;
	GMenu2X *gmenu2x;
	string filter;
	FileLister fl;
	uint selected;
	string path_v;

public:
	string file;
	FileDialog(GMenu2X *gmenu2x, string text, string filter="", string file="");
	virtual ~FileDialog() {};

	virtual string path() { return path_v; };
	virtual void setPath(string path);

	inline virtual void beforeFileList();
	inline virtual void onChangeDir();
	bool exec();
};

#endif /*INPUTDIALOG_H_*/
