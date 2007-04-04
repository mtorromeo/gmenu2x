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

#ifdef TARGET_GP2X
#include "gp2x.h"
#endif
#include <sstream>
#include "textmanualdialog.h"

using namespace std;

TextManualDialog::TextManualDialog(GMenu2X *gmenu2x, string title, string icon, vector<string> *text)
	: TextDialog(gmenu2x,title,"",icon,text) {
	this->gmenu2x = gmenu2x;

	//split the text in multiple pages
	for (uint i=0; i<text->size(); i++) {
		string line = trim(text->at(i));
		if (line[0]=='[' && line[line.length()-1]==']') {
			ManualPage mp;
			mp.title = line.substr(1,line.length()-2);
			pages.push_back(mp);
		} else {
			if (pages.size()==0) {
				ManualPage mp;
				mp.title = gmenu2x->tr["Untitled"];
				pages.push_back(mp);
			}
			pages[pages.size()-1].text.push_back(text->at(i));
		}
	}
	if (pages.size()==0) {
		ManualPage mp;
		mp.title = gmenu2x->tr["Untitled"];
		pages.push_back(mp);
	}

	//delete first and last blank lines from each page
	for (uint page=0; page<pages.size(); page++) {
		if (pages[page].text.size() > 0) {
			//first lines
			while (trim(pages[page].text[0])=="")
				pages[page].text.erase(pages[page].text.begin());
			//last lines
			while (trim(pages[page].text[pages[page].text.size()-1])=="")
				pages[page].text.erase(pages[page].text.end());
		}
	}
}

void TextManualDialog::exec() {
	bool close = false;
	uint page=0;

	Surface bg(gmenu2x->sc["imgs/bg.png"]);

	//link icon
	if (!fileExists(icon))
		gmenu2x->drawTitleIcon("icons/ebook.png",true,&bg);
	else
		gmenu2x->drawTitleIcon(icon,false,&bg);
	gmenu2x->writeTitle(title+(description.empty() ? "" : ": "+description),&bg);

	gmenu2x->drawButton(&bg, "x", gmenu2x->tr["Exit"],
	gmenu2x->drawButton(&bg, "right", gmenu2x->tr["Change page"],
	gmenu2x->drawButton(&bg, "left", "",
	gmenu2x->drawButton(&bg, "down", gmenu2x->tr["Scroll"],
	gmenu2x->drawButton(&bg, "up", "", 5)-10))-10));

	uint firstRow = 0, rowsPerPage = 180/gmenu2x->font->getHeight();
	stringstream ss;
	ss << pages.size();
	string spagecount;
	ss >> spagecount;
	string pageStatus;
	while (!close) {
		bg.blit(gmenu2x->s,0,0);
		gmenu2x->writeSubTitle(pages[page].title);
		drawText(&pages[page].text, firstRow, rowsPerPage);

		ss.clear();
		ss << page+1;
		ss >> pageStatus;
		pageStatus = gmenu2x->tr["Page"]+": "+pageStatus+"/"+spagecount;
		gmenu2x->s->write(gmenu2x->font, pageStatus, 310, 230, SFontHAlignRight, SFontVAlignMiddle);

		gmenu2x->s->flip();

#ifdef TARGET_GP2X
		gmenu2x->joy.update();
		if ( gmenu2x->joy[GP2X_BUTTON_UP   ] && firstRow>0 ) firstRow--;
		if ( gmenu2x->joy[GP2X_BUTTON_DOWN ] && firstRow+rowsPerPage<pages[page].text.size() ) firstRow++;
		if ( gmenu2x->joy[GP2X_BUTTON_LEFT ] && page>0 ) { page--; firstRow=0; }
		if ( gmenu2x->joy[GP2X_BUTTON_RIGHT] && page<pages.size()-1 ) { page++; firstRow=0; }
		if ( gmenu2x->joy[GP2X_BUTTON_L   ] ) {
			if (firstRow>=rowsPerPage-1)
				firstRow-= rowsPerPage-1;
			else
				firstRow = 0;
		}
		if ( gmenu2x->joy[GP2X_BUTTON_R   ] ) {
			if (firstRow+rowsPerPage*2-1<pages[page].text.size())
				firstRow+= rowsPerPage-1;
			else
				firstRow = max(0,pages[page].text.size()-rowsPerPage);
		}
		if ( gmenu2x->joy[GP2X_BUTTON_START] || gmenu2x->joy[GP2X_BUTTON_X] ) close = true;
#else
		while (SDL_PollEvent(&gmenu2x->event)) {
			if ( gmenu2x->event.type == SDL_QUIT ) close = true;
			if ( gmenu2x->event.type==SDL_KEYDOWN ) {
				if ( gmenu2x->event.key.keysym.sym==SDLK_ESCAPE ) close = true;
				if ( gmenu2x->event.key.keysym.sym==SDLK_UP && firstRow>0 ) firstRow--;
				if ( gmenu2x->event.key.keysym.sym==SDLK_DOWN && firstRow+rowsPerPage<pages[page].text.size() ) firstRow++;
				if ( gmenu2x->event.key.keysym.sym==SDLK_LEFT && page>0 ) { page--; firstRow=0; }
				if ( gmenu2x->event.key.keysym.sym==SDLK_RIGHT && page<pages.size()-1 ) { page++; firstRow=0; }
			}
		}
#endif
	}
}
