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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <fstream>
#include <sstream>
#include "linkapp.h"
#include "menu.h"
#include "selector.h"

using namespace std;

LinkApp::LinkApp(GMenu2X *gmenu2x, string path, const char* linkfile)
	: Link(gmenu2x) {
	this->gmenu2x = gmenu2x;
	this->path = path;
	file = linkfile;
	wrapper = false;
	dontleave = false;
	setClock(200);
	//G setGamma(0);
	selectordir = "";
	selectorfilter = "";

	string line;
	ifstream infile (linkfile, ios_base::in);
	while (getline(infile, line, '\n')) {
		line = trim(line);
		if (line=="") continue;
		if (line[0]=='#') continue;

		string::size_type position = line.find("=");
		string name = trim(line.substr(0,position));
		string value = trim(line.substr(position+1));
		if (name == "title") {
			title = value;
		} else if (name == "description") {
			description = value;
		} else if (name == "icon") {
			if (fileExists(value)) icon = value;
		} else if (name == "exec") {
			exec = value;
			if (icon=="") {
				string::size_type pos = exec.rfind(".");
				string execicon = exec.substr(0,pos)+".png";
				if (fileExists(execicon)) icon = execicon;
			}
		} else if (name == "params") {
			params = value;
		} else if (name == "workdir") {
			workdir = value;
		} else if (name == "wrapper") {
			if (value=="true") wrapper = true;
		} else if (name == "dontleave") {
			if (value=="true") dontleave = true;
		} else if (name == "clock") {
			setClock( atoi(value.c_str()) );
		//G } else if (name == "gamma") {
		//G 	setGamma( atoi(value.c_str()) );
		} else if (name == "selectordir") {
			setSelectorDir( value );
		} else if (name == "selectorfilter") {
			setSelectorFilter( value );
		} else if (name == "selectorscreens") {
			setSelectorScreens( value );
		} else if (name == "selectoraliases") {
			setAliasFile( value );
		} else {
			cout << "Unrecognized option: " << name << endl;
			break;
		}
	}
	infile.close();

	edited = false;
}

int LinkApp::clock() {
	return iclock;
}

string LinkApp::clockStr(int maxClock) {
	if (iclock>maxClock) setClock(maxClock);
	return sclock;
}

void LinkApp::setClock(int mhz) {
	iclock = constrain(mhz,50,325);
	stringstream ss;
	sclock = "";
	ss << iclock << "MHZ";
	ss >> sclock;

	edited = true;
}

/*G
int LinkApp::gamma() {
	return igamma;
}

string LinkApp::gammaStr() {
	return sgamma;
}

void LinkApp::setGamma(int gamma) {
	igamma = constrain(gamma,0,100);
	stringstream ss;
	sgamma = "";
	ss << igamma;
	ss >> sgamma;

	edited = true;
}
*/

bool LinkApp::targetExists() {
#ifndef TARGET_GP2X
	return true; //For displaying elements during testing on pc
#endif

	string target = exec;
	if (exec!="" && exec[0]!='/' && workdir!="")
		target = workdir + "/" + exec;

	return fileExists(target);
}

bool LinkApp::save() {
	if (!edited) return false;
	cout << "\033[0;34mGMENU2X:\033[0m Saving link " << title << endl;

	ofstream f(file.c_str());
	if (f.is_open()) {
		if (title!=""          ) f << "title="           << title           << endl;
		if (description!=""    ) f << "description="     << description     << endl;
		if (icon!=""           ) f << "icon="            << icon            << endl;
		if (exec!=""           ) f << "exec="            << exec            << endl;
		if (params!=""         ) f << "params="          << params          << endl;
		if (workdir!=""        ) f << "workdir="         << workdir         << endl;
		if (iclock!=0          ) f << "clock="           << iclock          << endl;
		//G if (igamma!=0          ) f << "gamma="           << igamma          << endl;
		if (selectordir!=""    ) f << "selectordir="     << selectordir     << endl;
		if (selectorfilter!="" ) f << "selectorfilter="  << selectorfilter  << endl;
		if (selectorscreens!="") f << "selectorscreens=" << selectorscreens << endl;
		if (aliasfile!=""      ) f << "selectoraliases=" << aliasfile       << endl;
		if (wrapper            ) f << "wrapper=true"                        << endl;
		if (dontleave          ) f << "dontleave=true"                      << endl;
		f.close();
		return true;
	} else
		cout << "\033[0;34mGMENU2X:\033[0;31m Error while opening the file '" << file << "' for write\033[0m" << endl;
	return false;
}

void LinkApp::drawRun() {
	//Darkened background
	gmenu2x->s->box(0, 0, 320, 240, 0,0,0,150);

	string text = "Launching "+getTitle();
	int textW = gmenu2x->font->getTextWidth(text);
	int boxW = 62+textW;
	int halfBoxW = boxW/2;

	//outer box
	SDL_Rect r = {158-halfBoxW, 97, halfBoxW*2+5, 47};
	SDL_FillRect(gmenu2x->s->raw, &r, SDL_MapRGB(gmenu2x->s->format(),255,255,255));
	//draw inner rectangle
	rectangleColor(gmenu2x->s->raw, 160-halfBoxW, 99, 160+halfBoxW, 141, SDL_MapRGB(gmenu2x->s->format(),80,80,80));

	int x = 170-halfBoxW;
	if (getIcon()!="")
		gmenu2x->sc[getIcon()]->blit(gmenu2x->s,x,104);
	else
		gmenu2x->sc["icons/generic.png"]->blit(gmenu2x->s,x,104);
	gmenu2x->s->write( gmenu2x->font, text, x+42, 121, SFontHAlignLeft, SFontVAlignMiddle );
	gmenu2x->s->flip();
}

void LinkApp::run() {
	if (selectordir!="")
		selector();
	else
		launch();
}

void LinkApp::selector(int startSelection, string selectorDir) {
	//Run selector interface
	Selector sel(gmenu2x, this, selectorDir);
	int selection = sel.exec(startSelection);
	if (selection!=-1) {
		gmenu2x->writeTmp(selection,sel.dir);
		launch(sel.file, sel.dir);
	}
}

void LinkApp::launch(string selectedFile, string selectedDir) {
	drawRun();
	save();
#ifndef TARGET_GP2X
	//delay for testing
	SDL_Delay(1000);
#endif

	//Set correct working directory
	string wd = workdir;
	if (wd=="") {
		string::size_type pos = exec.rfind("/");
		if (pos!=string::npos)
			wd = exec.substr(0,pos);
	}
	if (wd!="") {
		if (wd[0]!='/') wd = path + wd;
		cout << "\033[0;34mGMENU2X:\033[0m chdir '" << wd << "'" << endl;
		chdir(wd.c_str());
	}

	//selectedFile
	if (selectedFile!="") {
		string selectedFileExtension;
		string::size_type i = selectedFile.rfind(".");
		if (i != string::npos) {
			selectedFileExtension = selectedFile.substr(i,selectedFile.length());
			selectedFile = selectedFile.substr(0,i);
		}

		if (selectedDir=="")
			selectedDir = getSelectorDir();
		if (params=="") {
			params = cmdclean(selectedDir+selectedFile+selectedFileExtension);
		} else {
			params = strreplace(params,"[selFullPath]",cmdclean(selectedDir+selectedFile+selectedFileExtension));
			params = strreplace(params,"[selPath]",cmdclean(selectedDir));
			params = strreplace(params,"[selFile]",cmdclean(selectedFile));
			params = strreplace(params,"[selExt]",cmdclean(selectedFileExtension));
		}
	}

	if (clock()!=gmenu2x->menuClock)
		gmenu2x->setClock(clock());

	cout << "\033[0;34mGMENU2X:\033[0m Executing '" << title << "' (" << exec << ") (" << params << ")" << endl;

	//check if we have to quit
	string command = cmdclean(exec);
	
	// Check to see if permissions are desirable
	struct stat fstat;
	if( stat( command.c_str(), &fstat ) == 0 ) {
		struct stat newstat = fstat;
		if( S_IRUSR != ( fstat.st_mode & S_IRUSR ) )
			newstat.st_mode |= S_IRUSR;
		if( S_IXUSR != ( fstat.st_mode & S_IXUSR ) )
			newstat.st_mode |= S_IXUSR;
		if( fstat.st_mode != newstat.st_mode )
			chmod( command.c_str(), newstat.st_mode );
	} // else, well.. we are no worse off :)
	
	if (params!="") command += " " + params;
	if (wrapper) command += "; sync & cd "+cmdclean(path)+"; exec ./gmenu2x";
	if (dontleave) {
		system(command.c_str());
	} else {
		if (gmenu2x->saveSelection && (gmenu2x->startSectionIndex!=gmenu2x->menu->selSectionIndex() || gmenu2x->startLinkIndex!=gmenu2x->menu->selLinkIndex()))
			gmenu2x->writeConfig();
		if (selectedFile=="")
			gmenu2x->writeTmp();
		SDL_Quit();
		//G if (gamma()!=0 && gamma()!=gmenu2x->gamma)
		//G 	gmenu2x->setGamma(gamma());
		execlp("/bin/sh","/bin/sh","-c",command.c_str(),NULL);
		//if execution continues then something went wrong and as we already called SDL_Quit we cannot continue
		//try relaunching gmenu2x
		chdir(path.c_str());
		execlp("./gmenu2x", "./gmenu2x", NULL);
	}
	

	chdir(path.c_str());
}

string LinkApp::getExec() {
	return exec;
}

void LinkApp::setExec(string exec) {
	this->exec = exec;
	edited = true;
}

string LinkApp::getParams() {
	return params;
}

void LinkApp::setParams(string params) {
	this->params = params;
	edited = true;
}

string LinkApp::getWorkdir() {
	return workdir;
}

void LinkApp::setWorkdir(string workdir) {
	this->workdir = workdir;
	edited = true;
}

string LinkApp::getSelectorDir() {
	return selectordir;
}

void LinkApp::setSelectorDir(string selectordir) {
	if (selectordir!="" && selectordir[selectordir.length()-1]!='/') selectordir += "/";
	this->selectordir = selectordir;
	edited = true;
}

string LinkApp::getSelectorFilter() {
	return selectorfilter;
}

void LinkApp::setSelectorFilter(string selectorfilter) {
	this->selectorfilter = selectorfilter;
	edited = true;
}

string LinkApp::getSelectorScreens() {
	return selectorscreens;
}

void LinkApp::setSelectorScreens(string selectorscreens) {
	this->selectorscreens = selectorscreens;
	edited = true;
}

string LinkApp::getAliasFile() {
	return aliasfile;
}

void LinkApp::setAliasFile(string aliasfile) {
	if (fileExists(aliasfile)) {
		this->aliasfile = aliasfile;
		edited = true;
	}
}
