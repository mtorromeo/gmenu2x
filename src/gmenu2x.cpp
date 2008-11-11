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

#include <sys/statvfs.h>
#include <errno.h>

#include "gp2x.h"
#include <sys/fcntl.h> //for battery

//for browsing the filesystem
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

//for soundcard
#include <sys/ioctl.h>
#include <linux/soundcard.h>

#include "linkapp.h"
#include "linkaction.h"
#include "menu.h"
#include "asfont.h"
#include "sfontplus.h"
#include "surface.h"
#include "filedialog.h"
#include "gmenu2x.h"
#include "filelister.h"

#include "iconbutton.h"
#include "messagebox.h"
#include "inputdialog.h"
#include "settingsdialog.h"
#include "wallpaperdialog.h"
#include "textdialog.h"
#include "menusettingint.h"
#include "menusettingbool.h"
#include "menusettingrgba.h"
#include "menusettingstring.h"
#include "menusettingmultistring.h"
#include "menusettingfile.h"
#include "menusettingimage.h"
#include "menusettingdir.h"

#include <sys/mman.h>

using namespace std;
using namespace fastdelegate;

int main(int argc, char *argv[]) {
	cout << "----" << endl;
	cout << "GMenu2X starting: If you read this message in the logs, check http://gmenu2x.sourceforge.net/page/Troubleshooting for a solution" << endl;
	cout << "----" << endl;

	signal(SIGINT,&exit);
	GMenu2X app(argc,argv);
	return 0;
}

void GMenu2X::gp2x_init() {
#ifdef TARGET_GP2X
	gp2x_mem = open("/dev/mem", O_RDWR);
	gp2x_memregs=(unsigned short *)mmap(0, 0x10000, PROT_READ|PROT_WRITE, MAP_SHARED, gp2x_mem, 0xc0000000);
	MEM_REG=&gp2x_memregs[0];

	batteryHandle = open(f200 ? "/dev/mmsp2adc" : "/dev/batt", O_RDONLY);
	if (f200) {
		//if wm97xx fails to open, set f200 to false to prevent any further access to the touchscreen
		f200 = ts.init();
	}
#endif
}

void GMenu2X::gp2x_deinit() {
#ifdef TARGET_GP2X
	if (gp2x_mem!=0) {
		gp2x_memregs[0x28DA>>1]=0x4AB;
		gp2x_memregs[0x290C>>1]=640;
		close(gp2x_mem);
	}
	if (batteryHandle!=0) close(batteryHandle);
	if (f200) ts.deinit();
#endif
}

void GMenu2X::gp2x_tvout_on(bool pal) {
#ifdef TARGET_GP2X
	if (gp2x_mem!=0) {
		/*Ioctl_Dummy_t *msg;
		int TVHandle = ioctl(SDL_videofd, FBMMSP2CTRL, msg);*/
		if (cx25874!=0) gp2x_tvout_off();
		//if tv-out is enabled without cx25874 open, stop
		//if (gp2x_memregs[0x2800>>1]&0x100) return;
		cx25874 = open("/dev/cx25874",O_RDWR);
		ioctl(cx25874, _IOW('v', 0x02, unsigned char), pal ? 4 : 3);
		gp2x_memregs[0x2906>>1]=512;
		gp2x_memregs[0x28E4>>1]=gp2x_memregs[0x290C>>1];
		gp2x_memregs[0x28E8>>1]=239;
	}
#endif
}

void GMenu2X::gp2x_tvout_off() {
#ifdef TARGET_GP2X
	if (gp2x_mem!=0) {
		close(cx25874);
		cx25874 = 0;
		gp2x_memregs[0x2906>>1]=1024;
	}
#endif
}

GMenu2X::GMenu2X(int argc, char *argv[]) {
	//Detect firmware version and type
	if (fileExists("/etc/open2x")) {
		fwType = "open2x";
		fwVersion = "";
	} else {
		fwType = "gph";
		fwVersion = "";
	}
#ifdef TARGET_GP2X
	f200 = fileExists("/dev/touchscreen/wm97xx");
#else
	f200 = true;
#endif

	confStr.set_empty_key(" ");
	confStr.set_deleted_key("");
	confInt.set_empty_key(" ");
	confInt.set_deleted_key("");
	skinConfInt.set_empty_key(" ");
	skinConfInt.set_deleted_key("");
	skinConfStr.set_empty_key(" ");
	skinConfStr.set_deleted_key("");
	skinConfColors.set_empty_key(" ");
	skinConfColors.set_deleted_key("");

	//open2x
	savedVolumeMode = 0;
	volumeMode = VOLUME_MODE_NORMAL;
	volumeScalerNormal = VOLUME_SCALER_NORMAL;
	volumeScalerPhones = VOLUME_SCALER_PHONES;

	o2x_usb_net_on_boot = false;
	o2x_usb_net_ip = "";
	o2x_ftp_on_boot = false;
	o2x_telnet_on_boot = false;
	o2x_gp2xjoy_on_boot = false;
	o2x_usb_host_on_boot = false;
	o2x_usb_hid_on_boot = false;
	o2x_usb_storage_on_boot = false;

	usbnet = samba = inet = web = false;
	useSelectionPng = false;

	//load config data
	readConfig();
	if (fwType=="open2x") {
		readConfigOpen2x();
		//	VOLUME MODIFIER
		switch(volumeMode) {
			case VOLUME_MODE_MUTE:   setVolumeScaler(VOLUME_SCALER_MUTE); break;
			case VOLUME_MODE_PHONES: setVolumeScaler(volumeScalerPhones);	break;
			case VOLUME_MODE_NORMAL: setVolumeScaler(volumeScalerNormal); break;
		}
	} else
		readCommonIni();

	halfX = resX/2;
	halfY = resY/2;
	bottomBarIconY = resY-18;
	bottomBarTextY = resY-10;

	path = "";
	getExePath();

#ifdef TARGET_GP2X
	gp2x_mem = 0;
	cx25874 = 0;
	batteryHandle = 0;

	gp2x_init();

	//Fix tv-out
	if (gp2x_mem!=0) {
		if (gp2x_memregs[0x2800>>1]&0x100) {
			gp2x_memregs[0x2906>>1]=512;
			//gp2x_memregs[0x290C>>1]=640;
			gp2x_memregs[0x28E4>>1]=gp2x_memregs[0x290C>>1];
		}
		gp2x_memregs[0x28E8>>1]=239;
	}
#endif

	//Screen
	if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_JOYSTICK)<0 ) {
		cout << "\033[0;34mGMENU2X:\033[0;31m Could not initialize SDL:\033[0m " << SDL_GetError() << endl;
		quit();
	}

	s = new Surface();
#ifdef TARGET_GP2X
	{
		//I use a tmp variable to hide the cursor as soon as possible (and create the double buffer surface only after that)
		//I'm forced to use SW surfaces since with HW there are issuse with changing the clock frequency
		SDL_Surface *tmps = SDL_SetVideoMode(resX, resY, confInt["videoBpp"], SDL_SWSURFACE);
		SDL_ShowCursor(0);
		s->enableVirtualDoubleBuffer(tmps);
	}
#else
	s->raw = SDL_SetVideoMode(resX, resY, confInt["videoBpp"], SDL_HWSURFACE|SDL_DOUBLEBUF);
#endif

	bg = NULL;
	font = NULL;
	menu = NULL;
	setSkin(confStr["skin"], false);
	initMenu();

	if (!fileExists(confStr["wallpaper"])) {
#ifdef DEBUG
		cout << "Searching wallpaper" << endl;
#endif
		FileLister fl("skins/"+confStr["skin"]+"/wallpapers",false,true);
		fl.setFilter(".png,.jpg,.jpeg,.bmp");
		fl.browse();
		if (fl.files.size()<=0 && confStr["skin"] != "Default")
			fl.setPath("skins/Default/wallpapers",true);
		if (fl.files.size()>0)
			confStr["wallpaper"] = fl.getPath()+fl.files[0];
	}

	initBG();
	input.init(path+"input.conf");
	setInputSpeed();
	initServices();

	setGamma(confInt["gamma"]);
	setVolume(confInt["globalVolume"]);
	applyDefaultTimings();
	setClock(confInt["menuClock"]);

	//recover last session
	readTmp();
	if (lastSelectorElement>-1 && menu->selLinkApp()!=NULL && (!menu->selLinkApp()->getSelectorDir().empty() || !lastSelectorDir.empty()))
		menu->selLinkApp()->selector(lastSelectorElement,lastSelectorDir);

#ifdef DEBUG
	cout << "Starting main()" << endl;
#endif
	main();
	writeConfig();
	if (fwType=="open2x") writeConfigOpen2x();

	quit();
	exit(0);
}

GMenu2X::~GMenu2X() {
	free(menu);
	free(s);
	free(font);
}

void GMenu2X::quit() {
	fflush(NULL);
	sc.clear();
	s->free();
	SDL_Quit();
#ifdef TARGET_GP2X
	if (gp2x_mem!=0) {
		//Fix tv-out
		if (gp2x_memregs[0x2800>>1]&0x100) {
			gp2x_memregs[0x2906>>1]=512;
			gp2x_memregs[0x28E4>>1]=gp2x_memregs[0x290C>>1];
		}
		gp2x_deinit();
	}
#endif
}

void GMenu2X::initBG() {
	sc.del("bgmain");

	if (bg != NULL) free(bg);

	if (!fileExists(confStr["wallpaper"])) {
		bg = new Surface(s);
		bg->box(0,0,resX,resY,0,0,0);
	} else {
		bg = new Surface(confStr["wallpaper"],false);
	}

	drawTopBar(bg);
	drawBottomBar(bg);

	Surface *bgmain = new Surface(bg);
	sc.add(bgmain,"bgmain");

	Surface sd("imgs/sd.png", confStr["skin"]);
	Surface cpu("imgs/cpu.png", confStr["skin"]);
	Surface volume("imgs/volume.png", confStr["skin"]);
	string df = getDiskFree();

	sd.blit( sc["bgmain"], 3, bottomBarIconY );
	sc["bgmain"]->write( font, df, 22, bottomBarTextY, SFontHAlignLeft, SFontVAlignMiddle );
	volumeX = 27+font->getTextWidth(df);
	volume.blit( sc["bgmain"], volumeX, bottomBarIconY );
	volumeX += 19;
	cpuX = volumeX+font->getTextWidth("100")+5;
	cpu.blit( sc["bgmain"], cpuX, bottomBarIconY );
	cpuX += 19;
	manualX = cpuX+font->getTextWidth("300Mhz")+5;

	int serviceX = resX-38;
	if (usbnet) {
		if (web) {
			Surface webserver("imgs/webserver.png", confStr["skin"]);
			webserver.blit( sc["bgmain"], serviceX, bottomBarIconY );
			serviceX -= 19;
		}
		if (samba) {
			Surface sambaS("imgs/samba.png", confStr["skin"]);
			sambaS.blit( sc["bgmain"], serviceX, bottomBarIconY );
			serviceX -= 19;
		}
		if (inet) {
			Surface inetS("imgs/inet.png", confStr["skin"]);
			inetS.blit( sc["bgmain"], serviceX, bottomBarIconY );
			serviceX -= 19;
		}
	}
}

void GMenu2X::initFont() {
	if (font != NULL) {
		free(font);
		font = NULL;
	}

	string fontFile = sc.getSkinFilePath("imgs/font.png");
	if (fontFile.empty()) {
		cout << "Font png not found!" << endl;
		quit();
		exit(-1);
	}
	font = new ASFont(fontFile);
}

void GMenu2X::initMenu() {
	//Menu structure handler
	menu = new Menu(this);
	for (uint i=0; i<menu->sections.size(); i++) {
		//Add virtual links in the applications section
		if (menu->sections[i]=="applications") {
			menu->addActionLink(i,"Explorer",MakeDelegate(this,&GMenu2X::explorer),tr["Launch an application"],"skin:icons/explorer.png");
		}

		//Add virtual links in the setting section
		else if (menu->sections[i]=="settings") {
			menu->addActionLink(i,"GMenu2X",MakeDelegate(this,&GMenu2X::options),tr["Configure GMenu2X's options"],"skin:icons/configure.png");
			if (fwType=="open2x")
				menu->addActionLink(i,"Open2x",MakeDelegate(this,&GMenu2X::settingsOpen2x),tr["Configure Open2x system settings"],"skin:icons/o2xconfigure.png");
			menu->addActionLink(i,tr["Skin"],MakeDelegate(this,&GMenu2X::skinMenu),tr["Configure skin"],"skin:icons/skin.png");
			menu->addActionLink(i,tr["Wallpaper"],MakeDelegate(this,&GMenu2X::changeWallpaper),tr["Change GMenu2X wallpaper"],"skin:icons/wallpaper.png");
			menu->addActionLink(i,"TV",MakeDelegate(this,&GMenu2X::toggleTvOut),tr["Activate/deactivate tv-out"],"skin:icons/tv.png");
			menu->addActionLink(i,"USB Sd",MakeDelegate(this,&GMenu2X::activateSdUsb),tr["Activate Usb on SD"],"skin:icons/usb.png");
			if (fwType=="gph" && !f200)
				menu->addActionLink(i,"USB Nand",MakeDelegate(this,&GMenu2X::activateNandUsb),tr["Activate Usb on Nand"],"skin:icons/usb.png");
			if (fileExists(path+"log.txt"))
				menu->addActionLink(i,tr["Log Viewer"],MakeDelegate(this,&GMenu2X::viewLog),tr["Displays last launched program's output"],"skin:icons/ebook.png");
			menu->addActionLink(i,tr["About"],MakeDelegate(this,&GMenu2X::about),tr["Info about GMenu2X"],"skin:icons/about.png");
			//menu->addActionLink(i,"USB Root",MakeDelegate(this,&GMenu2X::activateRootUsb),tr["Activate Usb on the root of the Gp2x Filesystem"],"skin:icons/usb.png");
		}
	}

	menu->setSectionIndex(confInt["section"]);
	menu->setLinkIndex(confInt["link"]);

	menu->loadIcons();
}

void GMenu2X::about() {
	vector<string> text;
	split(text,"GMenu2X is developed by Massimiliano \"Ryo\" Torromeo, and is released under the GPL-v2 license.\n\
Website: http://gmenu2x.sourceforge.net\n\
E-Mail & PayPal account: massimiliano.torromeo@gmail.com\n\
\n\
Thanks goes to...\n\
\n\
 Contributors\n\
----\n\
NoidZ for his gp2x' buttons graphics\n\
\n\
 Beta testers\n\
----\n\
Goemon4, PokeParadox, PSyMastR and Tripmonkey_uk\n\
\n\
 Translators\n\
----\n\
English & Italian by me\n\
French by Yodaz\n\
Danish by claus\n\
Dutch by superfly\n\
Spanish by pedator\n\
Portuguese (Portugal) by NightShadow\n\
Slovak by Jozef\n\
Swedish by Esslan and Micket\n\
German by fusion_power, johnnysnet and Waldteufel\n\
Finnish by Jontte and Atte\n\
Norwegian by cowai\n\
Russian by XaMMaX90\n\
\n\
 Donors\n\
----\n\
EvilDragon (www.gp2x.de)\n\
Tecnologie Creative (www.tecnologiecreative.it)\n\
TelcoLou\n\
gaterooze\n\
deepmenace\n\
superfly\n\
halo9\n\
sbock\n\
b._.o._.b\n\
Jacopastorius\n\
lorystorm90\n\
and all the anonymous donors...\n\
(If I missed to list you or if you want to be removed, contact me.)","\n");
	TextDialog td(this, "GMenu2X", tr.translate("Version $1 (Build date: $2)","0.10-test3",__DATE__,NULL), "icons/about.png", &text);
	td.exec();
}

void GMenu2X::viewLog() {
	string logfile = path+"log.txt";
	if (fileExists(logfile)) {
		ifstream inf(logfile.c_str(), ios_base::in);
		if (inf.is_open()) {
			vector<string> log;

			string line;
			while (getline(inf, line, '\n'))
				log.push_back(line);
			inf.close();

			TextDialog td(this, tr["Log Viewer"], tr["Displays last launched program's output"], "icons/ebook.png", &log);
			td.exec();

			MessageBox mb(this, tr["Do you want to delete the log file?"], "icons/ebook.png");
			mb.buttons[ACTION_B] = tr["Yes"];
			mb.buttons[ACTION_X] = tr["No"];
			if (mb.exec() == ACTION_B) {
				ledOn();
				unlink(logfile.c_str());
				sync();
				menu->deleteSelectedLink();
				ledOff();
			}
		}
	}
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

				if (value.length()>1 && value.at(0)=='"' && value.at(value.length()-1)=='"')
					confStr[name] = value.substr(1,value.length()-2);
				else
					confInt[name] = atoi(value.c_str());
			}
			inf.close();
		}
	}

	if (!confStr["lang"].empty()) tr.setLang(confStr["lang"]);
	if (!confStr["wallpaper"].empty() && !fileExists(confStr["wallpaper"])) confStr["wallpaper"] = "";
	if (confStr["skin"].empty() || !fileExists("skins/"+confStr["skin"])) confStr["skin"] = "Default";

	evalIntConf( &confInt["outputLogs"], 0, 0,1 );
	evalIntConf( &confInt["maxClock"], 300, 200,300 );
	evalIntConf( &confInt["menuClock"], f200 ? 136 : 100, 50,300 );
	evalIntConf( &confInt["globalVolume"], 67, 0,100 );
	evalIntConf( &confInt["gamma"], 1, 1,100 );
	evalIntConf( &confInt["videoBpp"], 16, 8,32 );

	if (confStr["tvoutEncoding"] != "PAL") confStr["tvoutEncoding"] = "NTSC";
	resX = constrain( confInt["resolutionX"], 320,1920 );
	resY = constrain( confInt["resolutionY"], 240,1200 );
}

void GMenu2X::writeConfig() {
	ledOn();
	string conffile = path+"gmenu2x.conf";
	ofstream inf(conffile.c_str());
	if (inf.is_open()) {
		ConfStrHash::iterator endS = confStr.end();
		for(ConfStrHash::iterator curr = confStr.begin(); curr != endS; curr++)
			inf << curr->first << "=\"" << curr->second << "\"" << endl;

		ConfIntHash::iterator endI = confInt.end();
		for(ConfIntHash::iterator curr = confInt.begin(); curr != endI; curr++)
			inf << curr->first << "=" << curr->second << endl;

		inf.close();
		sync();
	}
	ledOff();
}


void GMenu2X::readConfigOpen2x() {
	string conffile = "/etc/config/open2x.conf";
	if (fileExists(conffile)) {
		ifstream inf(conffile.c_str(), ios_base::in);
		if (inf.is_open()) {
			string line;
			while (getline(inf, line, '\n')) {
				string::size_type pos = line.find("=");
				string name = trim(line.substr(0,pos));
				string value = trim(line.substr(pos+1,line.length()));

				if (name=="USB_NET_ON_BOOT") o2x_usb_net_on_boot = value == "y" ? true : false;
				else if (name=="USB_NET_IP") o2x_usb_net_ip = value;
				else if (name=="TELNET_ON_BOOT") o2x_telnet_on_boot = value == "y" ? true : false;
				else if (name=="FTP_ON_BOOT") o2x_ftp_on_boot = value == "y" ? true : false;
				else if (name=="GP2XJOY_ON_BOOT") o2x_gp2xjoy_on_boot = value == "y" ? true : false;
				else if (name=="USB_HOST_ON_BOOT") o2x_usb_host_on_boot = value == "y" ? true : false;
				else if (name=="USB_HID_ON_BOOT") o2x_usb_hid_on_boot = value == "y" ? true : false;
				else if (name=="USB_STORAGE_ON_BOOT") o2x_usb_storage_on_boot = value == "y" ? true : false;
				else if (name=="VOLUME_MODE") volumeMode = savedVolumeMode = constrain( atoi(value.c_str()), 0, 2);
				else if (name=="PHONES_VALUE") volumeScalerPhones = constrain( atoi(value.c_str()), 0, 100);
				else if (name=="NORMAL_VALUE") volumeScalerNormal = constrain( atoi(value.c_str()), 0, 150);
			}
			inf.close();
		}
	}
}
void GMenu2X::writeConfigOpen2x() {
	ledOn();
	string conffile = "/etc/config/open2x.conf";
	ofstream inf(conffile.c_str());
	if (inf.is_open()) {
		inf << "USB_NET_ON_BOOT=" << ( o2x_usb_net_on_boot ? "y" : "n" ) << endl;
		inf << "USB_NET_IP=" << o2x_usb_net_ip << endl;
		inf << "TELNET_ON_BOOT=" << ( o2x_telnet_on_boot ? "y" : "n" ) << endl;
		inf << "FTP_ON_BOOT=" << ( o2x_ftp_on_boot ? "y" : "n" ) << endl;
		inf << "GP2XJOY_ON_BOOT=" << ( o2x_gp2xjoy_on_boot ? "y" : "n" ) << endl;
		inf << "USB_HOST_ON_BOOT=" << ( (o2x_usb_host_on_boot || o2x_usb_hid_on_boot || o2x_usb_storage_on_boot) ? "y" : "n" ) << endl;
		inf << "USB_HID_ON_BOOT=" << ( o2x_usb_hid_on_boot ? "y" : "n" ) << endl;
		inf << "USB_STORAGE_ON_BOOT=" << ( o2x_usb_storage_on_boot ? "y" : "n" ) << endl;
		inf << "VOLUME_MODE=" << volumeMode << endl;
		if (volumeScalerPhones != VOLUME_SCALER_PHONES) inf << "PHONES_VALUE=" << volumeScalerPhones << endl;
		if (volumeScalerNormal != VOLUME_SCALER_NORMAL) inf << "NORMAL_VALUE=" << volumeScalerNormal << endl;
		inf.close();
		sync();
	}
	ledOff();
}

void GMenu2X::writeSkinConfig() {
	ledOn();
	string conffile = path+"skins/"+confStr["skin"]+"/skin.conf";
	ofstream inf(conffile.c_str());
	if (inf.is_open()) {
		ConfStrHash::iterator endS = skinConfStr.end();
		for(ConfStrHash::iterator curr = skinConfStr.begin(); curr != endS; curr++)
			inf << curr->first << "=\"" << curr->second << "\"" << endl;

		ConfIntHash::iterator endI = skinConfInt.end();
		for(ConfIntHash::iterator curr = skinConfInt.begin(); curr != endI; curr++)
			inf << curr->first << "=" << curr->second << endl;

		ConfRGBAHash::iterator endC = skinConfColors.end();
		for(ConfRGBAHash::iterator curr = skinConfColors.begin(); curr != endC; curr++)
			inf << curr->first << "=#" << hex << curr->second.r << hex << curr->second.g << hex << curr->second.b << hex << curr->second.a << endl;

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

void GMenu2X::readTmp() {
	lastSelectorElement = -1;
	if (fileExists("/tmp/gmenu2x.tmp")) {
		ifstream inf("/tmp/gmenu2x.tmp", ios_base::in);
		if (inf.is_open()) {
			string line;
			string section = "";
			while (getline(inf, line, '\n')) {
				string::size_type pos = line.find("=");
				string name = trim(line.substr(0,pos));
				string value = trim(line.substr(pos+1,line.length()));

				if (name=="section")
					menu->setSectionIndex(atoi(value.c_str()));
				else if (name=="link")
					menu->setLinkIndex(atoi(value.c_str()));
				else if (name=="selectorelem")
					lastSelectorElement = atoi(value.c_str());
				else if (name=="selectordir")
					lastSelectorDir = value;
			}
			inf.close();
		}
	}
}

void GMenu2X::writeTmp(int selelem, string selectordir) {
	string conffile = "/tmp/gmenu2x.tmp";
	ofstream inf(conffile.c_str());
	if (inf.is_open()) {
		inf << "section=" << menu->selSectionIndex() << endl;
		inf << "link=" << menu->selLinkIndex() << endl;
		if (selelem>-1)
			inf << "selectorelem=" << selelem << endl;
		if (selectordir!="")
			inf << "selectordir=" << selectordir << endl;
		inf.close();
	}
}

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
	if (gp2x_mem!=0 && !f200) gp2x_memregs[0x106E >> 1] ^= 16;
	//SDL_SYS_JoystickGp2xSys(joy.joystick, BATT_LED_ON);
#endif
}

void GMenu2X::ledOff() {
#ifdef TARGET_GP2X
	if (gp2x_mem!=0 && !f200) gp2x_memregs[0x106E >> 1] ^= 16;
	//SDL_SYS_JoystickGp2xSys(joy.joystick, BATT_LED_OFF);
#endif
}

int GMenu2X::main() {
	uint linksPerPage = linkColumns*linkRows;
	int linkSpacingX = (resX-10 - linkColumns*skinConfInt["linkWidth"])/linkColumns;
	int linkSpacingY = (resY-35 - skinConfInt["topBarHeight"] - linkRows*skinConfInt["linkHeight"])/linkRows;
	uint sectionLinkPadding = (skinConfInt["topBarHeight"] - 32 - font->getLineHeight()) / 3;

	bool quit = false;
	int x,y, offset = menu->sectionLinks()->size()>linksPerPage ? 2 : 6, helpBoxHeight = fwType=="open2x" ? 154 : 139;
	uint i;
	long tickBattery = -60000, tickNow;
	string batteryIcon = "imgs/battery/0.png";
	stringstream ss;
	uint sectionsCoordX = 24;
	SDL_Rect re = {0,0,0,0};

#ifdef DEBUG
	//framerate
	long tickFPS = SDL_GetTicks();
	string fps;
#endif

	IconButton btnContextMenu(this,"skin:imgs/menu.png");
	btnContextMenu.setPosition(resX-38, bottomBarIconY);
	btnContextMenu.setAction(MakeDelegate(this, &GMenu2X::contextMenu));

	while (!quit) {
		tickNow = SDL_GetTicks();

		//Background
		sc["bgmain"]->blit(s,0,0);

		//Sections
		if (menu->firstDispSection()>0)
			sc.skinRes("imgs/l_enabled.png")->blit(s,0,0);
		else
			sc.skinRes("imgs/l_disabled.png")->blit(s,0,0);
		if (menu->firstDispSection()+linkColumns<menu->sections.size())
			sc.skinRes("imgs/r_enabled.png")->blit(s,resX-10,0);
		else
			sc.skinRes("imgs/r_disabled.png")->blit(s,resX-10,0);
		for (i=menu->firstDispSection(); i<menu->sections.size() && i<menu->firstDispSection()+linkColumns; i++) {
			string sectionIcon = "skin:sections/"+menu->sections[i]+".png";
			sectionsCoordX = halfX - (constrain((uint)(linkColumns-menu->sections.size()), 0 , linkColumns) * skinConfInt["linkWidth"]) / 2;
			x = (i-menu->firstDispSection())*skinConfInt["linkWidth"]+sectionsCoordX;
			if (menu->selSectionIndex()==(int)i)
				s->box(x, 0, skinConfInt["linkWidth"], skinConfInt["topBarHeight"], skinConfColors["selectionBg"]);
			x += skinConfInt["linkWidth"]/2;
			if (sc.exists(sectionIcon))
				sc[sectionIcon]->blit(s,x-16,sectionLinkPadding,32,32);
			else
				sc.skinRes("icons/section.png")->blit(s,x,sectionLinkPadding);
			s->write( font, menu->sections[i], x, skinConfInt["topBarHeight"]-sectionLinkPadding, SFontHAlignCenter, SFontVAlignBottom );
		}

		//Links
		s->setClipRect(offset,skinConfInt["topBarHeight"],resX-9,resY-74); //32*2+10
		for (i=menu->firstDispRow()*linkColumns; i<(menu->firstDispRow()*linkColumns)+linksPerPage && i<menu->sectionLinks()->size(); i++) {
			int ir = i-menu->firstDispRow()*linkColumns;
			x = (ir%linkColumns)*(skinConfInt["linkWidth"]+linkSpacingX)+offset;
			y = ir/linkColumns*(skinConfInt["linkHeight"]+linkSpacingY)+skinConfInt["topBarHeight"]+2;
			menu->sectionLinks()->at(i)->setPosition(x,y);

			if (i==(uint)menu->selLinkIndex())
				menu->sectionLinks()->at(i)->paintHover();

			menu->sectionLinks()->at(i)->paint();
		}
		s->clearClipRect();

		drawScrollBar(linkRows,menu->sectionLinks()->size()/linkColumns + ((menu->sectionLinks()->size()%linkColumns==0) ? 0 : 1),menu->firstDispRow(),43,resY-81);

		switch(volumeMode) {
			case VOLUME_MODE_MUTE:   sc.skinRes("imgs/mute.png")->blit(s,279,bottomBarIconY); break;
			case VOLUME_MODE_PHONES: sc.skinRes("imgs/phones.png")->blit(s,279,bottomBarIconY); break;
			default: sc.skinRes("imgs/volume.png")->blit(s,279,bottomBarIconY); break;
		}

		if (menu->selLink()!=NULL) {
			s->write ( font, menu->selLink()->getDescription(), halfX, resY-19, SFontHAlignCenter, SFontVAlignBottom );
			if (menu->selLinkApp()!=NULL) {
				s->write ( font, menu->selLinkApp()->clockStr(confInt["maxClock"]), cpuX, bottomBarTextY, SFontHAlignLeft, SFontVAlignMiddle );
				s->write ( font, menu->selLinkApp()->volumeStr(), volumeX, bottomBarTextY, SFontHAlignLeft, SFontVAlignMiddle );
				//Manual indicator
				if (!menu->selLinkApp()->getManual().empty())
					sc.skinRes("imgs/manual.png")->blit(s,manualX,bottomBarIconY);
			}
		}

		if (f200) {
			btnContextMenu.paint();
		}
		//check battery status every 60 seconds
		if (tickNow-tickBattery >= 60000) {
			tickBattery = tickNow;
			unsigned short battlevel = getBatteryLevel();
			if (battlevel>5) {
				batteryIcon = "imgs/battery/ac.png";
			} else {
				ss.clear();
				ss << battlevel;
				ss >> batteryIcon;
				batteryIcon = "imgs/battery/"+batteryIcon+".png";
			}
		}
		sc.skinRes(batteryIcon)->blit( s, resX-19, bottomBarIconY );

		//On Screen Help
		if (input[ACTION_A]) {
			s->box(10,50,300,143, skinConfColors["messageBoxBg"]);
			s->rectangle( 12,52,296,helpBoxHeight, skinConfColors["messageBoxBorder"] );
			s->write( font, tr["CONTROLS"], 20, 60 );
			s->write( font, tr["B, Stick press: Launch link / Confirm action"], 20, 80 );
			s->write( font, tr["L, R: Change section"], 20, 95 );
			s->write( font, tr["Y: Show manual/readme"], 20, 110 );
			s->write( font, tr["VOLUP, VOLDOWN: Change cpu clock"], 20, 125 );
			s->write( font, tr["A+VOLUP, A+VOLDOWN: Change volume"], 20, 140 );
			s->write( font, tr["SELECT: Show contextual menu"], 20, 155 );
			s->write( font, tr["START: Show options menu"], 20, 170 );
			if (fwType=="open2x") s->write( font, tr["X: Toggle speaker mode"], 20, 185 );
		}

#ifdef DEBUG
		//framerate
		ss.clear();
		ss << 1000/(tickNow-tickFPS+1);
		ss >> fps;
		fps += " FPS";
		tickFPS = tickNow;
		s->write( font, fps, resX-1,1 ,SFontHAlignRight );
#endif

		s->flip();

		//touchscreen
		if (f200) {
			ts.poll();
			btnContextMenu.handleTS();
			re.x = 0; re.y = 0; re.h = skinConfInt["topBarHeight"]; re.w = resX;
			if (ts.pressed() && ts.inRect(re)) {
				re.w = skinConfInt["linkWidth"];
				for (i=menu->firstDispSection(); !ts.handled() && i<menu->sections.size() && i<menu->firstDispSection()+linkColumns; i++) {
					sectionsCoordX = halfX - (constrain((uint)(linkColumns-menu->sections.size()), 0 , linkColumns) * skinConfInt["linkWidth"]) / 2;
					re.x = (i-menu->firstDispSection())*re.w+sectionsCoordX;

					if (ts.inRect(re)) {
						menu->setSectionIndex(i);
						ts.setHandled();
					}
				}
			}

			i=menu->firstDispRow()*linkColumns;
			while ( i<(menu->firstDispRow()*linkColumns)+linksPerPage && i<menu->sectionLinks()->size()) {
				if (menu->sectionLinks()->at(i)->isPressed())
					menu->setLinkIndex(i);
				if (menu->sectionLinks()->at(i)->handleTS())
					i = menu->sectionLinks()->size();
				i++;
			}
		}

//#ifdef TARGET_GP2X
		input.update();
		if ( input[ACTION_B] && menu->selLink()!=NULL ) menu->selLink()->run();
		else if ( input[ACTION_START]  ) options();
		else if ( input[ACTION_SELECT] ) contextMenu();
		// VOLUME SCALE MODIFIER
		else if ( fwType=="open2x" && input[ACTION_X] ) {
			volumeMode = constrain(volumeMode-1, -VOLUME_MODE_MUTE-1, VOLUME_MODE_NORMAL);
			if(volumeMode < VOLUME_MODE_MUTE)
				volumeMode = VOLUME_MODE_NORMAL;
			switch(volumeMode) {
				case VOLUME_MODE_MUTE:   setVolumeScaler(VOLUME_SCALER_MUTE); break;
				case VOLUME_MODE_PHONES: setVolumeScaler(volumeScalerPhones); break;
				case VOLUME_MODE_NORMAL: setVolumeScaler(volumeScalerNormal); break;
			}
			setVolume(confInt["globalVolume"]);
		}
		// LINK NAVIGATION
		else if ( input[ACTION_LEFT ]  ) menu->linkLeft();
		else if ( input[ACTION_RIGHT]  ) menu->linkRight();
		else if ( input[ACTION_UP   ]  ) menu->linkUp();
		else if ( input[ACTION_DOWN ]  ) menu->linkDown();
		// SELLINKAPP SELECTED
		else if (menu->selLinkApp()!=NULL) {
			if ( input[ACTION_Y] ) menu->selLinkApp()->showManual();
			else if ( input.isActive(ACTION_A) ) {
				// VOLUME
				if ( input[ACTION_VOLDOWN] && !input.isActive(ACTION_VOLUP) )
					menu->selLinkApp()->setVolume( constrain(menu->selLinkApp()->volume()-1,0,100) );
				if ( input[ACTION_VOLUP] && !input.isActive(ACTION_VOLDOWN) )
					menu->selLinkApp()->setVolume( constrain(menu->selLinkApp()->volume()+1,0,100) );;
				if ( input.isActive(ACTION_VOLUP) && input.isActive(ACTION_VOLDOWN) ) menu->selLinkApp()->setVolume(-1);
			} else {
				// CLOCK
				if ( input[ACTION_VOLDOWN] && !input.isActive(ACTION_VOLUP) )
					menu->selLinkApp()->setClock( constrain(menu->selLinkApp()->clock()-1,50,confInt["maxClock"]) );
				if ( input[ACTION_VOLUP] && !input.isActive(ACTION_VOLDOWN) )
					menu->selLinkApp()->setClock( constrain(menu->selLinkApp()->clock()+1,50,confInt["maxClock"]) );
				if ( input.isActive(ACTION_VOLUP) && input.isActive(ACTION_VOLDOWN) ) menu->selLinkApp()->setClock(200);
			}
		}
		if ( input.isActive(ACTION_A) ) {
			if (input.isActive(ACTION_L) && input.isActive(ACTION_R))
				saveScreenshot();
		} else {
			// SECTIONS
			if ( input[ACTION_L     ] ) {
				menu->decSectionIndex();
				offset = menu->sectionLinks()->size()>linksPerPage ? 2 : 6;
			} else if ( input[ACTION_R     ] ) {
				menu->incSectionIndex();
				offset = menu->sectionLinks()->size()>linksPerPage ? 2 : 6;
			}
		}
	}

	return -1;
}

void GMenu2X::explorer() {
	FileDialog fd(this,tr["Select an application"],".gpu,.gpe,.sh");
	if (fd.exec()) {
		if (confInt["saveSelection"] && (confInt["section"]!=menu->selSectionIndex() || confInt["link"]!=menu->selLinkIndex()))
			writeConfig();
		if (fwType == "open2x" && savedVolumeMode != volumeMode)
			writeConfigOpen2x();

		//string command = cmdclean(fd.path()+"/"+fd.file) + "; sync & cd "+cmdclean(getExePath())+"; exec ./gmenu2x";
		string command = cmdclean(fd.path()+"/"+fd.file);
		chdir(fd.path().c_str());
		quit();
		setClock(200);
		execlp("/bin/sh","/bin/sh","-c",command.c_str(),NULL);

		//if execution continues then something went wrong and as we already called SDL_Quit we cannot continue
		//try relaunching gmenu2x
		fprintf(stderr, "Error executing selected application, re-launching gmenu2x\n");
		chdir(getExePath().c_str());
		execlp("./gmenu2x", "./gmenu2x", NULL);
	}
}

void GMenu2X::options() {
	int curMenuClock = confInt["menuClock"];
	int curGlobalVolume = confInt["globalVolume"];
	//G
	int prevgamma = confInt["gamma"];
	bool showRootFolder = fileExists("/mnt/root");

	FileLister fl_tr("translations");
	fl_tr.browse();
	fl_tr.files.insert(fl_tr.files.begin(),"English");
	string lang = tr.lang();

	vector<string> encodings;
	encodings.push_back("NTSC");
	encodings.push_back("PAL");

	SettingsDialog sd(this,tr["Settings"]);
	sd.addSetting(new MenuSettingMultiString(this,tr["Language"],tr["Set the language used by GMenu2X"],&lang,&fl_tr.files));
	sd.addSetting(new MenuSettingBool(this,tr["Save last selection"],tr["Save the last selected link and section on exit"],&confInt["saveSelection"]));
	sd.addSetting(new MenuSettingInt(this,tr["Clock for GMenu2X"],tr["Set the cpu working frequency when running GMenu2X"],&confInt["menuClock"],50,325));
	sd.addSetting(new MenuSettingInt(this,tr["Maximum overclock"],tr["Set the maximum overclock for launching links"],&confInt["maxClock"],50,325));
	sd.addSetting(new MenuSettingInt(this,tr["Global Volume"],tr["Set the default volume for the gp2x soundcard"],&confInt["globalVolume"],0,100));
	sd.addSetting(new MenuSettingBool(this,tr["Output logs"],tr["Logs the output of the links. Use the Log Viewer to read them."],&confInt["outputLogs"]));
	//G
	sd.addSetting(new MenuSettingInt(this,tr["Gamma"],tr["Set gp2x gamma value (default: 10)"],&confInt["gamma"],1,100));
	sd.addSetting(new MenuSettingMultiString(this,tr["Tv-Out encoding"],tr["Encoding of the tv-out signal"],&confStr["tvoutEncoding"],&encodings));
	sd.addSetting(new MenuSettingBool(this,tr["Show root"],tr["Show root folder in the file selection dialogs"],&showRootFolder));

	if (sd.exec() && sd.edited()) {
		//G
		if (prevgamma != confInt["gamma"]) setGamma(confInt["gamma"]);
		if (curMenuClock!=confInt["menuClock"]) setClock(confInt["menuClock"]);
		if (curGlobalVolume!=confInt["globalVolume"]) setVolume(confInt["globalVolume"]);
		if (lang == "English") lang = "";
		if (lang != tr.lang()) tr.setLang(lang);
		if (fileExists("/mnt/root") && !showRootFolder)
			unlink("/mnt/root");
		else if (!fileExists("/mnt/root") && showRootFolder)
			symlink("/","/mnt/root");
		writeConfig();
	}
}

void GMenu2X::settingsOpen2x() {
	SettingsDialog sd(this,tr["Open2x Settings"]);
	sd.addSetting(new MenuSettingBool(this,tr["USB net on boot"],tr["Allow USB networking to be started at boot time"],&o2x_usb_net_on_boot));
	sd.addSetting(new MenuSettingString(this,tr["USB net IP"],tr["IP address to be used for USB networking"],&o2x_usb_net_ip));
	sd.addSetting(new MenuSettingBool(this,tr["Telnet on boot"],tr["Allow telnet to be started at boot time"],&o2x_telnet_on_boot));
	sd.addSetting(new MenuSettingBool(this,tr["FTP on boot"],tr["Allow FTP to be started at boot time"],&o2x_ftp_on_boot));
	sd.addSetting(new MenuSettingBool(this,tr["GP2XJOY on boot"],tr["Create a js0 device for GP2X controls"],&o2x_gp2xjoy_on_boot));
	sd.addSetting(new MenuSettingBool(this,tr["USB host on boot"],tr["Allow USB host to be started at boot time"],&o2x_usb_host_on_boot));
	sd.addSetting(new MenuSettingBool(this,tr["USB HID on boot"],tr["Allow USB HID to be started at boot time"],&o2x_usb_hid_on_boot));
	sd.addSetting(new MenuSettingBool(this,tr["USB storage on boot"],tr["Allow USB storage to be started at boot time"],&o2x_usb_storage_on_boot));
	//sd.addSetting(new MenuSettingInt(this,tr["Speaker Mode on boot"],tr["Set Speaker mode. 0 = Mute, 1 = Phones, 2 = Speaker"],&volumeMode,0,2));
	sd.addSetting(new MenuSettingInt(this,tr["Speaker Scaler"],tr["Set the Speaker Mode scaling 0-150\% (default is 100\%)"],&volumeScalerNormal,0,150));
	sd.addSetting(new MenuSettingInt(this,tr["Headphones Scaler"],tr["Set the Headphones Mode scaling 0-100\% (default is 65\%)"],&volumeScalerPhones,0,100));

	if (sd.exec() && sd.edited()) {
		writeConfigOpen2x();
		switch(volumeMode) {
			case VOLUME_MODE_MUTE:   setVolumeScaler(VOLUME_SCALER_MUTE); break;
			case VOLUME_MODE_PHONES: setVolumeScaler(volumeScalerPhones);   break;
			case VOLUME_MODE_NORMAL: setVolumeScaler(volumeScalerNormal); break;
		}
		setVolume(confInt["globalVolume"]);
	}
}

void GMenu2X::skinMenu() {
	FileLister fl_sk("skins",true,false);
	fl_sk.exclude.push_back("..");
	fl_sk.browse();
	string curSkin = confStr["skin"];

	SettingsDialog sd(this,tr["Skin"]);
	sd.addSetting(new MenuSettingMultiString(this,tr["Skin"],tr["Set the skin used by GMenu2X"],&confStr["skin"],&fl_sk.directories));
	sd.addSetting(new MenuSettingRGBA(this,tr["Top Bar Color"],tr["Color of the top bar"],&skinConfColors["topBarBg"]));
	sd.addSetting(new MenuSettingRGBA(this,tr["Bottom Bar Color"],tr["Color of the bottom bar"],&skinConfColors["bottomBarBg"]));
	sd.addSetting(new MenuSettingRGBA(this,tr["Selection Color"],tr["Color of the selection and other interface details"],&skinConfColors["selectionBg"]));
	sd.addSetting(new MenuSettingRGBA(this,tr["Message Box Color"],tr["Background color of the message box"],&skinConfColors["messageBoxBg"]));
	sd.addSetting(new MenuSettingRGBA(this,tr["Message Box Border Color"],tr["Border color of the message box"],&skinConfColors["messageBoxBorder"]));
	sd.addSetting(new MenuSettingRGBA(this,tr["Message Box Selection Color"],tr["Color of the selection of the message box"],&skinConfColors["messageBoxSelection"]));

	if (sd.exec() && sd.edited()) {
		if (curSkin != confStr["skin"]) {
			setSkin(confStr["skin"]);
			writeConfig();
		}
		writeSkinConfig();
		initBG();
	}
}

void GMenu2X::toggleTvOut() {
#ifdef TARGET_GP2X
	if (cx25874!=0)
		gp2x_tvout_off();
	else
		gp2x_tvout_on(confStr["tvoutEncoding"] == "PAL");
#endif
}

void GMenu2X::setSkin(string skin, bool setWallpaper) {
	confStr["skin"] = skin;

	//Clear previous skin settings
	skinConfColors.clear();
	skinConfStr.clear();
	skinConfInt.clear();

	//clear collection and change the skin path
	sc.clear();
	sc.setSkin(skin);

	//reset colors to the default values
	skinConfColors["topBarBg"] = (RGBAColor){255,255,255,130};
	skinConfColors["bottomBarBg"] = (RGBAColor){255,255,255,130};
	skinConfColors["selectionBg"] = (RGBAColor){255,255,255,130};
	skinConfColors["messageBoxBg"] = (RGBAColor){255,255,255,255};
	skinConfColors["messageBoxBorder"] = (RGBAColor){80,80,80,255};
	skinConfColors["messageBoxSelection"] = (RGBAColor){160,160,160,255};

	//load skin settings
	string skinconfname = "skins/"+skin+"/skin.conf";
	if (fileExists(skinconfname)) {
		ifstream skinconf(skinconfname.c_str(), ios_base::in);
		if (skinconf.is_open()) {
			string line;
			while (getline(skinconf, line, '\n')) {
				line = trim(line);
				cout << "skinconf: " << line << endl;
				string::size_type pos = line.find("=");
				string name = trim(line.substr(0,pos));
				string value = trim(line.substr(pos+1,line.length()));

				if (value.length()>0) {
					if (value.length()>1 && value.at(0)=='"' && value.at(value.length()-1)=='"')
						skinConfStr[name] = value.substr(1,value.length()-2);
					else if (value.at(0) == '#')
						skinConfColors[name] = strtorgba( value.substr(1,value.length()) );
					else
						skinConfInt[name] = atoi(value.c_str());
				}
			}
			skinconf.close();

			if (setWallpaper && !skinConfStr["wallpaper"].empty() && fileExists("skins/"+skin+"/wallpapers/"+skinConfStr["wallpaper"]))
				confStr["wallpaper"] = "skins/"+skin+"/wallpapers/"+skinConfStr["wallpaper"];
		}
	}

	evalIntConf( &skinConfInt["topBarHeight"], 40, 32,120 );
	evalIntConf( &skinConfInt["linkHeight"], 40, 32,120 );
	evalIntConf( &skinConfInt["linkWidth"], 60, 32,120 );

	//recalculate some coordinates based on the new element sizes
	linkColumns = (resX-10)/skinConfInt["linkWidth"];
	linkRows = (resY-35-skinConfInt["topBarHeight"])/skinConfInt["linkHeight"];

	if (menu != NULL) menu->loadIcons();

	//Selection png
	useSelectionPng = sc.addSkinRes("imgs/selection.png") != NULL;

	//font
	initFont();
}

void GMenu2X::activateSdUsb() {
	if (usbnet) {
		MessageBox mb(this,tr["Operation not permitted."]+"\n"+tr["You should disable Usb Networking to do this."]);
		mb.exec();
	} else {
		system("scripts/usbon.sh sd");
		MessageBox mb(this,tr["USB Enabled (SD)"],"icons/usb.png");
		mb.buttons[ACTION_B] = tr["Turn off"];
		mb.exec();
		system("scripts/usboff.sh sd");
	}
}

void GMenu2X::activateNandUsb() {
	if (usbnet) {
		MessageBox mb(this,tr["Operation not permitted."]+"\n"+tr["You should disable Usb Networking to do this."]);
		mb.exec();
	} else {
		system("scripts/usbon.sh nand");
		MessageBox mb(this,tr["USB Enabled (Nand)"],"icons/usb.png");
		mb.buttons[ACTION_B] = tr["Turn off"];
		mb.exec();
		system("scripts/usboff.sh nand");
	}
}

void GMenu2X::activateRootUsb() {
	if (usbnet) {
		MessageBox mb(this,tr["Operation not permitted."]+"\n"+tr["You should disable Usb Networking to do this."]);
		mb.exec();
	} else {
		system("scripts/usbon.sh root");
		MessageBox mb(this,tr["USB Enabled (Root)"],"icons/usb.png");
		mb.buttons[ACTION_B] = tr["Turn off"];
		mb.exec();
		system("scripts/usboff.sh root");
	}
}

void GMenu2X::contextMenu() {
	vector<MenuOption> voices;
	{
	MenuOption opt = {tr.translate("Add link in $1",menu->selSection().c_str(),NULL), MakeDelegate(this, &GMenu2X::addLink)};
	voices.push_back(opt);
	}

	if (menu->selLinkApp()!=NULL) {
		{
		MenuOption opt = {tr.translate("Edit $1",menu->selLink()->getTitle().c_str(),NULL), MakeDelegate(this, &GMenu2X::editLink)};
		voices.push_back(opt);
		}{
		MenuOption opt = {tr.translate("Delete $1 link",menu->selLink()->getTitle().c_str(),NULL), MakeDelegate(this, &GMenu2X::deleteLink)};
		voices.push_back(opt);
		}
	}

	{
	MenuOption opt = {tr["Add section"], MakeDelegate(this, &GMenu2X::addSection)};
	voices.push_back(opt);
	}{
	MenuOption opt = {tr["Rename section"], MakeDelegate(this, &GMenu2X::renameSection)};
	voices.push_back(opt);
	}{
	MenuOption opt = {tr["Delete section"], MakeDelegate(this, &GMenu2X::deleteSection)};
	voices.push_back(opt);
	}{
	MenuOption opt = {tr["Scan for applications and games"], MakeDelegate(this, &GMenu2X::scanner)};
	voices.push_back(opt);
	}

	bool close = false;
	uint i, sel=0, fadeAlpha=0;

	int h = font->getHeight();
	int h2 = font->getHalfHeight();
	SDL_Rect box;
	box.h = (h+2)*voices.size()+8;
	box.w = 0;
	for (i=0; i<voices.size(); i++) {
		int w = font->getTextWidth(voices[i].text);
		if (w>box.w) box.w = w;
	}
	box.w += 23;
	box.x = halfX - box.w/2;
	box.y = halfY - box.h/2;

	SDL_Rect selbox = {box.x+4, 0, box.w-8, h+2};
	long tickNow, tickFade = SDL_GetTicks();

	Surface bg(s);
	/*//Darken background
	bg.box(0, 0, resX, resY, 0,0,0,150);
	bg.box(box.x, box.y, box.w, box.h, skinConfColors["messageBoxBg"]);
	bg.rectangle( box.x+2, box.y+2, box.w-4, box.h-4, skinConfColors["messageBoxBorder"] );*/
	while (!close) {
		tickNow = SDL_GetTicks();

		selbox.y = box.y+4+(h+2)*sel;
		bg.blit(s,0,0);

		if (fadeAlpha<200) {
			uint inc = floor((tickNow-tickFade)/3);
			if (inc>0) {
				fadeAlpha += inc;
				if (fadeAlpha>200)
					fadeAlpha = 200;
				tickFade = tickNow;
			}
		}
		s->box(0, 0, resX, resY, 0,0,0,fadeAlpha);
		s->box(box.x, box.y, box.w, box.h, skinConfColors["messageBoxBg"]);
		s->rectangle( box.x+2, box.y+2, box.w-4, box.h-4, skinConfColors["messageBoxBorder"] );


		//draw selection rect
		s->box( selbox.x, selbox.y, selbox.w, selbox.h, skinConfColors["messageBoxSelection"] );
		for (i=0; i<voices.size(); i++)
			s->write( font, voices[i].text, box.x+12, box.y+h2+5+(h+2)*i, SFontHAlignLeft, SFontVAlignMiddle );
		s->flip();

		//touchscreen
		if (f200) {
			ts.poll();
			if (ts.released()) {
				if (!ts.inRect(box))
					close = true;
				else if (ts.x>=selbox.x && ts.x<=selbox.x+selbox.w)
					for (i=0; i<voices.size(); i++) {
						selbox.y = box.y+4+(h+2)*i;
						if (ts.y>=selbox.y && ts.y<=selbox.y+selbox.h) {
							voices[i].action();
							close = true;
							i = voices.size();
						}
					}
			} else if (ts.pressed() && ts.inRect(box)) {
				for (i=0; i<voices.size(); i++) {
					selbox.y = box.y+4+(h+2)*i;
					if (ts.y>=selbox.y && ts.y<=selbox.y+selbox.h) {
						sel = i;
						i = voices.size();
					}
				}
			}
		}

		input.update();
		if ( input[ACTION_SELECT] ) close = true;
		if ( input[ACTION_UP    ] ) sel = max(0, sel-1);
		if ( input[ACTION_DOWN  ] ) sel = min((int)voices.size()-1, sel+1);
		if ( input[ACTION_B] ) { voices[sel].action(); close = true; }
	}
}

void GMenu2X::changeWallpaper() {
	WallpaperDialog wp(this);
	if (wp.exec() && confStr["wallpaper"] != wp.wallpaper) {
		confStr["wallpaper"] = wp.wallpaper;
		initBG();
		writeConfig();
	}
}

void GMenu2X::saveScreenshot() {
	ledOn();
	uint x = 0;
	stringstream ss;
	string fname;
	do {
		x++;
		fname = "";
		ss.clear();
		ss << x;
		ss >> fname;
		fname = "screen"+fname+".bmp";
	} while (fileExists(fname));
	SDL_SaveBMP(s->raw,fname.c_str());
	sync();
	ledOff();
}

void GMenu2X::addLink() {
	FileDialog fd(this,tr["Select an application"]);
	if (fd.exec()) {
		ledOn();
		menu->addLink(fd.path(), fd.file);
		sync();
		ledOff();
	}
}

void GMenu2X::editLink() {
	if (menu->selLinkApp()==NULL) return;

	vector<string> pathV;
	split(pathV,menu->selLinkApp()->file,"/");
	string oldSection = "";
	if (pathV.size()>1)
		oldSection = pathV[pathV.size()-2];
	string newSection = oldSection;

	string linkTitle = menu->selLinkApp()->getTitle();
	string linkDescription = menu->selLinkApp()->getDescription();
	string linkIcon = menu->selLinkApp()->getIcon();
	string linkManual = menu->selLinkApp()->getManual();
	string linkParams = menu->selLinkApp()->getParams();
	string linkSelFilter = menu->selLinkApp()->getSelectorFilter();
	string linkSelDir = menu->selLinkApp()->getSelectorDir();
	bool linkSelBrowser = menu->selLinkApp()->getSelectorBrowser();
	bool linkUseRamTimings = menu->selLinkApp()->getUseRamTimings();
	string linkSelScreens = menu->selLinkApp()->getSelectorScreens();
	string linkSelAliases = menu->selLinkApp()->getAliasFile();
	int linkClock = menu->selLinkApp()->clock();
	int linkVolume = menu->selLinkApp()->volume();
	//G
	int linkGamma = menu->selLinkApp()->gamma();

	string diagTitle = tr.translate("Edit link: $1",linkTitle.c_str(),NULL);
	string diagIcon = menu->selLinkApp()->getIconPath();

	SettingsDialog sd(this,diagTitle,diagIcon);
	sd.addSetting(new MenuSettingString(this,tr["Title"],tr["Link title"],&linkTitle, diagTitle,diagIcon));
	sd.addSetting(new MenuSettingString(this,tr["Description"],tr["Link description"],&linkDescription, diagTitle,diagIcon));
	sd.addSetting(new MenuSettingMultiString(this,tr["Section"],tr["The section this link belongs to"],&newSection,&menu->sections));
	sd.addSetting(new MenuSettingImage(this,tr["Icon"],tr.translate("Select an icon for the link: $1",linkTitle.c_str(),NULL),&linkIcon,".png,.bmp,.jpg,.jpeg"));
	sd.addSetting(new MenuSettingFile(this,tr["Manual"],tr["Select a graphic/textual manual or a readme"],&linkManual,".man.png,.txt"));
	sd.addSetting(new MenuSettingInt(this,tr["Clock (default: 200)"],tr["Cpu clock frequency to set when launching this link"],&linkClock,50,confInt["maxClock"]));
	sd.addSetting(new MenuSettingBool(this,tr["Tweak RAM Timings"],tr["This usually speeds up the application at the cost of stability"],&linkUseRamTimings));
	sd.addSetting(new MenuSettingInt(this,tr["Volume (default: -1)"],tr["Volume to set for this link"],&linkVolume,-1,100));
	sd.addSetting(new MenuSettingString(this,tr["Parameters"],tr["Parameters to pass to the application"],&linkParams, diagTitle,diagIcon));
	sd.addSetting(new MenuSettingDir(this,tr["Selector Directory"],tr["Directory to scan for the selector"],&linkSelDir));
	sd.addSetting(new MenuSettingBool(this,tr["Selector Browser"],tr["Allow the selector to change directory"],&linkSelBrowser));
	sd.addSetting(new MenuSettingString(this,tr["Selector Filter"],tr["Filter for the selector (Separate values with a comma)"],&linkSelFilter, diagTitle,diagIcon));
	sd.addSetting(new MenuSettingDir(this,tr["Selector Screenshots"],tr["Directory of the screenshots for the selector"],&linkSelScreens));
	sd.addSetting(new MenuSettingFile(this,tr["Selector Aliases"],tr["File containing a list of aliases for the selector"],&linkSelAliases));
	//G
	sd.addSetting(new MenuSettingInt(this,tr["Gamma (default: 0)"],tr["Gamma value to set when launching this link"],&linkGamma,0,100));
	sd.addSetting(new MenuSettingBool(this,tr["Wrapper"],tr["Explicitly relaunch GMenu2X after this link's execution ends"],&menu->selLinkApp()->wrapper));
	sd.addSetting(new MenuSettingBool(this,tr["Don't Leave"],tr["Don't quit GMenu2X when launching this link"],&menu->selLinkApp()->dontleave));

	if (sd.exec() && sd.edited()) {
		ledOn();

		menu->selLinkApp()->setTitle(linkTitle);
		menu->selLinkApp()->setDescription(linkDescription);
		menu->selLinkApp()->setIcon(linkIcon);
		menu->selLinkApp()->setManual(linkManual);
		menu->selLinkApp()->setParams(linkParams);
		menu->selLinkApp()->setSelectorFilter(linkSelFilter);
		menu->selLinkApp()->setSelectorDir(linkSelDir);
		menu->selLinkApp()->setSelectorBrowser(linkSelBrowser);
		menu->selLinkApp()->setUseRamTimings(linkUseRamTimings);
		menu->selLinkApp()->setSelectorScreens(linkSelScreens);
		menu->selLinkApp()->setAliasFile(linkSelAliases);
		menu->selLinkApp()->setClock(linkClock);
		menu->selLinkApp()->setVolume(linkVolume);
		//G
		menu->selLinkApp()->setGamma(linkGamma);

#ifdef DEBUG
		cout << "New Section: " << newSection << endl;
#endif
		//if section changed move file and update link->file
		if (oldSection!=newSection) {
			vector<string>::iterator newSectionIndex = find(menu->sections.begin(),menu->sections.end(),newSection);
			if (newSectionIndex==menu->sections.end()) return;
			string newFileName = "sections/"+newSection+"/"+linkTitle;
			uint x=2;
			while (fileExists(newFileName)) {
				string id = "";
				stringstream ss; ss << x; ss >> id;
				newFileName = "sections/"+newSection+"/"+linkTitle+id;
				x++;
			}
			rename(menu->selLinkApp()->file.c_str(),newFileName.c_str());
			menu->selLinkApp()->file = newFileName;
#ifdef DEBUG
			cout << "New section index: " << newSectionIndex - menu->sections.begin() << endl;
#endif
			menu->linkChangeSection(menu->selLinkIndex(), menu->selSectionIndex(), newSectionIndex - menu->sections.begin());
		}
		menu->selLinkApp()->save();
		sync();

		ledOff();
	}
}

void GMenu2X::deleteLink() {
	if (menu->selLinkApp()!=NULL) {
		MessageBox mb(this, tr.translate("Deleting $1",menu->selLink()->getTitle().c_str(),NULL)+"\n"+tr["Are you sure?"], menu->selLink()->getIconPath());
		mb.buttons[ACTION_B] = tr["Yes"];
		mb.buttons[ACTION_X] = tr["No"];
		if (mb.exec() == ACTION_B) {
			ledOn();
			menu->deleteSelectedLink();
			sync();
			ledOff();
		}
	}
}

void GMenu2X::addSection() {
	InputDialog id(this,tr["Insert a name for the new section"]);
	if (id.exec()) {
		//only if a section with the same name does not exist
		if (find(menu->sections.begin(),menu->sections.end(),id.input)==menu->sections.end()) {
			//section directory doesn't exists
			ledOn();
			if (menu->addSection(id.input)) {
				menu->setSectionIndex( menu->sections.size()-1 ); //switch to the new section
				sync();
			}
			ledOff();
		}
	}
}

void GMenu2X::renameSection() {
	InputDialog id(this,tr["Insert a new name for this section"],menu->selSection());
	if (id.exec()) {
		//only if a section with the same name does not exist & !samename
		if (menu->selSection()!=id.input && find(menu->sections.begin(),menu->sections.end(),id.input)==menu->sections.end()) {
			//section directory doesn't exists
			string newsectiondir = "sections/"+id.input;
			string sectiondir = "sections/"+menu->selSection();
			ledOn();
			if (rename(sectiondir.c_str(), "tmpsection")==0 && rename("tmpsection", newsectiondir.c_str())==0) {
				string oldpng = sectiondir+".png", newpng = newsectiondir+".png";
				string oldicon = sc.getSkinFilePath(oldpng), newicon = sc.getSkinFilePath(newpng);
				if (!oldicon.empty() && newicon.empty()) {
					newicon = oldicon;
          				newicon.replace(newicon.find(oldpng), oldpng.length(), newpng);

					if (!fileExists(newicon)) {
						rename(oldicon.c_str(), "tmpsectionicon");
						rename("tmpsectionicon", newicon.c_str());
						sc.move("skin:"+oldpng, "skin:"+newpng);
					}
				}
				menu->sections[menu->selSectionIndex()] = id.input;
				sync();
			}
			ledOff();
		}
	}
}

void GMenu2X::deleteSection() {
	MessageBox mb(this,tr["You will lose all the links in this section."]+"\n"+tr["Are you sure?"]);
	mb.buttons[ACTION_B] = tr["Yes"];
	mb.buttons[ACTION_X] = tr["No"];
	if (mb.exec() == ACTION_B) {
		ledOn();
		if (rmtree(path+"sections/"+menu->selSection())) {
			menu->deleteSelectedSection();
			sync();
		}
		ledOff();
	}
}

void GMenu2X::scanner() {
	Surface scanbg(bg);
	drawButton(&scanbg, "x", tr["Exit"],
	drawButton(&scanbg, "b", "", 5)-10);
	scanbg.write(font,tr["Link Scanner"],halfX,7,SFontHAlignCenter,SFontVAlignMiddle);

	uint lineY = 42;

	if (confInt["menuClock"]<200) {
		setClock(200);
		scanbg.write(font,tr["Raising cpu clock to 200Mhz"],5,lineY);
		scanbg.blit(s,0,0);
		s->flip();
		lineY += 26;
	}

	scanbg.write(font,tr["Scanning SD filesystem..."],5,lineY);
	scanbg.blit(s,0,0);
	s->flip();
	lineY += 26;

	vector<string> files;
	scanPath("/mnt/sd",&files);

	//Onyl gph firmware has nand
	if (fwType=="gph" && !f200) {
		scanbg.write(font,tr["Scanning NAND filesystem..."],5,lineY);
		scanbg.blit(s,0,0);
		s->flip();
		lineY += 26;
		scanPath("/mnt/nand",&files);
	}

	stringstream ss;
	ss << files.size();
	string str = "";
	ss >> str;
	scanbg.write(font,tr.translate("$1 files found.",str.c_str(),NULL),5,lineY);
	lineY += 26;
	scanbg.write(font,tr["Creating links..."],5,lineY);
	scanbg.blit(s,0,0);
	s->flip();
	lineY += 26;

	string path, file;
	string::size_type pos;
	uint linkCount = 0;

	ledOn();
	for (uint i = 0; i<files.size(); i++) {
		pos = files[i].rfind("/");
		if (pos!=string::npos && pos>0) {
			path = files[i].substr(0, pos+1);
			file = files[i].substr(pos+1, files[i].length());
			if (menu->addLink(path,file,"found "+file.substr(file.length()-3,3)))
				linkCount++;
		}
	}

	ss.clear();
	ss << linkCount;
	ss >> str;
	scanbg.write(font,tr.translate("$1 links created.",str.c_str(),NULL),5,lineY);
	scanbg.blit(s,0,0);
	s->flip();
	lineY += 26;

	if (confInt["menuClock"]<200) {
		setClock(confInt["menuClock"]);
		scanbg.write(font,tr["Decreasing cpu clock"],5,lineY);
		scanbg.blit(s,0,0);
		s->flip();
		lineY += 26;
	}

	bool close = false;
	while (!close) {
		input.update();
		if (input[ACTION_START] || input[ACTION_B] || input[ACTION_X]) close = true;
	}

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
	if (batteryHandle<=0) return 0;

	if (f200) {
		MMSP2ADC val;
		int rv = read(batteryHandle, &val, sizeof(MMSP2ADC));

		if (val.batt==0) return 5;
		if (val.batt==1) return 3;
		if (val.batt==2) return 1;
		if (val.batt==3) return 0;
	} else {
		int battval = 0;
		unsigned short cbv, min=900, max=0;
		int v;

		for (int i = 0; i < BATTERY_READS; i ++) {
			if ( read(batteryHandle, &cbv, 2) == 2) {
				battval += cbv;
				if (cbv>max) max = cbv;
				if (cbv<min) min = cbv;
			}
		}

		battval -= min+max;
		battval /= BATTERY_READS-2;

		if (battval>=850) return 6;
		if (battval>780) return 5;
		if (battval>740) return 4;
		if (battval>700) return 3;
		if (battval>690) return 2;
		if (battval>680) return 1;
	}
	return 0;
#else
	return 6; //AC Power
#endif
}

void GMenu2X::setInputSpeed() {
	input.setInterval(150);
	input.setInterval(30,  ACTION_VOLDOWN);
	input.setInterval(30,  ACTION_VOLUP  );
	input.setInterval(30,  ACTION_A      );
	input.setInterval(500, ACTION_START  );
	input.setInterval(500, ACTION_SELECT );
	input.setInterval(300, ACTION_X      );
	input.setInterval(300,  ACTION_Y      );
	input.setInterval(1000,ACTION_B      );
	//joy.setInterval(1000,ACTION_CLICK  );
	input.setInterval(300, ACTION_L      );
	input.setInterval(300, ACTION_R      );
	SDL_EnableKeyRepeat(1,150);
}

void GMenu2X::applyRamTimings() {
#ifdef TARGET_GP2X
	// 6 4 1 1 1 2 2
	if (gp2x_mem!=0) {
		int tRC = 5, tRAS = 3, tWR = 0, tMRD = 0, tRFC = 0, tRP = 1, tRCD = 1;
		gp2x_memregs[0x3802>>1] = ((tMRD & 0xF) << 12) | ((tRFC & 0xF) << 8) | ((tRP & 0xF) << 4) | (tRCD & 0xF);
		gp2x_memregs[0x3804>>1] = ((tRC & 0xF) << 8) | ((tRAS & 0xF) << 4) | (tWR & 0xF);
	}
#endif
}

void GMenu2X::applyDefaultTimings() {
#ifdef TARGET_GP2X
	// 8 16 3 8 8 8 8
	if (gp2x_mem!=0) {
		int tRC = 7, tRAS = 15, tWR = 2, tMRD = 7, tRFC = 7, tRP = 7, tRCD = 7;
		gp2x_memregs[0x3802>>1] = ((tMRD & 0xF) << 12) | ((tRFC & 0xF) << 8) | ((tRP & 0xF) << 4) | (tRCD & 0xF);
		gp2x_memregs[0x3804>>1] = ((tRC & 0xF) << 8) | ((tRAS & 0xF) << 4) | (tWR & 0xF);
	}
#endif
}

void GMenu2X::setClock(unsigned mhz) {
	mhz = constrain(mhz,50,confInt["maxClock"]);
#ifdef TARGET_GP2X
	if (gp2x_mem!=0) {
		unsigned v;
		unsigned mdiv,pdiv=3,scale=0;
		mhz*=1000000;
		mdiv=(mhz*pdiv)/GP2X_CLK_FREQ;
		mdiv=((mdiv-8)<<8) & 0xff00;
		pdiv=((pdiv-2)<<2) & 0xfc;
		scale&=3;
		v=mdiv | pdiv | scale;
		MEM_REG[0x910>>1]=v;
	}
#endif
}

void GMenu2X::setGamma(int gamma) {
#ifdef TARGET_GP2X
	float fgamma = (float)constrain(gamma,1,100)/10;
	fgamma = 1 / fgamma;
	MEM_REG[0x2880>>1]&=~(1<<12);
	MEM_REG[0x295C>>1]=0;

	for (int i=0; i<256; i++) {
		unsigned char g = (unsigned char)(255.0*pow(i/255.0,fgamma));
		unsigned short s = (g<<8) | g;
		MEM_REG[0x295E>>1]= s;
		MEM_REG[0x295E>>1]= g;
	}
#endif
}

int GMenu2X::getVolume() {
	int vol = -1;
	unsigned long soundDev = open("/dev/mixer", O_RDONLY);
	if (soundDev) {
		ioctl(soundDev, SOUND_MIXER_READ_PCM, &vol);
		close(soundDev);
		if (vol != -1) {
			//just return one channel , not both channels, they're hopefully the same anyways
			return vol & 0xFF;
		}
	}
	return vol;
}

void GMenu2X::setVolume(int vol) {
	vol = constrain(vol,0,100);
	unsigned long soundDev = open("/dev/mixer", O_RDWR);
	if (soundDev) {
		vol = (vol << 8) | vol;
		ioctl(soundDev, SOUND_MIXER_WRITE_PCM, &vol);
		close(soundDev);
	}
}

void GMenu2X::setVolumeScaler(int scale) {
	scale = constrain(scale,0,MAX_VOLUME_SCALE_FACTOR);
	unsigned long soundDev = open("/dev/mixer", O_WRONLY);
	if (soundDev) {
		ioctl(soundDev, SOUND_MIXER_PRIVATE2, &scale);
		close(soundDev);
	}
}

int GMenu2X::getVolumeScaler() {
	int currentscalefactor = -1;
	unsigned long soundDev = open("/dev/mixer", O_RDONLY);
	if (soundDev) {
		ioctl(soundDev, SOUND_MIXER_PRIVATE1, &currentscalefactor);
		close(soundDev);
	}
	return currentscalefactor;
}

string GMenu2X::getExePath() {
	if (path.empty()) {
		char buf[255];
		int l = readlink("/proc/self/exe",buf,255);

		path = buf;
		path = path.substr(0,l);
		l = path.rfind("/");
		path = path.substr(0,l+1);
	}
	return path;
}

string GMenu2X::getDiskFree() {
	stringstream ss;
	string df = "";
	struct statvfs b;

	int ret = statvfs("/mnt/sd", &b);
	if (ret==0) {
		unsigned long free = b.f_bfree*b.f_frsize/1048576;
		unsigned long total = b.f_blocks*b.f_frsize/1048576;
		ss << free << "/" << total << "MB";
		ss >> df;
	} else cout << "\033[0;34mGMENU2X:\033[0;31m statvfs failed with error '" << strerror(errno) << "'\033[0m" << endl;
	return df;
}

int GMenu2X::drawButton(IconButton *btn, int x, int y) {
	if (y<0) y = resY+y;
	btn->setPosition(x, y-7);
	btn->paint();
	return x+btn->getRect().w+6;
}

int GMenu2X::drawButton(Surface *s, string btn, string text, int x, int y) {
	if (y<0) y = resY+y;
	SDL_Rect re = {x, y-7, 0, 16};
	if (sc.skinRes("imgs/buttons/"+btn+".png") != NULL) {
		sc["imgs/buttons/"+btn+".png"]->blit(s, x, y-7);
		re.w = sc["imgs/buttons/"+btn+".png"]->raw->w+3;
		s->write(font, text, x+re.w, y, SFontHAlignLeft, SFontVAlignMiddle);
		re.w += font->getTextWidth(text);
	}
	return x+re.w+6;
}

int GMenu2X::drawButtonRight(Surface *s, string btn, string text, int x, int y) {
	if (y<0) y = resY+y;
	if (sc.skinRes("imgs/buttons/"+btn+".png") != NULL) {
		x -= 16;
		sc["imgs/buttons/"+btn+".png"]->blit(s, x, y-7);
		x -= 3;
		s->write(font, text, x, y, SFontHAlignRight, SFontVAlignMiddle);
		return x-6-font->getTextWidth(text);
	}
	return x-6;
}

void GMenu2X::drawScrollBar(uint pagesize, uint totalsize, uint pagepos, uint top, uint height) {
	if (totalsize<=pagesize) return;

	s->rectangle(resX-8, top, 7, height, skinConfColors["selectionBg"]);

	//internal bar total height = height-2
	//bar size
	uint bs = (height-2) * pagesize / totalsize;
	//bar y position
	uint by = (height-2) * pagepos / totalsize;
	by = top+2+by;
	if (by+bs>top+height-2) by = top+height-2-bs;


	s->box(resX-6, by, 3, bs, skinConfColors["selectionBg"]);
}

void GMenu2X::drawTitleIcon(string icon, bool skinRes, Surface *s) {
	if (s==NULL) s = this->s;

	Surface *i = NULL;
	if (!icon.empty()) {
		if (skinRes)
			i = sc.skinRes(icon);
		else
			i = sc[icon];
	}

	if (i==NULL)
		i = sc.skinRes("icons/generic.png");

	i->blit(s,4,(skinConfInt["topBarHeight"]-32)/2);
}

void GMenu2X::writeTitle(string title, Surface *s) {
	if (s==NULL) s = this->s;
	s->write(font,title,40, skinConfInt["topBarHeight"]/4, SFontHAlignLeft, SFontVAlignMiddle);
}

void GMenu2X::writeSubTitle(string subtitle, Surface *s) {
	if (s==NULL) s = this->s;
	s->write(font,subtitle,40, skinConfInt["topBarHeight"]/4*3, SFontHAlignLeft, SFontVAlignMiddle);
}

void GMenu2X::drawTopBar(Surface *s) {
	if (s==NULL) s = this->s;

	Surface *bar = sc.skinRes("imgs/topbar.png");
	if (bar != NULL)
		bar->blit(s, 0, 0);
	else
		s->box(0, 0, resX, skinConfInt["topBarHeight"], skinConfColors["topBarBg"]);
}

void GMenu2X::drawBottomBar(Surface *s) {
	if (s==NULL) s = this->s;

	Surface *bar = sc.skinRes("imgs/bottombar.png");
	if (bar != NULL)
		bar->blit(s, 0, resY-bar->raw->h);
	else
		s->box(0, resY-20, resX, 20, skinConfColors["bottomBarBg"]);
}
