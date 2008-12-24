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

#include "messagebox.h"

using namespace std;

MessageBox::MessageBox(GMenu2X *gmenu2x, string text, string icon) {
	this->gmenu2x = gmenu2x;
	this->text = text;
	this->icon = icon;

	buttons.resize(19);
	buttonLabels.resize(19);
	buttonPositions.resize(19);
	for (uint x=0; x<buttons.size(); x++) {
		buttons[x] = "";
		buttonLabels[x] = "";
		buttonPositions[x].h = gmenu2x->font->getHeight();
	}

	//Default enabled button
	buttons[ACTION_B] = "OK";

	//Default labels
	buttonLabels[ACTION_UP] = "up";
	buttonLabels[ACTION_DOWN] = "down";
	buttonLabels[ACTION_LEFT] = "left";
	buttonLabels[ACTION_RIGHT] = "right";
	buttonLabels[ACTION_A] = "a";
	buttonLabels[ACTION_B] = "b";
	buttonLabels[ACTION_X] = "x";
	buttonLabels[ACTION_Y] = "y";
	buttonLabels[ACTION_L] = "l";
	buttonLabels[ACTION_R] = "r";
	buttonLabels[ACTION_START] = "start";
	buttonLabels[ACTION_SELECT] = "select";
	buttonLabels[ACTION_VOLUP] = "vol+";
	buttonLabels[ACTION_VOLDOWN] = "vol-";
}

int MessageBox::exec() {
	int result = -1;

	Surface bg(gmenu2x->s);
	//Darken background
	bg.box(0, 0, gmenu2x->resX, gmenu2x->resY, 0,0,0,200);
	
	SDL_Rect box;
	box.h = gmenu2x->font->getHeight()*3 +4;
	box.w = gmenu2x->font->getTextWidth(text) + 24 + (gmenu2x->sc[icon] != NULL ? 37 : 0);
	box.x = gmenu2x->halfX - box.w/2 -2;
	box.y = gmenu2x->halfY - box.h/2 -2;

	//outer box
	bg.box(box, gmenu2x->skinConfColors["messageBoxBg"]);
	//draw inner rectangle
	bg.rectangle(box.x+2, box.y+2, box.w-4, box.h-gmenu2x->font->getHeight(), gmenu2x->skinConfColors["messageBoxBorder"]);
	//icon+text
	if (gmenu2x->sc[icon] != NULL)
		gmenu2x->sc[icon]->blitCenter( &bg, box.x+25, box.y+gmenu2x->font->getHeight()+3 );
	bg.write( gmenu2x->font, text, box.x+(gmenu2x->sc[icon] != NULL ? 47 : 10), box.y+gmenu2x->font->getHeight()+3, SFontHAlignLeft, SFontVAlignMiddle );

	int btnX = gmenu2x->halfX+box.w/2-6;
	for (uint i=0; i<buttons.size(); i++) {
		if (buttons[i] != "") {
			buttonPositions[i].y = box.y+box.h-4;
			buttonPositions[i].w = btnX;
			
			btnX = gmenu2x->drawButtonRight(&bg, buttonLabels[i], buttons[i], btnX, buttonPositions[i].y);
			
			buttonPositions[i].x = btnX;
			buttonPositions[i].w = buttonPositions[i].x-btnX-6;
		}
	}

	bg.blit(gmenu2x->s,0,0);
	gmenu2x->s->flip();

	while (result<0) {
		//touchscreen
		if (gmenu2x->f200) {
			if (gmenu2x->ts.poll()) {
				for (uint i=0; i<buttons.size(); i++)
					if (buttons[i]!="" && gmenu2x->ts.inRect(buttonPositions[i])) {
						result = i;
						i = buttons.size();
					}
			}
		}

		gmenu2x->input.update();
		for (uint i=0; i<buttons.size(); i++)
			if (buttons[i]!="" && gmenu2x->input[i]) result = i;
		
		usleep(LOOP_DELAY);
	}

	return result;
}
