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

#ifndef BROWSEDIALOG_H_
#define BROWSEDIALOG_H_

#include <string>
#include "filelister.h"
#include "gmenu2x.h"
#include "buttonbox.h"
#include "dialog.h"

class FileLister;

using std::string;

class BrowseDialog : protected Dialog {
protected:
	BrowseDialog(GMenu2X *gmenu2x, const string &title, const string &subtitle);
	virtual ~BrowseDialog();

	virtual void beforeFileList() {};
	virtual void onChangeDir() {};

	void setPath(const string &path) {
		fl->setPath(path);
		onChangeDir();
	}

	FileLister *fl;
	unsigned int selected;

private:
	enum Action {
		ACT_NONE,
		ACT_SELECT,
		ACT_CLOSE,
		ACT_UP,
		ACT_DOWN,
		ACT_SCROLLUP,
		ACT_SCROLLDOWN,
		ACT_GOUP,
		ACT_CONFIRM,
	};

	bool close, result;

	string title;
	string subtitle;

	SDL_Rect clipRect;
	SDL_Rect touchRect;

	unsigned int numRows;
	unsigned int rowHeight;

	bool ts_pressed;

	Surface *iconGoUp;
	Surface *iconFolder;
	Surface *iconFile;

	ButtonBox buttonBox;

	Action getAction();
	void handleInput();

	void paint();

	void directoryUp();
	void directoryEnter();
	void confirm();

public:
	bool exec();

	const std::string &getPath() {
		return fl->getPath();
	}
	std::string getFile() {
		return (*fl)[selected];
	}
};

#endif /*INPUTDIALOG_H_*/
