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

#include "gp2x.h"
#include "messagebox.h"

using namespace std;

MessageBox::MessageBox(GMenu2X *gmenu2x, string text, string icon) {
	this->gmenu2x = gmenu2x;
	this->text = text;
	this->icon = icon;

	buttons.resize(19);
	buttonLabels.resize(19);
	for (uint x=0; x<buttons.size(); x++) {
		buttons[x] = "";
		buttonLabels[x] = "";
	}

	//Default enabled button
	buttons[GP2X_BUTTON_B] = "OK";

	//Default labels
	buttonLabels[GP2X_BUTTON_UP] = "up";
	buttonLabels[GP2X_BUTTON_DOWN] = "down";
	buttonLabels[GP2X_BUTTON_LEFT] = "left";
	buttonLabels[GP2X_BUTTON_RIGHT] = "right";
	buttonLabels[GP2X_BUTTON_A] = "a";
	buttonLabels[GP2X_BUTTON_B] = "b";
	buttonLabels[GP2X_BUTTON_X] = "x";
	buttonLabels[GP2X_BUTTON_Y] = "y";
	buttonLabels[GP2X_BUTTON_L] = "l";
	buttonLabels[GP2X_BUTTON_R] = "r";
	buttonLabels[GP2X_BUTTON_START] = "start";
	buttonLabels[GP2X_BUTTON_SELECT] = "select";
	buttonLabels[GP2X_BUTTON_VOLUP] = "vol+";
	buttonLabels[GP2X_BUTTON_VOLDOWN] = "vol-";
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
	bg.box(x-2, 90, boxW+5, 61, 255,255,255);
	//draw inner rectangle
	bg.rectangle(x, 92, boxW, 36, 80,80,80);
	//icon+text
	x += 10;
	if (gmenu2x->sc[icon] != NULL) {
		gmenu2x->sc[icon]->blit( &bg, x-3, 94 );
		x += 37;
	}
	bg.write( gmenu2x->font, text, x, 110, SFontHAlignLeft, SFontVAlignMiddle );

	int btnX = 158+halfBoxW;
	for (uint i=0; i<buttons.size(); i++) {
		if (buttons[i]!="")
			btnX = gmenu2x->drawButtonRight(&bg, buttonLabels[i], buttons[i], btnX, 140);
	}

	bg.blit(gmenu2x->s,0,0);
	gmenu2x->s->flip();

	while (result<0) {
#ifdef TARGET_GP2X
		gmenu2x->joy.update();
		for (uint i=0; i<buttons.size(); i++)
			if (buttons[i]!="" && gmenu2x->joy[i]) result = i;
#else
		while (SDL_PollEvent(&gmenu2x->event)) {
			if ( gmenu2x->event.type == SDL_QUIT ) result = GP2X_BUTTON_X;
			if ( gmenu2x->event.type==SDL_KEYDOWN ) {
				if ( gmenu2x->event.key.keysym.sym==SDLK_ESCAPE ) result = GP2X_BUTTON_X;
				if ( gmenu2x->event.key.keysym.sym==SDLK_RETURN ) result = GP2X_BUTTON_B;
			}
		}
#endif
	}

	return result;
}
