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
		buttonPositions[x].x = 0;
		buttonPositions[x].y = 140;
		buttonPositions[x].w = 0;
		buttonPositions[x].h = 16;
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
	bg.box(0, 0, 320, 240, 0,0,0,150);

	int textW = gmenu2x->font->getTextWidth(text);
	int boxW = textW + 20;
	if (gmenu2x->sc[icon] != NULL)
		boxW += 37;
	int halfBoxW = boxW/2;
	int x = 160-halfBoxW;

	//outer box
	bg.box(x-2, 90, boxW+5, 61, gmenu2x->messageBoxColor);
	//draw inner rectangle
	bg.rectangle(x, 92, boxW, 36, gmenu2x->messageBoxBorderColor);
	//icon+text
	x += 10;
	if (gmenu2x->sc[icon] != NULL) {
		gmenu2x->sc[icon]->blit( &bg, x-3, 94 );
		x += 37;
	}
	bg.write( gmenu2x->font, text, x, 110, SFontHAlignLeft, SFontVAlignMiddle );

	int btnX = 158+halfBoxW;
	for (uint i=0; i<buttons.size(); i++) {
		if (buttons[i] != "") {
			buttonPositions[i].w = btnX;
			btnX = gmenu2x->drawButtonRight(&bg, buttonLabels[i], buttons[i], btnX, 140);
			buttonPositions[i].x = btnX;
			buttonPositions[i].w = buttonPositions[i].w-btnX-6;
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
	}

	return result;
}
