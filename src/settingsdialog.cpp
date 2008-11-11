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

#include <SDL.h>
#include <SDL_gfxPrimitives.h>

#include "settingsdialog.h"

using namespace std;

SettingsDialog::SettingsDialog(GMenu2X *gmenu2x, string text, string icon) {
	this->gmenu2x = gmenu2x;
	this->text = text;

	if (icon!="" && gmenu2x->sc[icon] != NULL)
		this->icon = icon;
	else
		this->icon = "icons/generic.png";
}

SettingsDialog::~SettingsDialog() {
	for (uint i=0; i<voices.size(); i++)
		free(voices[i]);
}

bool SettingsDialog::exec() {
	//Surface bg (gmenu2x->confStr["wallpaper"],false);
	Surface bg(gmenu2x->bg);

	bool close = false, ts_pressed = false;
	uint i, sel = 0, iY, firstElement = 0, action;
	voices[sel]->adjustInput();

	SDL_Rect clipRect = {0, gmenu2x->skinConfInt["topBarHeight"]+1, gmenu2x->resX-9, gmenu2x->resY-gmenu2x->skinConfInt["topBarHeight"]-25};
	SDL_Rect touchRect = {2, gmenu2x->skinConfInt["topBarHeight"]+4, gmenu2x->resX-12, clipRect.h};
	uint rowHeight = gmenu2x->font->getHeight()+1; // gp2x=15+1 / pandora=19+1
	uint numRows = (gmenu2x->resY-gmenu2x->skinConfInt["topBarHeight"]-20)/rowHeight;

	while (!close) {
		action = SD_NO_ACTION;
		if (gmenu2x->f200) gmenu2x->ts.poll();

		bg.blit(gmenu2x->s,0,0);

		gmenu2x->drawTopBar(gmenu2x->s);
		//link icon
		gmenu2x->drawTitleIcon(icon);
		gmenu2x->writeTitle(text);
		gmenu2x->drawBottomBar(gmenu2x->s);

		if (sel>firstElement+numRows-1) firstElement=sel-numRows+1;
		if (sel<firstElement) firstElement=sel;

		//selection
		iY = sel-firstElement;
		iY = gmenu2x->skinConfInt["topBarHeight"]+2+(iY*rowHeight);
		gmenu2x->s->setClipRect(clipRect);
		if (sel<voices.size())
			gmenu2x->s->box(1, iY, 148, rowHeight-2, gmenu2x->skinConfColors["selectionBg"]);
		gmenu2x->s->clearClipRect();

		//selected option
		voices[sel]->drawSelected(iY);

		gmenu2x->s->setClipRect(clipRect);
		if (ts_pressed && !gmenu2x->ts.pressed()) ts_pressed = false;
		if (gmenu2x->f200 && gmenu2x->ts.pressed() && !gmenu2x->ts.inRect(touchRect)) ts_pressed = false;
		for (i=firstElement; i<voices.size() && i<firstElement+numRows; i++) {
			iY = i-firstElement;
			voices[i]->draw(iY*rowHeight+gmenu2x->skinConfInt["topBarHeight"]+2);
			if (gmenu2x->f200 && gmenu2x->ts.pressed() && gmenu2x->ts.inRect(touchRect.x, touchRect.y+(iY*rowHeight), touchRect.w, rowHeight)) {
				ts_pressed = true;
				sel = i;
			}
		}
		gmenu2x->s->clearClipRect();

		gmenu2x->drawScrollBar(numRows,voices.size(),firstElement,clipRect.y+1,clipRect.h);

		//description
		gmenu2x->writeSubTitle(voices[sel]->description);

		gmenu2x->s->flip();
		voices[sel]->handleTS();

		gmenu2x->input.update();
		if ( gmenu2x->input[ACTION_START] ) action = SD_ACTION_CLOSE;
		if ( gmenu2x->input[ACTION_UP   ] ) action = SD_ACTION_UP;
		if ( gmenu2x->input[ACTION_DOWN ] ) action = SD_ACTION_DOWN;
		voices[sel]->manageInput();

		switch (action) {
			case SD_ACTION_CLOSE: close = true; break;
			case SD_ACTION_UP: {
				if (sel==0)
					sel = voices.size()-1;
				else
					sel -= 1;
				gmenu2x->setInputSpeed();
				voices[sel]->adjustInput();
			} break;
			case SD_ACTION_DOWN: {
				sel += 1;
				if (sel>=voices.size()) sel = 0;
				gmenu2x->setInputSpeed();
				voices[sel]->adjustInput();
			} break;
		}
	}

	gmenu2x->setInputSpeed();
	return true;
}

void SettingsDialog::addSetting(MenuSetting* set) {
	voices.push_back(set);
}

bool SettingsDialog::edited() {
	for (uint i=0; i<voices.size(); i++)
		if (voices[i]->edited()) return true;
	return false;
}
