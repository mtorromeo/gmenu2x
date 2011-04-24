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
class InputManager;

/**
Parses links files.

	@author Massimiliano Torromeo <massimiliano.torromeo@gmail.com>
*/
class LinkApp : public Link {
private:
	InputManager &inputMgr;
	string sclock, svolume;
	int iclock, ivolume;
	//G
	string sgamma;
	//G
	int igamma;
	string exec, params, workdir, manual, selectordir, selectorfilter, selectorscreens;
	bool selectorbrowser, useRamTimings, useGinge;
	void drawRun();

	string aliasfile;
	string file;

	bool wrapper;
	bool dontleave;

public:
	LinkApp(GMenu2X *gmenu2x, InputManager &inputMgr, const char* linkfile);
	virtual const string &searchIcon();

	const string &getExec();
	void setExec(const string &exec);
	const string &getParams();
	void setParams(const string &params);
	const string &getWorkdir();
	const string getRealWorkdir();
	void setWorkdir(const string &workdir);
	const string &getManual();
	void setManual(const string &manual);
	const string &getSelectorDir();
	void setSelectorDir(const string &selectordir);
	bool getSelectorBrowser();
	void setSelectorBrowser(bool value);
	bool getUseRamTimings();
	void setUseRamTimings(bool value);
	bool getUseGinge();
	void setUseGinge(bool value);
	const string &getSelectorScreens();
	void setSelectorScreens(const string &selectorscreens);
	const string &getSelectorFilter();
	void setSelectorFilter(const string &selectorfilter);
	const string &getAliasFile();
	void setAliasFile(const string &aliasfile);

	int clock();
	const string &clockStr(int maxClock);
	void setClock(int mhz);

	int volume();
	const string &volumeStr();
	void setVolume(int vol);

//G
	int gamma();
	const string &gammaStr();
	void setGamma(int gamma);
// /G

	bool save();
	void run();
	void showManual();
	void selector(int startSelection=0, const string &selectorDir="");
	void launch(const string &selectedFile="", const string &selectedDir="");
	bool targetExists();

	const string &getFile() { return file; }
	void renameFile(const string &name);
	bool &needsWrapperRef() { return wrapper; }
	bool &runsInBackgroundRef() { return dontleave; }
};

#endif
