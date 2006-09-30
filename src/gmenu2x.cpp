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

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <signal.h>

//for statfs
#include <sys/vfs.h>
#include <errno.h>

#ifdef TARGET_GP2X
#include <SDL_gp2x.h>
#include <SDL_joystick.h>
#include "gp2x.h"
#include <sys/fcntl.h> //for battery
#endif

//for browsing the filesystem
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include "menu.h"
#include "asfont.h"
#include "surface.h"
#include "filedialog.h"
#include "gmenu2x.h"

#include "inputdialog.h"
#include "settingsdialog.h"
#include "menusettingint.h"
#include "menusettingbool.h"
#include "menusettingrgba.h"
#include "menusettingstring.h"
#include "menusettingmultistring.h"
#include "menusettingfile.h"
#include "menusettingdir.h"

#include <sys/mman.h>

using namespace std;
using namespace fastdelegate;

int main(int argc, char *argv[]) {
	signal(SIGINT,&exit);
	GMenu2X app(argc,argv);
	return 0;
}

void GMenu2X::gp2x_init() {
#ifdef TARGET_GP2X
if (!gp2x_initialized) {
	gp2x_mem = open("/dev/mem", O_RDWR);
	gp2x_memregs=(unsigned short *)mmap(0, 0x10000, PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_mem, 0xc0000000);
	MEM_REG=&gp2x_memregs[0];

	gp2x_initialized = true;
}
#endif
}

void GMenu2X::gp2x_deinit() {
#ifdef TARGET_GP2X
if (gp2x_initialized) {
	gp2x_memregs[0x28DA>>1]=0x4AB;
	gp2x_memregs[0x290C>>1]=640;
	close(gp2x_mem);

	gp2x_initialized = false;
}
#endif
}

GMenu2X::GMenu2X(int argc, char *argv[]) {
	gp2x_initialized = false;
	//Initialize configuration settings to default
	topBarColor.r = 255;
	topBarColor.g = 255;
	topBarColor.b = 255;
	topBarColor.a = 130;
	bottomBarColor.r = 255;
	bottomBarColor.g = 255;
	bottomBarColor.b = 255;
	bottomBarColor.a = 130;
	selectionColor.r = 255;
	selectionColor.g = 255;
	selectionColor.b = 255;
	selectionColor.a = 130;
	saveSelection = true;
	maxClock = 300;
	menuClock = 100;
	//G gamma = 10;
	startSectionIndex = 0;
	startLinkIndex = 0;

	samba = inet = web = false;

	//load config data
	readConfig();
	readCommonIni();

	path = getExePath();

#ifdef TARGET_GP2X
	gp2x_init();
	if (gp2x_memregs[0x2800>>1]&0x100) {
		gp2x_memregs[0x2906>>1]=512;
	}
	gp2x_deinit();
#endif

	//Screen
	cout << "\033[0;34mGMENU2X:\033[0m Initializing screen..." << endl;
	if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK)<0 ) {
		cout << "\033[0;34mGMENU2X:\033[0;31m Could not initialize SDL:\033[0m " << SDL_GetError() << endl;
		SDL_Quit();
	}
	s = new Surface();
	SDL_JoystickOpen(0);
	s->raw = SDL_SetVideoMode(320, 240, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
	SDL_ShowCursor(0);

	font = new ASFont( sc["imgs/font.png"]->raw );

	//Menu structure handler
	menu = new Menu(this,path);
	for (uint i=0; i<menu->sections.size(); i++) {
		string sectionIcon = "sections/"+menu->sections[i]+".png";
		if (fileExists(sectionIcon))
			sc.add(sectionIcon);
	}
	menu->setSectionIndex(startSectionIndex);
	menu->setLinkIndex(startLinkIndex);

	initBG();

	//Events
#ifdef TARGET_GP2X
	joy.init(0);
#endif
	setInputSpeed();

	initServices();

	//G gp2x_init();
	//G if (gamma!=10) setGamma(gamma);
	setClock(menuClock);
	//G gp2x_deinit();

	main();
	writeConfig();

	SDL_Quit();
	exit(0);
}

GMenu2X::~GMenu2X() {
	free(menu);
	free(s);
	free(font);
}

void GMenu2X::readConfig() {
	string conffile = path+"gmenu2x.conf";
	if (fileExists(conffile)) {
		ifstream inf(conffile.c_str(), ios_base::in);
		if (inf.is_open()) {
			string line;
			while (getline(inf, line, '\n')) {
				string::size_type pos = line.find("=");
				string name = trim(line.substr(0,pos));
				string value = trim(line.substr(pos+1,line.length()));

				if (name=="selectionColorR") selectionColor.r = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="selectionColorG") selectionColor.g = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="selectionColorB") selectionColor.b = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="selectionColorA") selectionColor.a = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="topBarColorR") topBarColor.r = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="topBarColorG") topBarColor.g = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="topBarColorB") topBarColor.b = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="topBarColorA") topBarColor.a = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="bottomBarColorR") bottomBarColor.r = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="bottomBarColorG") bottomBarColor.g = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="bottomBarColorB") bottomBarColor.b = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="bottomBarColorA") bottomBarColor.a = constrain( atoi(value.c_str()), 0, 255 );
				else if (name=="saveSelection") saveSelection = value == "on" ? true : false;
				else if (name=="section") startSectionIndex = atoi(value.c_str());
				else if (name=="link") startLinkIndex = atoi(value.c_str());
				else if (name=="menuClock") menuClock = constrain( atoi(value.c_str()), 50,300 );
				else if (name=="maxClock") maxClock = constrain( atoi(value.c_str()), 50,300 );
				//G else if (name=="gamma") gamma = constrain( atoi(value.c_str()), 1,100 );
			}
			inf.close();
		}
	}
}

void GMenu2X::writeConfig() {
	ledOn();
	string conffile = path+"gmenu2x.conf";
	ofstream inf(conffile.c_str());
	if (inf.is_open()) {
		if (saveSelection) {
			startSectionIndex = menu->selSectionIndex();
			startLinkIndex = menu->selLinkIndex();
		}

		inf << "selectionColorR=" << selectionColor.r << endl;
		inf << "selectionColorG=" << selectionColor.g << endl;
		inf << "selectionColorB=" << selectionColor.b << endl;
		inf << "selectionColorA=" << selectionColor.a << endl;
		inf << "topBarColorR=" << topBarColor.r << endl;
		inf << "topBarColorG=" << topBarColor.g << endl;
		inf << "topBarColorB=" << topBarColor.b << endl;
		inf << "topBarColorA=" << topBarColor.a << endl;
		inf << "bottomBarColorR=" << bottomBarColor.r << endl;
		inf << "bottomBarColorG=" << bottomBarColor.g << endl;
		inf << "bottomBarColorB=" << bottomBarColor.b << endl;
		inf << "bottomBarColorA=" << bottomBarColor.a << endl;
		inf << "saveSelection=" << ( saveSelection ? "on" : "off" ) << endl;
		inf << "section=" << startSectionIndex << endl;
		inf << "link=" << startLinkIndex << endl;
		inf << "menuClock=" << menuClock << endl;
		inf << "maxClock=" << maxClock << endl;
		//G inf << "gamma=" << gamma << endl;
		inf.close();
		sync();
	}
	ledOff();
}

void GMenu2X::readCommonIni() {
	if (fileExists("/usr/gp2x/common.ini")) {
		ifstream inf("/usr/gp2x/common.ini", ios_base::in);
		if (inf.is_open()) {
			string line;
			string section = "";
			while (getline(inf, line, '\n')) {
				line = trim(line);
				if (line[0]=='[' && line[line.length()-1]==']') {
					section = line.substr(1,line.length()-2);
				} else {
					string::size_type pos = line.find("=");
					string name = trim(line.substr(0,pos));
					string value = trim(line.substr(pos+1,line.length()));

					if (section=="usbnet") {
						if (name=="enable")
							usbnet = value=="true" ? true : false;
						else if (name=="ip")
							ip = value;

					} else if (section=="server") {
						if (name=="inet")
							inet = value=="true" ? true : false;
						else if (name=="samba")
							samba = value=="true" ? true : false;
						else if (name=="web")
							web = value=="true" ? true : false;
					}
				}
			}
			inf.close();
		}
	}
}

void GMenu2X::writeCommonIni() {}

void GMenu2X::initServices() {
#ifdef TARGET_GP2X
	if (usbnet) {
		string services = "scripts/services.sh "+ip+" "+(inet?"on":"off")+" "+(samba?"on":"off")+" "+(web?"on":"off")+" &";
		system(services.c_str());
	}
#endif
}

void GMenu2X::ledOn() {
#ifdef TARGET_GP2X
	SDL_SYS_JoystickGp2xSys(joy.joystick, BATT_LED_ON);
#endif
}

void GMenu2X::ledOff() {
#ifdef TARGET_GP2X
	SDL_SYS_JoystickGp2xSys(joy.joystick, BATT_LED_OFF);
#endif
}

int GMenu2X::main() {
	bool quit = false, useSelectionPng = fileExists("imgs/selection.png");
	int x,y,ix, offset = menu->links.size()>24 ? 0 : 4;
	uint i;
	long tickBattery = -60000, tickNow;
	string batteryIcon = "imgs/battery/0.png";

	while (!quit) {
		//Background
		sc["imgs/bg.png"]->blit(s,0,0);

		//Sections
		if (menu->firstDispSection()>0)
			sc["imgs/left.png"]->blit(s,1,16);
		if (menu->firstDispSection()+5<menu->sections.size())
			sc["imgs/right.png"]->blit(s,311,16);
		for (i=menu->firstDispSection(); i<menu->sections.size() && i<menu->firstDispSection()+5; i++) {
			string sectionIcon = "sections/"+menu->sections[i]+".png";
			x = (i-menu->firstDispSection())*60+24;
			if (menu->selSectionIndex()==(int)i)
				s->box(x-14, 0, 60, 40, selectionColor);
			if (sc.exists(sectionIcon))
				sc[sectionIcon]->blit(s,x,0,32,32);
			else
				sc["icons/section.png"]->blit(s,x,0);
			s->write( font, menu->sections[i], x+16, 41, SFontHAlignCenter, SFontVAlignBottom );
		}

		//Links
		for (i=menu->firstDispRow()*6; i<(menu->firstDispRow()*6)+24 && i<menu->links.size(); i++) {
			int ir = i-menu->firstDispRow()*6;
			x = (ir%6)*52+offset;
			y = (ir/6+1)*41+1;
			ix = x+10;

			if (menu->selLink()==menu->links[i]) {
				if (useSelectionPng)
					sc["imgs/selection.png"]->blitCenter(s,x+25,y+20);
				else
					s->box(x, y, 50, 41, selectionColor);
			}

			if (menu->links[i]->getIcon() != "")
				sc[menu->links[i]->getIcon()]->blit(s,ix,y,32,32);
			else
				sc["icons/generic.png"]->blit(s,ix,y,32,32);

			s->write( font, menu->links[i]->getTitle(), ix+16, y+43, SFontHAlignCenter, SFontVAlignBottom );
		}
		drawScrollBar(4,menu->links.size()/6 + ((menu->links.size()%6==0) ? 0 : 1),menu->firstDispRow(),43,159);

		if (menu->selLink()!=NULL) {
			s->write ( font, menu->selLink()->getDescription(), 160, 221, SFontHAlignCenter, SFontVAlignBottom );
			s->write ( font, menu->selLink()->clockStr(maxClock), cpuX, 230, SFontHAlignLeft, SFontVAlignMiddle );
		}

		//battery
		tickNow = SDL_GetTicks();
		//check battery status every 60 seconds
		if (tickNow-tickBattery >= 60000) {
			tickBattery = tickNow;
			unsigned short battlevel = getBatteryLevel();
			if (battlevel>5) {
				batteryIcon = "imgs/battery/ac.png";
			} else {
				stringstream ss;
				ss << battlevel;
				ss >> batteryIcon;
				batteryIcon = "imgs/battery/"+batteryIcon+".png";
			}
		}
		sc[batteryIcon]->blit( s, 301, 222 );

#ifdef TARGET_GP2X
		joy.update();
		if ( joy[GP2X_BUTTON_START] ) options();
		// LINK NAVIGATION
		if ( joy[GP2X_BUTTON_LEFT ] ) menu->linkLeft();
		if ( joy[GP2X_BUTTON_RIGHT] ) menu->linkRight();
		if ( joy[GP2X_BUTTON_UP   ] ) menu->linkUp();
		if ( joy[GP2X_BUTTON_DOWN ] ) menu->linkDown();
		// CLOCK
		if ( joy[GP2X_BUTTON_VOLDOWN] && !joy[GP2X_BUTTON_VOLUP] )
			menu->selLink()->setClock( constrain(menu->selLink()->clock()-1,50,maxClock) );
		if ( joy[GP2X_BUTTON_VOLUP] && !joy[GP2X_BUTTON_VOLDOWN] )
			menu->selLink()->setClock( constrain(menu->selLink()->clock()+1,50,maxClock) );
		if ( joy[GP2X_BUTTON_VOLUP] && joy[GP2X_BUTTON_VOLDOWN] ) menu->selLink()->setClock(200);
		// SECTIONS
		if ( joy[GP2X_BUTTON_L     ] ) {
			menu->decSectionIndex();
			offset = menu->links.size()>24 ? 0 : 4;
		}
		if ( joy[GP2X_BUTTON_R     ] ) {
			menu->incSectionIndex();
			offset = menu->links.size()>24 ? 0 : 4;
		}
		if ( joy[GP2X_BUTTON_B] || joy[GP2X_BUTTON_CLICK] && menu->selLink()!=NULL ) menu->selLink()->run();
		if ( joy[GP2X_BUTTON_SELECT] ) contextMenu();
#else
		while (SDL_PollEvent(&event)) {
			if ( event.type == SDL_QUIT ) quit = true;
			if ( event.type==SDL_KEYDOWN ) {
				if ( event.key.keysym.sym==SDLK_ESCAPE ) quit = true;
				// LINK NAVIGATION
				if ( event.key.keysym.sym==SDLK_LEFT   ) menu->linkLeft();
				if ( event.key.keysym.sym==SDLK_RIGHT  ) menu->linkRight();
				if ( event.key.keysym.sym==SDLK_UP     ) menu->linkUp();
				if ( event.key.keysym.sym==SDLK_DOWN   ) menu->linkDown();
				// CLOCK
				if ( event.key.keysym.sym==SDLK_z      )
					menu->selLink()->setClock( constrain(menu->selLink()->clock()-1,50,maxClock) );
				if ( event.key.keysym.sym==SDLK_x      )
					menu->selLink()->setClock( constrain(menu->selLink()->clock()+1,50,maxClock) );
				// SECTIONS
				if ( event.key.keysym.sym==SDLK_q      ) {
					menu->decSectionIndex();
					offset = menu->links.size()>24 ? 0 : 4;
				}
				if ( event.key.keysym.sym==SDLK_w      ) {
					menu->incSectionIndex();
					offset = menu->links.size()>24 ? 0 : 4;
				}
				if ( event.key.keysym.sym==SDLK_s      ) options();
				if ( event.key.keysym.sym==SDLK_RETURN && menu->selLink()!=NULL ) menu->selLink()->run();
				if ( event.key.keysym.sym==SDLK_SPACE  ) contextMenu();
			}
		}
#endif

		s->flip();
	}

	return -1;
}

void GMenu2X::options() {
	int curMenuClock = menuClock;
	//G int prevgamma = gamma;

	SettingsDialog sd(this,"Settings");
	sd.addSetting(new MenuSettingBool(this,"Save last selection","Save the last selected link and section on exit",&saveSelection));
	sd.addSetting(new MenuSettingInt(this,"Clock for GMenu2X","Set the cpu working frequency when running GMenu2X",&menuClock,50,325));
	sd.addSetting(new MenuSettingInt(this,"Maximum overclock","Set the maximum overclock for launching links",&maxClock,50,325));
	//G sd.addSetting(new MenuSettingInt(this,"Gamma","Set gp2x gamma value (default=10)",&gamma,1,100));
	sd.addSetting(new MenuSettingRGBA(this,"Top Bar Color","Color of the top bar",&topBarColor));
	sd.addSetting(new MenuSettingRGBA(this,"Bottom Bar Color","Color of the bottom bar",&bottomBarColor));
	sd.addSetting(new MenuSettingRGBA(this,"Selection Color","Color of the selection and other interface details",&selectionColor));
	if (sd.exec() && sd.edited()) {
		//G if (prevgamma!=gamma) setGamma(gamma);
		if (curMenuClock!=menuClock) setClock(menuClock);
		writeConfig();
		initBG();
	}
}

void GMenu2X::contextMenu() {
	Surface bg(s);
	//Darken background
	bg.box(0, 0, 320, 240, 0,0,0,150);

	vector<MenuOption> voices;
	{
	MenuOption opt = {"Add link in "+menu->selSection(), MakeDelegate(this, &GMenu2X::addLink)};
	voices.push_back(opt);
	}

	if (menu->selLink()!=NULL) {
		{
		MenuOption opt = {"Edit "+menu->selLink()->getTitle(), MakeDelegate(this, &GMenu2X::editLink)};
		voices.push_back(opt);
		}
		{
		MenuOption opt = {"Delete "+menu->selLink()->getTitle()+" link", MakeDelegate(this, &GMenu2X::deleteLink)};
		voices.push_back(opt);
		}
	}

	{
	MenuOption opt = {"Add section", MakeDelegate(this, &GMenu2X::addSection)};
	voices.push_back(opt);
	}
	{
	MenuOption opt = {"Rename section", MakeDelegate(this, &GMenu2X::renameSection)};
	voices.push_back(opt);
	}
	{
	MenuOption opt = {"Delete section", MakeDelegate(this, &GMenu2X::deleteSection)};
	voices.push_back(opt);
	}
	{
	MenuOption opt = {"Scan for applications and games", MakeDelegate(this, &GMenu2X::scanner)};
	voices.push_back(opt);
	}

	bool close = false;
	uint i, sel = 0;

	int h = font->getHeight();
	SDL_Rect box;
	box.h = (h+2)*voices.size()+8;
	box.w = 0;
	for (i=0; i<voices.size(); i++) {
		int w = font->getTextWidth(voices[i].text);
		if (w>box.w) box.w = w;
	}
	box.w += 23;
	box.x = 160 - box.w/2;
	box.y = 120 - box.h/2;

	SDL_Rect selbox = {box.x+4, 0, box.w-8, h+2};

	while (!close) {
		bg.blit(s,0,0);
		SDL_FillRect( s->raw, &box, SDL_MapRGB(s->format(),255,255,255));
		selbox.y = box.y+4+(h+2)*sel;
		SDL_FillRect( s->raw, &selbox, SDL_MapRGB(s->format(),160,160,160) );
		rectangleColor( s->raw, box.x+2, box.y+2, box.x+box.w-3, box.y+box.h-3, SDL_MapRGB(s->format(),80,80,80) );
		for (i=0; i<voices.size(); i++) {
			s->write( font, voices[i].text, box.x+12, box.y+10+(h+2)*i, SFontHAlignLeft, SFontVAlignMiddle );
		}

#ifdef TARGET_GP2X
		joy.update();
		if ( joy[GP2X_BUTTON_SELECT] ) close = true;
		if ( joy[GP2X_BUTTON_UP    ] ) sel = max(0, sel-1);
		if ( joy[GP2X_BUTTON_DOWN  ] ) sel = min(voices.size()-1, sel+1);
		if ( joy[GP2X_BUTTON_B] || joy[GP2X_BUTTON_CLICK] ) { voices[sel].action(); return; }
#else
		while (SDL_PollEvent(&event)) {
			if ( event.type == SDL_QUIT ) return;
			if ( event.type==SDL_KEYDOWN ) {
				if ( event.key.keysym.sym==SDLK_ESCAPE ) close = true;
				if ( event.key.keysym.sym==SDLK_UP ) sel = max(0, sel-1);
				if ( event.key.keysym.sym==SDLK_DOWN ) sel = min((int)voices.size()-1, sel+1);
				if ( event.key.keysym.sym==SDLK_RETURN ) { voices[sel].action(); return; }
			}
		}
#endif

		s->flip();
	}
}

void GMenu2X::addLink() {
	FileDialog fd(this,"Select an application");
	if (fd.exec()) {
		ledOn();
		createLink(fd.path, fd.file);
		sync();
		ledOff();
		menu->setSectionIndex( menu->selSectionIndex() ); //Force a reload of current section links
	}
}

void GMenu2X::editLink() {
	vector<string> pathV;
	split(pathV,menu->selLink()->file,"/");
	string oldSection = "";
	if (pathV.size()>1)
		oldSection = pathV[pathV.size()-2];
	string newSection = oldSection;

	string linkTitle = menu->selLink()->getTitle();
	string linkDescription = menu->selLink()->getDescription();
	string linkIcon = menu->selLink()->getIcon();
	string linkParams = menu->selLink()->getParams();
	string linkSelFilter = menu->selLink()->getSelectorFilter();
	string linkSelDir = menu->selLink()->getSelectorDir();
	string linkSelScreens = menu->selLink()->getSelectorScreens();
	string linkSelAliases = menu->selLink()->getAliasFile();
	int linkClock = menu->selLink()->clock();
	//G int linkGamma = menu->selLink()->gamma();

	SettingsDialog sd(this,"Edit link");
	sd.addSetting(new MenuSettingString(this,"Title","Link title",&linkTitle));
	sd.addSetting(new MenuSettingString(this,"Description","Link description",&linkDescription));
	sd.addSetting(new MenuSettingMultiString(this,"Section","The section this link belongs to",&newSection,&menu->sections));
	sd.addSetting(new MenuSettingFile(this,"Icon","Select an icon for the link",&linkIcon,".png,.bmp,.jpg,.jpeg"));
	sd.addSetting(new MenuSettingInt(this,"Clock (default=200)","Cpu clock frequency to set when launching this link",&linkClock,50,maxClock));
	sd.addSetting(new MenuSettingString(this,"Parameters","Parameters to pass to the application",&linkParams));
	sd.addSetting(new MenuSettingDir(this,"Selector Directory","Directory to scan for the selector",&linkSelDir));
	sd.addSetting(new MenuSettingString(this,"Selector Filter","Filter for the selector (Separate values with a comma)",&linkSelFilter));
	sd.addSetting(new MenuSettingDir(this,"Selector Screenshots","Directory of the screenshots for the selector",&linkSelScreens));
	sd.addSetting(new MenuSettingFile(this,"Selector Aliases","File containing a list of aliases to use for the selector's files",&linkSelAliases));
	//G sd.addSetting(new MenuSettingInt(this,"Gamma (0=default)","Gamma value to set when launching this link",&linkGamma,0,100));
	sd.addSetting(new MenuSettingBool(this,"Wrapper","Explicitly relaunch GMenu2X after this link's execution ends",&menu->selLink()->wrapper));
	sd.addSetting(new MenuSettingBool(this,"Don't Leave","Don't quit GMenu2X when launching this link",&menu->selLink()->dontleave));

	if (sd.exec() && sd.edited()) {
		ledOn();

		menu->selLink()->setTitle(linkTitle);
		menu->selLink()->setDescription(linkDescription);
		menu->selLink()->setIcon(linkIcon);
		menu->selLink()->setParams(linkParams);
		menu->selLink()->setSelectorFilter(linkSelFilter);
		menu->selLink()->setSelectorDir(linkSelDir);
		menu->selLink()->setSelectorScreens(linkSelScreens);
		menu->selLink()->setAliasFile(linkSelAliases);
		menu->selLink()->setClock(linkClock);
		//G menu->selLink()->setGamma(linkGamma);

		//if section changed move file and update link->file
		if (oldSection!=newSection) {
			if (find(menu->sections.begin(),menu->sections.end(),newSection)==menu->sections.end()) return;
			string newFileName = "sections/"+newSection+"/"+linkTitle;
			int x=2;
			while (fileExists(newFileName)) {
				string id = "";
				stringstream ss; ss << x; ss >> id;
				newFileName = "sections/"+newSection+"/"+linkTitle+id;
				x++;
			}
			rename(menu->selLink()->file.c_str(),newFileName.c_str());
			menu->selLink()->file = newFileName;
		}
		menu->selLink()->save();
		sync();

		ledOff();
		if (oldSection!=newSection)
			menu->setSectionIndex( menu->selSectionIndex() );
	}
}

void GMenu2X::deleteLink() {
	ledOn();
	unlink(menu->selLink()->file.c_str());
	sc.del(menu->selLink()->getIcon());
	menu->setSectionIndex( menu->selSectionIndex() ); //Force a reload of current section links
	sync();
	ledOff();
}

bool GMenu2X::createLink(string path, string file, string section) {
	if (section=="")
		section = menu->selSection();
	else if (find(menu->sections.begin(),menu->sections.end(),section)==menu->sections.end()) {
		//section directory doesn't exists
		string sectiondir = "sections/"+section;
		cout << "\033[0;34mGMENU2X:\033[0m mkdir " << sectiondir << endl;
		if (mkdir(sectiondir.c_str(),777)==0)
			menu->sections.push_back(section);
		else
			return false;
	}
	cout << "\033[0;34mGMENU2X:\033[0m createLink section=" << section << " file=" << file << endl;
	if (path[path.length()-1]!='/') path += "/";

	string title = file;
	string::size_type pos = title.rfind(".");
	if (pos!=string::npos && pos>0)
		title = title.substr(0, pos);

	cout << "\033[0;34mGMENU2X:\033[0m Creating link " << title << endl;

	string linkpath = "sections/"+section+"/"+title;
	int x=2;
	while (fileExists(linkpath)) {
		stringstream ss;
		linkpath = "";
		ss << x;
		ss >> linkpath;
		linkpath = "sections/"+section+"/"+title+linkpath; 
		cout << "\033[0;34mGMENU2X:\033[0m linkpath=" << linkpath << endl;
		x++;
	}

	if (title.length()>9) {
		title = title.substr(0,7)+"..";
	}

	ofstream f(linkpath.c_str());
	if (f.is_open()) {
		f << "title=" << title << endl;
		if (fileExists(path+title+".png"))
			f << "icon=" << path << title << ".png" << endl;
		f << "exec=" << path << file << endl;
		f.close();
	} else {
		cout << "\033[0;34mGMENU2X:\033[0;31m Error while opening the file '" << linkpath << "' for write\033[0m" << endl;
		return false;
	}

	return true;
}

void GMenu2X::addSection() {
	InputDialog id(this,"Insert a name for the new section");
	if (id.exec()) {
		//only if a section with the same name does not exist
		if (find(menu->sections.begin(),menu->sections.end(),id.input)==menu->sections.end()) {
			//section directory doesn't exists
			string sectiondir = "sections/"+id.input;
			cout << "\033[0;34mGMENU2X:\033[0m mkdir " << sectiondir << endl;
			ledOn();
			if (mkdir(sectiondir.c_str(),0777)==0) {
				menu->sections.push_back(id.input);
				menu->setSectionIndex( menu->sections.size()-1 ); //switch to the new section
				sync();
			}
			ledOff();
		}
	}
}

void GMenu2X::renameSection() {
	InputDialog id(this,"Insert a name for the new section",menu->selSection());
	if (id.exec()) {
		//only if a section with the same name does not exist & !samename
		if (menu->selSection()!=id.input && find(menu->sections.begin(),menu->sections.end(),id.input)==menu->sections.end()) {
			//section directory doesn't exists
			string newsectiondir = "sections/"+id.input;
			string sectiondir = "sections/"+menu->selSection();
			cout << "\033[0;34mGMENU2X:\033[0m mv " << sectiondir << " " << newsectiondir << endl;
			ledOn();
			if (rename(sectiondir.c_str(), newsectiondir.c_str())==0) {
				string oldicon = sectiondir+".png", newicon = newsectiondir+".png";
				if (fileExists(oldicon) && !fileExists(newicon)) {
					rename(oldicon.c_str(), newicon.c_str());
					sc.move(oldicon, newicon);
				}
				menu->sections[ menu->selSectionIndex() ] = id.input;
				menu->setSectionIndex( menu->selSectionIndex() ); //reload sections
				sync();
			}
			ledOff();
		}
	}
}

void GMenu2X::deleteSection() {
	ledOn();
	if (rmtree(path+"sections/"+menu->selSection())) {
		menu->sections.erase( menu->sections.begin()+menu->selSectionIndex() );
		sc.del("sections/"+menu->selSection()+".png");
		menu->setSectionIndex(0); //reload sections
		sync();
	}
	ledOff();
}

void GMenu2X::scanner() {
	Surface bg("imgs/bg.png");
	drawTopBar(&bg,15);
	bg.write(font,"Link Scanner",160,7,SFontHAlignCenter,SFontVAlignMiddle);
	bg.write(font,"Scanning SD filesystem...",5,20);
	bg.blit(s,0,0);
	s->flip();

	vector<string> files;
	scanPath("/mnt/sd",&files);

	bg.write(font,"Scanning NAND filesystem...",5,35);
	bg.blit(s,0,0);
	s->flip();
	scanPath("/mnt/nand",&files);

	stringstream ss;
	ss << files.size();
	string str = "";
	ss >> str;
	bg.write(font,str+" files found.",5,50);
	bg.write(font,"Creating links...",5,65);
	bg.blit(s,0,0);
	s->flip();

	string path, file;
	string::size_type pos;
	uint linkCount = 0;

	ledOn();
	for (uint i = 0; i<files.size(); i++) {
		pos = files[i].rfind("/");
		if (pos!=string::npos && pos>0) {
			path = files[i].substr(0, pos+1);
			file = files[i].substr(pos+1, files[i].length());
			if (createLink(path,file,"found "+file.substr(file.length()-3,3)))
				linkCount++;
		}
	}

	ss.clear();
	ss << linkCount;
	ss >> str;
	bg.write(font,str+" links created.",5,80);
	bg.blit(s,0,0);
	s->flip();

	sync();
	ledOff();
}

void GMenu2X::scanPath(string path, vector<string> *files) {
	DIR *dirp;
	struct stat st;
	struct dirent *dptr;
	string filepath, ext;

	if (path[path.length()-1]!='/') path += "/";
	if ((dirp = opendir(path.c_str())) == NULL) return;

	while ((dptr = readdir(dirp))) {
		if (dptr->d_name[0]=='.')
			continue;
		filepath = path+dptr->d_name;
		int statRet = stat(filepath.c_str(), &st);
		if (S_ISDIR(st.st_mode))
			scanPath(filepath, files);
		if (statRet != -1) {
			ext = filepath.substr(filepath.length()-4,4);
			if (ext==".gpu" || ext==".gpe")
				files->push_back(filepath);
		}
	}
	
	closedir(dirp);
}

unsigned short GMenu2X::getBatteryLevel() {
#ifdef TARGET_GP2X
	int devbatt = open ("/dev/batt", O_RDONLY);
	if (devbatt<0) return 0;

	int battval = 0;
	unsigned short cbv, min=900, max=0;
	int v;

	for (int i = 0; i < BATTERY_READS; i ++) {
		if (read (devbatt, &cbv, 2) == 2) {
			battval += cbv;
			if (cbv>max) max = cbv;
			if (cbv<min) min = cbv;
		}
	}
	close(devbatt);

	battval -= min+max;
	battval /= BATTERY_READS-2;

	if (battval>=850) return 6;
	if (battval>780) return 5;
	if (battval>740) return 4;
	if (battval>700) return 3;
	if (battval>690) return 2;
	if (battval>680) return 1;
	return 0;
#else
	return 6; //AC Power
#endif
}

void GMenu2X::setInputSpeed() {
#ifdef TARGET_GP2X
	joy.setInterval(150);
	joy.setInterval(30,  GP2X_BUTTON_VOLDOWN);
	joy.setInterval(30,  GP2X_BUTTON_VOLUP  );
	joy.setInterval(500, GP2X_BUTTON_START  );
	joy.setInterval(500, GP2X_BUTTON_SELECT );
	joy.setInterval(300, GP2X_BUTTON_A      );
	joy.setInterval(1000,GP2X_BUTTON_B      );
	joy.setInterval(1000,GP2X_BUTTON_CLICK  );
	joy.setInterval(300, GP2X_BUTTON_L      );
	joy.setInterval(300, GP2X_BUTTON_R      );
#else
	SDL_EnableKeyRepeat(1,150);
#endif
}

void GMenu2X::setClock(unsigned mhz) {
	mhz = constrain(mhz,50,maxClock);
	cout << "\033[0;34mGMENU2X:\033[0m Setting clock speed at " << mhz << "MHZ" << endl;
#ifdef TARGET_GP2X
	bool alreadyInited = gp2x_initialized;
	if (!alreadyInited) gp2x_init();

	unsigned v;
	unsigned mdiv,pdiv=3,scale=0;
	mhz*=1000000;
	mdiv=(mhz*pdiv)/GP2X_CLK_FREQ;
	mdiv=((mdiv-8)<<8) & 0xff00;
	pdiv=((pdiv-2)<<2) & 0xfc;
	scale&=3;
	v=mdiv | pdiv | scale;
	MEM_REG[0x910>>1]=v;

	if (!alreadyInited) gp2x_deinit();
#endif
}

void GMenu2X::setGamma(int gamma) {
	cout << "\033[0;34mGMENU2X:\033[0m Setting gamma to " << gamma << endl;
#ifdef TARGET_GP2X
	bool alreadyInited = gp2x_initialized;
	if (!alreadyInited) gp2x_init();

	float fgamma = (float)constrain(gamma,1,100)/10.0;
	fgamma = 1 / fgamma;
	MEM_REG[0x2880>>1]&=~(1<<12);
	MEM_REG[0x295C>>1]=0;

	for (int i=0; i<256; i++) {
		unsigned short s;
		unsigned char g = (unsigned char)(255.0*pow(i/255.0,fgamma));
		s = (g<<8) | g;
		MEM_REG[0x295E>>1]= s;
		MEM_REG[0x295E>>1]= g;
	}

	if (!alreadyInited) gp2x_deinit();
#endif
}

string GMenu2X::getExePath() {
	char buf[255];
	string p;
	int l = readlink("/proc/self/exe",buf,255);

	p = buf;
	p = p.substr(0,l);
	l = p.rfind("/");
	return p.substr(0,l+1);
}

string GMenu2X::getDiskFree() {
	stringstream ss;
	string df = "";
	struct statfs b;

#ifdef TARGET_GP2X
	int ret = statfs("/mnt/sd", &b);
#else
	int ret = statfs("/mnt/sda1", &b);
#endif
	if (ret==0) {
		ss << b.f_bfree*b.f_bsize/1048576 << "/" << b.f_blocks*b.f_bsize/1048576 << "MB";
		ss >> df;
	} else cout << "\033[0;34mGMENU2X:\033[0;31m statfs failed with error '" << strerror(errno) << "'\033[0m" << endl;
	return df;
}

void GMenu2X::initBG() {
	sc.del("imgs/bg.png");

	drawTopBar(sc["imgs/bg.png"],40);
	drawBottomBar(sc["imgs/bg.png"]);

	Surface sd("imgs/sd.png");
	Surface cpu("imgs/cpu.png");
	string df = getDiskFree();

	sd.blit( sc["imgs/bg.png"], 3, 222 );
	sc["imgs/bg.png"]->write( font, df, 22, 230, SFontHAlignLeft, SFontVAlignMiddle );
	cpuX = 27+font->getTextWidth(df);
	cpu.blit( sc["imgs/bg.png"], cpuX, 222 );
	cpuX += 19;

	//301-3-16
	int serviceX = 282;
	if (web) {
		Surface webserver("imgs/webserver.png");
		webserver.blit( sc["imgs/bg.png"], serviceX, 222 );
		serviceX -= 19;
	}
	if (samba) {
		Surface sambaS("imgs/samba.png");
		sambaS.blit( sc["imgs/bg.png"], serviceX, 222 );
		serviceX -= 19;
	}
	if (inet) {
		Surface inetS("imgs/inet.png");
		inetS.blit( sc["imgs/bg.png"], serviceX, 222 );
		serviceX -= 19;
	}
}

int GMenu2X::drawButton(Surface *s, string btn, string text, int x) {
	filledCircleRGBA(s->raw, x, 230, 7, 0,0,0,255);
	s->write(font, btn, x+1, 230, SFontHAlignCenter, SFontVAlignMiddle);
	s->write(font, text, x+11, 230, SFontHAlignLeft, SFontVAlignMiddle);
	return x+24+font->getTextWidth(text);
}

void GMenu2X::drawScrollBar(uint pagesize, uint totalsize, uint pagepos, uint top, uint height) {
	if (totalsize<=pagesize) return;

	s->rectangle(312, top, 5, height, selectionColor);

	//internal bar total height = height-2
	//bar size
	uint bs = (height-2) * pagesize / totalsize;
	//bar y position
	uint by = (height-2) * pagepos / totalsize;
	by = top+2+by;
	if (by+bs>top+height-2) by = top+height-2-bs;


	s->box(314, by, 1, bs, selectionColor);
}

void GMenu2X::drawTopBar(Surface *s, uint height) {
	if (s==NULL) s = this->s;
	s->box(0, 0, 320, height, topBarColor);
}

void GMenu2X::drawBottomBar(Surface *s, uint height) {
	if (s==NULL) s = this->s;
	s->box(0, 240-height, 320, height, bottomBarColor);
}
