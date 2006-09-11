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

#include "menu.h"
#include "asfont.h"
#include "surface.h"
#include "filedialog.h"
#include "gmenu2x.h"
#include "menusettingint.h"
#include "menusettingbool.h"
#include "menusettingrgba.h"
#include "menusettingstring.h"
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
	gamma = 10;
	startSectionIndex = 0;
	startLinkIndex = 0;

	samba = inet = web = false;

	//load config data
	readConfig();
	readCommonIni();

	path = getExePath();

	//Screen
	cout << "GMENU2X: Initializing screen..." << endl;
	if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK)<0 ) {
		fprintf(stdout, "Could not initialize SDL: %s\n", SDL_GetError());
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

	gp2x_init();
	if (gamma!=10) setGamma(gamma);
	setClock(menuClock);
	gp2x_deinit();

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
				else if (name=="gamma") gamma = constrain( atoi(value.c_str()), 1,100 );
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
		inf << "section=" << menu->selSectionIndex() << endl;
		inf << "link=" << menu->selLinkIndex() << endl;
		inf << "menuClock=" << menuClock << endl;
		inf << "maxClock=" << maxClock << endl;
		inf << "gamma=" << gamma << endl;
		inf.close();
		system("sync");
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
			s->write ( font, menu->selLink()->getDescription(), 160, 220, SFontHAlignCenter, SFontVAlignBottom );
			s->write ( font, menu->selLink()->clockStr(maxClock), cpuX, 230, SFontHAlignLeft, SFontVAlignMiddle );
		}

		//battery
		tickNow = SDL_GetTicks();
		//check battery status every 60 seconds
		if (tickNow-tickBattery >= 60000) {
			tickBattery = tickNow;
			unsigned short battlevel = getBatteryLevel();
			if (battlevel>100) {
				batteryIcon = "imgs/battery/ac.png";
			} else {
				if (battlevel<10)
					batteryIcon = "imgs/battery/0.png";
				else if (battlevel<30)
					batteryIcon = "imgs/battery/1.png";
				else if (battlevel<50)
					batteryIcon = "imgs/battery/2.png";
				else if (battlevel<70)
					batteryIcon = "imgs/battery/3.png";
				else if (battlevel<90)
					batteryIcon = "imgs/battery/4.png";
				else
					batteryIcon = "imgs/battery/5.png";

				cout << "GMENU2X: Battery level " << battlevel << endl;
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
		if ( joy[GP2X_BUTTON_B] || joy[GP2X_BUTTON_CLICK] && menu->selLink()!=NULL ) runLink();
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
				if ( event.key.keysym.sym==SDLK_RETURN && menu->selLink()!=NULL ) runLink();
				if ( event.key.keysym.sym==SDLK_SPACE  ) contextMenu();
			}
		}
#endif

		s->flip();
	}

	return -1;
}

void GMenu2X::options() {
	Surface bg ("imgs/bg.png");

	int curMenuClock = menuClock;

	vector<MenuSetting *> voices;
	voices.resize(7);
	voices[0] = new MenuSettingBool(this,"Save last selection","Save the last selected link and section on exit",&saveSelection);
	voices[1] = new MenuSettingInt(this,"Clock for GMenu2X","Set the cpu working frequency when running GMenu2X",&menuClock,50,325);
	voices[2] = new MenuSettingInt(this,"Maximum overclock","Set the maximum overclock for launching links",&maxClock,50,325);
	voices[3] = new MenuSettingInt(this,"Gamma","Set gp2x gamma value (default=10)",&gamma,1,100);
	voices[4] = new MenuSettingRGBA(this,"Top Bar Color","Color of the top bar",&topBarColor);
	voices[5] = new MenuSettingRGBA(this,"Bottom Bar Color","Color of the bottom bar",&bottomBarColor);
	voices[6] = new MenuSettingRGBA(this,"Selection Color","Color of the selection and other interface details",&selectionColor);

	bool close = false;
	uint i, sel = 0, iY;
	voices[sel]->adjustInput();

	gp2x_init();
	int prevgamma = gamma;

	while (!close) {
		if (prevgamma!=gamma) {
			setGamma(gamma);
			prevgamma = gamma;
		}

		bg.blit(s,0,0);
		drawTopBar(s,15);
		s->write(font, "Settings", 160, 8, SFontHAlignCenter, SFontVAlignMiddle);
		drawBottomBar(s,30);

		//selection
		iY = 18+(sel*17);
		//s->box(2, iY, 316, 16, selectionColor);
		s->box(2, iY, 158, 16, selectionColor);

		//selected option
		voices[sel]->drawSelected(iY);

		for (i=0; i<voices.size(); i++) {
			voices[i]->draw(i*17+18);
		}

		//description at bottom
		s->write(font, voices[sel]->description, 160, 218, SFontHAlignCenter, SFontVAlignMiddle);

#ifdef TARGET_GP2X
		joy.update();
		if ( joy[GP2X_BUTTON_START] ) close = true;
		if ( joy[GP2X_BUTTON_UP    ] ) {
			sel = max(0, sel-1);
			setInputSpeed();
			voices[sel]->adjustInput();
		}
		if ( joy[GP2X_BUTTON_DOWN  ] ) {
			sel = min((int)voices.size()-1, sel+1);
			setInputSpeed();
			voices[sel]->adjustInput();
		}
		voices[sel]->manageInput();
#else
		while (SDL_PollEvent(&event)) {
			if ( event.type == SDL_QUIT ) return;
			if ( event.type==SDL_KEYDOWN ) {
				if ( event.key.keysym.sym==SDLK_ESCAPE ) close = true;
				if ( event.key.keysym.sym==SDLK_UP ) {
					sel = max(0, sel-1);
					setInputSpeed();
					voices[sel]->adjustInput();
				}
				if ( event.key.keysym.sym==SDLK_DOWN ) {
					sel = min((int)voices.size()-1, sel+1);
					setInputSpeed();
					voices[sel]->adjustInput();
				}
				voices[sel]->manageInput();
			}
		}
#endif

		s->flip();
	}

	gp2x_deinit();

	for (i=0; i<voices.size(); i++) {
		free(voices[i]);
	}
	if (curMenuClock!=menuClock) setClock(menuClock);
	writeConfig();
	initBG();
	setInputSpeed();
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
		SDL_FillRect( s->raw, &box, SDL_MapRGB(s->format(),255,255,255) );
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

void GMenu2X::editLink() {
	Surface bg ("imgs/bg.png");

	string linkTitle = menu->selLink()->getTitle();
	string linkDescription = menu->selLink()->getDescription();
	string linkIcon = menu->selLink()->getIcon();
	string linkSelFilter = menu->selLink()->getSelectorFilter();
	string linkSelDir = menu->selLink()->getSelectorDir();
	string linkSelScreens = menu->selLink()->getSelectorScreens();
	int linkClock = menu->selLink()->clock();
	int linkGamma = menu->selLink()->gamma();

	vector<MenuSetting *> voices;
	voices.resize(10);
	voices[0] = new MenuSettingString(this,"Title","Link title",&linkTitle);
	voices[1] = new MenuSettingString(this,"Description","Link description",&linkDescription);
	voices[2] = new MenuSettingFile(this,"Icon","Select an icon for the link",&linkIcon,".png,.bmp,.jpg,.jpeg");
	voices[3] = new MenuSettingInt(this,"Clock (default=200)","Cpu clock frequency to set when launching this link",&linkClock,50,maxClock);
	voices[4] = new MenuSettingString(this,"Selector Filter","Filter for the selector (Separate values with a comma)",&linkSelFilter);
	voices[5] = new MenuSettingDir(this,"Selector Directory","Directory to scan for the selector",&linkSelDir);
	voices[6] = new MenuSettingDir(this,"Selector Screens","Directory of the screenshots for the selector",&linkSelScreens);
	voices[7] = new MenuSettingInt(this,"Gamma (0=default)","Gamma value to set when launching this link",&linkGamma,0,100);
	voices[8] = new MenuSettingBool(this,"Wrapper","Explicitly relaunch GMenu2X after this link's execution ends",&menu->selLink()->dontleave);
	voices[9] = new MenuSettingBool(this,"Don't Leave","Don't quit GMenu2X when launching this link",&menu->selLink()->dontleave);

	bool close = false;
	uint i, sel = 0, iY;
	voices[sel]->adjustInput();

	while (!close) {
		bg.blit(s,0,0);
		drawTopBar(s,15);
		s->write(font, "Edit link", 160, 8, SFontHAlignCenter, SFontVAlignMiddle);
		drawBottomBar(s,30);

		//selection
		iY = 18+(sel*17);
		//s->box(2, iY, 316, 16, selectionColor);
		s->box(2, iY, 158, 16, selectionColor);

		//selected option
		voices[sel]->drawSelected(iY);

		for (i=0; i<voices.size(); i++) {
			voices[i]->draw(i*17+18);
		}

		//description at bottom
		s->write(font, voices[sel]->description, 160, 218, SFontHAlignCenter, SFontVAlignMiddle);

#ifdef TARGET_GP2X
		joy.update();
		if ( joy[GP2X_BUTTON_START] ) close = true;
		if ( joy[GP2X_BUTTON_UP    ] ) {
			sel = max(0, sel-1);
			setInputSpeed();
			voices[sel]->adjustInput();
		}
		if ( joy[GP2X_BUTTON_DOWN  ] ) {
			sel = min((int)voices.size()-1, sel+1);
			setInputSpeed();
			voices[sel]->adjustInput();
		}
		voices[sel]->manageInput();
#else
		while (SDL_PollEvent(&event)) {
			if ( event.type == SDL_QUIT ) return;
			if ( event.type==SDL_KEYDOWN ) {
				if ( event.key.keysym.sym==SDLK_ESCAPE ) close = true;
				if ( event.key.keysym.sym==SDLK_UP ) {
					sel = max(0, sel-1);
					setInputSpeed();
					voices[sel]->adjustInput();
				}
				if ( event.key.keysym.sym==SDLK_DOWN ) {
					sel = min((int)voices.size()-1, sel+1);
					setInputSpeed();
					voices[sel]->adjustInput();
				}
				voices[sel]->manageInput();
			}
		}
#endif

		s->flip();
	}

	for (i=0; i<voices.size(); i++) {
		free(voices[i]);
	}

	menu->selLink()->setTitle(linkTitle);
	menu->selLink()->setDescription(linkDescription);
	menu->selLink()->setIcon(linkIcon);
	menu->selLink()->setSelectorFilter(linkSelFilter);
	menu->selLink()->setSelectorDir(linkSelDir);
	menu->selLink()->setSelectorScreens(linkSelScreens);
	menu->selLink()->setClock(linkClock);
	menu->selLink()->setGamma(linkGamma);
	ledOn();
	menu->selLink()->save();
	system("sync");
	ledOff();

	initBG();
	setInputSpeed();
}

void GMenu2X::addLink() {
	FileDialog fd(this,"Select an application");
	if (fd.exec()) {
		createLink(fd.path, fd.file);
		menu->setSectionIndex( menu->selSectionIndex() ); //Force a reload of current section links
	}
}
void GMenu2X::deleteLink() {
	ledOn();
	unlink(menu->selLink()->file.c_str());
	menu->setSectionIndex( menu->selSectionIndex() ); //Force a reload of current section links
	system("sync");
	ledOff();
}

void GMenu2X::createLink(string path, string file) {
	if (path[path.length()-1]!='/') path += "/";

	string title = file;
	string::size_type pos = title.rfind(".");
	if (pos!=string::npos && pos>0)
		title = title.substr(0, pos);

	cout << "GMENU2X: Creating link " << title << endl;

	string linkpath = "sections/"+menu->selSection()+"/"+title;
	int x=2;
	while (fileExists(linkpath)) {
		stringstream ss;
		ss << "sections/" << menu->selSection() << "/" << title << x;
		ss >> linkpath;
		x++;
	}

	if (title.length()>9) {
		title = title.substr(0,7)+"..";
	}

	ofstream f(linkpath.c_str());
	if (f.is_open()) {
		ledOn();
		f << "title=" << title << endl;
		if (fileExists(path+title+".png"))
			f << "icon=" << path << title << ".png" << endl;
		f << "exec=" << path << file << endl;
		f.close();
		system("sync");
		ledOff();
	} else
		cout << "GMENU2X: Error while opening the file '" << linkpath << "' for write" << endl;
}

unsigned short GMenu2X::getBatteryLevel() {
#ifdef TARGET_GP2X
	int devbatt = open ("/dev/batt", O_RDONLY);
	if (devbatt<0) return 0;

	int battval = 0;
	unsigned short cbv;
	int v;

	for (int i = 0; i < BATTERY_READS; i ++) {
		if (read (devbatt, &cbv, 2) == 2)
			battval += cbv;
	}
 	close(devbatt);

 	battval /= BATTERY_READS;

	if (battval>=850) return 101;

 	battval -= 645; //645 ~= 2.3v (0%) , 745 ~= 2.6v (100%)
 	if (battval<0) battval = 0;
 	//battval = battval*100/xxx; //max-min=xxx
 	if (battval>100) battval = 100;

 	return battval;
#else
	return 101; //>100 = AC Power
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
	cout << "GMENU2X: Setting clock speed at " << mhz << "MHZ" << endl;
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
	cout << "GMENU2X: Setting gamma to " << gamma << endl;
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

void GMenu2X::runLink() {
	if (saveSelection && (startSectionIndex!=menu->selSectionIndex() || startLinkIndex!=menu->selLinkIndex()))
		writeConfig();
	menu->selLink()->run();
}

string GMenu2X::getExePath() {
	stringstream ss;
	ss << "/proc/" << getpid() << "/exe";
	string p;
	ss >> p;
	char buf[255];
	int l = readlink(p.c_str(),buf,255);
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
	} else cout << "GMENU2X: statfs failed with error '" << strerror(errno) << "'" << endl;
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
