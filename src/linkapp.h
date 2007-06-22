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
#ifndef LINKAPP_H
#define LINKAPP_H

#include <string>
#include <iostream>

#include "link.h"

using std::string;

class GMenu2X;

/**
Parses links files.

	@author Massimiliano Torromeo <massimiliano.torromeo@gmail.com>
*/
class LinkApp : public Link {
private:
	string sclock, svolume;
	int iclock, ivolume;
	//G
	string sgamma;
	//G
	int igamma;
	string exec, params, workdir, manual, selectordir, selectorfilter, selectorscreens;
	bool selectorbrowser, useRamTimings;
	void drawRun();

	string aliasfile;

public:
	LinkApp(GMenu2X *gmenu2x, const char* linkfile);
	string searchIcon();

	string getExec();
	void setExec(string exec);
	string getParams();
	void setParams(string params);
	string getWorkdir();
	void setWorkdir(string workdir);
	string getManual();
	void setManual(string manual);
	string getSelectorDir();
	void setSelectorDir(string selectordir);
	bool getSelectorBrowser();
	void setSelectorBrowser(bool value);
	bool getUseRamTimings();
	void setUseRamTimings(bool value);
	string getSelectorScreens();
	void setSelectorScreens(string selectorscreens);
	string getSelectorFilter();
	void setSelectorFilter(string selectorfilter);
	string getAliasFile();
	void setAliasFile(string aliasfile);

	string file;

	int clock();
	string clockStr(int maxClock);
	void setClock(int mhz);

	int volume();
	string volumeStr();
	void setVolume(int vol);

//G
	int gamma();
	string gammaStr();
	void setGamma(int gamma);
// /G

	bool wrapper;
	bool dontleave;

	bool save();
	void run();
	void showManual();
	void selector(int startSelection=0, string selectorDir="");
	void launch(string selectedFile="", string selectedDir="");
	bool targetExists();
};

#endif
