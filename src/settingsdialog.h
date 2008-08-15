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

#ifndef SETTINGSDIALOG_H_
#define SETTINGSDIALOG_H_

#define SD_NO_ACTION 0
#define SD_ACTION_CLOSE 1
#define SD_ACTION_UP 2
#define SD_ACTION_DOWN 3

#include <string>
#include "gmenu2x.h"
#include "menusetting.h"

using std::string;
using std::vector;

class SettingsDialog {
private:
	vector<MenuSetting *> voices;
	string text, icon;
	GMenu2X *gmenu2x;

public:
	SettingsDialog(GMenu2X *gmenu2x, string text, string icon="skin:sections/settings.png");
	~SettingsDialog();

	bool edited();
	bool exec();
	void addSetting(MenuSetting* set);
};

#endif /*INPUTDIALOG_H_*/
