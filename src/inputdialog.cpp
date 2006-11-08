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

#ifdef TARGET_GP2X
#include "gp2x.h"
#endif
#include "inputdialog.h"

using namespace std;

InputDialog::InputDialog(GMenu2X *gmenu2x, string text, string startvalue) {
	this->gmenu2x = gmenu2x;
	this->text = text;
	input = startvalue;
	selCol = 0;
	selRow = 0;

	keyboard.resize(5);
	keyboard[0] = "abcdefghijklm";
	keyboard[1] = "nopqrstuvwxyz";
	keyboard[2] = "0123456789 \"'";
	keyboard[3] = "&!?.,:;*+-<=>";
	keyboard[4] = "()[]{}|/\\@#$%";
//^_`~
}

bool InputDialog::exec() {
	bool close = false, ok = true;
	Surface bg("imgs/bg.png");

	SDL_Rect box = {0, 60, 0, gmenu2x->font->getHeight()+4};

	Uint32 caretTick = 0, curTick;
	bool caretOn = true;

	gmenu2x->drawTopBar(&bg,15);
	gmenu2x->drawBottomBar(&bg);
	bg.write(gmenu2x->font, text, 160, 8, SFontHAlignCenter, SFontVAlignMiddle);

	gmenu2x->drawButton(&bg, "Y", "Shift",
	gmenu2x->drawButton(&bg, "B", "Confirm",
	gmenu2x->drawButton(&bg, "R", "Space",
	gmenu2x->drawButton(&bg, "L", "Backspace",
	gmenu2x->drawButton(&bg, "A", "/", 10)-4))));

	while (!close) {
		bg.blit(gmenu2x->s,0,0);

		box.w = gmenu2x->font->getTextWidth(input)+18;
		box.x = 160-box.w/2;
		gmenu2x->s->box(box.x, box.y, box.w, box.h, gmenu2x->selectionColor);
		gmenu2x->s->rectangle(box.x, box.y, box.w, box.h, gmenu2x->selectionColor);

		gmenu2x->s->write(gmenu2x->font, input, box.x+5, box.y+box.h, SFontHAlignLeft, SFontVAlignBottom);

		curTick = SDL_GetTicks();
		if (curTick-caretTick>=600) {
			caretOn = !caretOn;
			caretTick = curTick;
		}

		if (caretOn) gmenu2x->s->box(box.x+box.w-12, box.y+3, 8, box.h-6, gmenu2x->selectionColor);

		drawVirtualKeyboard();

		gmenu2x->s->flip();

#ifdef TARGET_GP2X
		gmenu2x->joy.update();
		// LINK NAVIGATION
		if ( gmenu2x->joy[GP2X_BUTTON_LEFT ] ) selCol--;
		if ( gmenu2x->joy[GP2X_BUTTON_RIGHT] ) selCol++;
		if ( gmenu2x->joy[GP2X_BUTTON_UP   ] ) selRow--;
		if ( gmenu2x->joy[GP2X_BUTTON_DOWN ] ) {
			selRow++;
			if (selRow==(int)keyboard.size()) selCol = selCol<8 ? 0 : 1;
		}
		if ( gmenu2x->joy[GP2X_BUTTON_A] || gmenu2x->joy[GP2X_BUTTON_L] ) input = input.substr(0,input.length()-1);
		if ( gmenu2x->joy[GP2X_BUTTON_R    ] ) input += " ";
		if ( gmenu2x->joy[GP2X_BUTTON_Y    ] ) {
			if (keyboard[0][0]=='A') {
				keyboard[0] = "abcdefghijklm";
				keyboard[1] = "nopqrstuvwxyz";
			} else {
				keyboard[0] = "ABCDEFGHIJKLM";
				keyboard[1] = "NOPQRSTUVWXYZ";
			}
		}
		if ( gmenu2x->joy[GP2X_BUTTON_B] || gmenu2x->joy[GP2X_BUTTON_CLICK] ) {
			if (selRow==keyboard.size()) {
				if (selCol==0)
					ok = false;
				close = true;
			} else
				input += keyboard[selRow][selCol];
		}
		if ( gmenu2x->joy[GP2X_BUTTON_START] ) close = true;
#else
		while (SDL_PollEvent(&gmenu2x->event)) {
			if ( gmenu2x->event.type==SDL_KEYDOWN ) {
				if ( gmenu2x->event.key.keysym.sym==SDLK_ESCAPE ) { ok = false; close = true; }
				// LINK NAVIGATION
				if ( gmenu2x->event.key.keysym.sym==SDLK_LEFT      ) selCol--;
				if ( gmenu2x->event.key.keysym.sym==SDLK_RIGHT     ) selCol++;
				if ( gmenu2x->event.key.keysym.sym==SDLK_UP        ) selRow--;
				if ( gmenu2x->event.key.keysym.sym==SDLK_DOWN      )  {
					selRow++;
					if (selRow==(int)keyboard.size()) selCol = selCol<8 ? 0 : 1;
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_BACKSPACE ) input = input.substr(0,input.length()-1);
				if ( gmenu2x->event.key.keysym.sym==SDLK_LSHIFT    ) {
					if (keyboard[0][0]=='A') {
						keyboard[0] = "abcdefghijklm";
						keyboard[1] = "nopqrstuvwxyz";
					} else {
						keyboard[0] = "ABCDEFGHIJKLM";
						keyboard[1] = "NOPQRSTUVWXYZ";
					}
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_RETURN    ) {
					if (selRow==(int)keyboard.size()) {
						if (selCol==0)
							ok = false;
						close = true;
					} else
						input += keyboard[selRow][selCol];
				}
			}
		}
#endif
	}

	return ok;
}

void InputDialog::drawVirtualKeyboard() {
	//keyboard border
	gmenu2x->s->rectangle(157-keyboard[0].length()*5, 88, keyboard[0].length()*10+4, keyboard.size()*15+18, gmenu2x->selectionColor);
	uint left = 160-keyboard[0].length()*5;

	if (selCol<0) selCol = selRow==(int)keyboard.size() ? 1 : keyboard[0].length()-1;
	if (selCol>=(int)keyboard[0].length()) selCol = 0;
	if (selRow<0) selRow = keyboard.size()-1;
	if (selRow>(int)keyboard.size()) selRow = 0;

	//selection
	if (selRow<(int)keyboard.size())
		gmenu2x->s->box(left+selCol*10-1, 90+selRow*15, 10, 13, gmenu2x->selectionColor);
	else {
		if (selCol>1) selCol = 0;
		if (selCol<0) selCol = 1;
		gmenu2x->s->box(left+selCol*keyboard[0].length()*5-1, 90+keyboard.size()*15, keyboard[0].length()*5, 14, gmenu2x->selectionColor);
	}

	//keys
	for (uint l=0; l<keyboard.size(); l++) {
		string line = keyboard[l];
		for (uint x=0; x<line.length(); x++) {
			string charX = line.substr(x,1);
			gmenu2x->s->write(gmenu2x->font, charX, left+4+x*10, 98+l*15, SFontHAlignCenter, SFontVAlignMiddle);
		}
	}

	//Ok/Cancel
	gmenu2x->s->write(gmenu2x->font, "Cancel", (int)(160-keyboard[0].length()*2.5), 98+keyboard.size()*15, SFontHAlignCenter, SFontVAlignMiddle);
	gmenu2x->s->write(gmenu2x->font, "OK", (int)(160+keyboard[0].length()*2.5), 98+keyboard.size()*15, SFontHAlignCenter, SFontVAlignMiddle);
}
