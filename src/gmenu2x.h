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

#ifndef GMENU2X_H
#define GMENU2X_H

#include <string>
#include <iostream>
#include "surfacecollection.h"
#include "FastDelegate.h"
#include "utilities.h"

#ifdef TARGET_GP2X
#include "joystick.h"
#endif

#define BATTERY_READS 10

using std::string;
using fastdelegate::FastDelegate0;

typedef FastDelegate0<> MenuAction;

struct MenuOption {
	string text;
	MenuAction action;
};

class Menu;

class GMenu2X {
private:
	string path;
	string getExePath();
	string getDiskFree();
	unsigned short cpuX;
	unsigned short getBatteryLevel();
	void browsePath(string path, vector<string>* directories, vector<string>* files);
	bool createLink(string path, string file, string section="");
	void scanner();
	void scanPath(string path, vector<string> *files);

	bool inet, usbnet, samba, web;
	string ip, defaultgw;
	void readConfig();
	void writeConfig();
	void readCommonIni();
	void writeCommonIni();
	void initServices();

	bool gp2x_initialized;
	unsigned long gp2x_mem;
	unsigned short *gp2x_memregs;
	volatile unsigned short *MEM_REG;
	void gp2x_init();
	void gp2x_deinit();

public:
	GMenu2X(int argc, char *argv[]);
	~GMenu2X();

#ifdef TARGET_GP2X
	Joystick joy;
#else
	SDL_Event event;
#endif

	//Configuration settings
	RGBAColor selectionColor, topBarColor, bottomBarColor;
	bool saveSelection, useBorders;
	int maxClock, menuClock, startSectionIndex, startLinkIndex;
	//G int gamma;

	SurfaceCollection sc;
	Surface *s;
	ASFont *font;

	//Status functions
	int main();
	void options();
	void contextMenu();
	void runLink();

	void setClock(unsigned mhz);
	void setGamma(int gamma);
	void setInputSpeed();

	void ledOn();
	void ledOff();

	void addLink();
	void editLink();
	void deleteLink();

	void initBG();
	int drawButton(Surface *s, string btn, string text, int x);
	void drawScrollBar(uint pagesize, uint totalsize, uint pagepos, uint top, uint height);
	void drawTopBar(Surface *s=NULL, uint height=20);
	void drawBottomBar(Surface *s=NULL, uint height=20);

	Menu* menu;
};

#endif
