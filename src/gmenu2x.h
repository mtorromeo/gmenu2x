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
#include "translator.h"
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
	string path; //!< Contains the working directory of GMenu2X
	/*!
	Retrieves the free disk space on the sd
	@return String containing a human readable representation of the free disk space
	*/
	string getDiskFree();
	unsigned short cpuX; //!< Offset for displaying cpu clock information
	unsigned short volumeX; //!< Offset for displaying volume level
	unsigned short manualX; //!< Offset for displaying the manual indicator in the taskbar
	/*!
	Reads the current battery state and returns a number representing it's level of charge
	@return A number representing battery charge. 0 means fully discharged. 5 means fully charged. 6 represents a gp2x using AC power.
	*/
	unsigned short getBatteryLevel();
	void browsePath(string path, vector<string>* directories, vector<string>* files);
	/*!
	Starts the scanning of the nand and sd filesystems, searching for gpe and gpu files and creating the links in 2 dedicated sections.
	*/
	void scanner();
	/*!
	Performs the actual scan in the given path and populates the files vector with the results. The creation of the links is not performed here.
	@see scanner
	*/
	void scanPath(string path, vector<string> *files);

	bool inet, //!< Represents the configuration of the basic network services. @see readCommonIni @see usbnet @see samba @see web
		usbnet,
		samba,
		web;
	string ip, defaultgw, lastSelectorDir;
	int lastSelectorElement;
	void readConfig();
	void readTmp();
	void readCommonIni();
	void writeCommonIni();

	void initServices();
	void initFont();
	void initMenu();

	uint numRows, numCols;

#ifdef TARGET_GP2X
	unsigned long gp2x_mem;
	unsigned short *gp2x_memregs;
	volatile unsigned short *MEM_REG;
	int cx25874;
#endif
	string tvoutEncoding;
	void gp2x_tvout_on(bool pal);
	void gp2x_tvout_off();
	void gp2x_init();
	void gp2x_deinit();
	void toggleTvOut();

public:
	GMenu2X(int argc, char *argv[]);
	~GMenu2X();
	void quit();

	/*!
	Retrieves the parent directory of GMenu2X.
	This functions is used to initialize the "path" variable.
	@see path
	@return String containing the parent directory
	*/
	string getExePath();

#ifdef TARGET_GP2X
	Joystick joy;
#else
	SDL_Event event;
#endif

	//Configuration settings
	RGBAColor selectionColor, topBarColor, bottomBarColor, messageBoxColor, messageBoxBorderColor, messageBoxSelectionColor;
	bool saveSelection, outputLogs;
	int maxClock, menuClock, startSectionIndex, startLinkIndex, globalVolume;
	string skin, wallpaper;
	void setSkin(string skin);
	//G
	int gamma;

	SurfaceCollection sc;
	Translator tr;
	Surface *s, *bg;
	ASFont *font;

	//Status functions
	int main();
	void options();
	void activateSdUsb();
	void activateNandUsb();
	void activateRootUsb();
	void about();
	void viewLog();
	void contextMenu();
	void changeWallpaper();

	void applyRamTimings();
	void applyDefaultTimings();

	void setClock(unsigned mhz);
	void setGamma(int gamma);
	void setVolume(int vol);

	void setInputSpeed();

	void writeConfig();
	void writeTmp(int selelem=-1, string selectordir="");

	void ledOn();
	void ledOff();

	void addLink();
	void editLink();
	void deleteLink();
	void addSection();
	void renameSection();
	void deleteSection();

	void initBG();
	int drawButton(Surface *s, string btn, string text, int x, int y=230);
	int drawButtonRight(Surface *s, string btn, string text, int x, int y=230);
	void drawScrollBar(uint pagesize, uint totalsize, uint pagepos, uint top, uint height);

	void drawTitleIcon(string icon, bool skinRes=true, Surface *s=NULL);
	void writeTitle(string title, Surface *s=NULL);
	void writeSubTitle(string subtitle, Surface *s=NULL);
	void drawTopBar(Surface *s=NULL);
	void drawBottomBar(Surface *s=NULL);

	Menu* menu;
};

#endif
