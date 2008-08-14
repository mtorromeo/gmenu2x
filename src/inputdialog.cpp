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
	keyboard.resize(7);

	keyboard[0].push_back("abcdefghijklm");
	keyboard[0].push_back("nopqrstuvwxyz");
	keyboard[0].push_back("0123456789");

	keyboard[1].push_back("ABCDEFGHIJKLM");
	keyboard[1].push_back("NOPQRSTUVWXYZ");
	keyboard[1].push_back("_\"'`.,:;!?");


	keyboard[2].push_back("¡¿*+-/\\&<=>|");
	keyboard[2].push_back("()[]{}@#$%^~ ");
	keyboard[2].push_back("_\"'`.,:;!?");


	keyboard[3].push_back("àáèéìíòóùúýäõ");
	keyboard[3].push_back("ëïöüÿâêîôûåãñ");
	keyboard[3].push_back("čďěľĺňôřŕšťůž");

	keyboard[4].push_back("ÀÁÈÉÌÍÒÓÙÚÝÄÕ");
	keyboard[4].push_back("ËÏÖÜŸÂÊÎÔÛÅÃÑ");
	keyboard[4].push_back("ČĎĚĽĹŇÔŘŔŠŤŮŽ");


	keyboard[5].push_back("æçабвгдеёжзий ");
	keyboard[5].push_back("клмнопрстуфхцч");
	keyboard[5].push_back("шщъыьэюяøðßÐÞþ");

	keyboard[6].push_back("ÆÇАБВГДЕЁЖЗИЙ ");
	keyboard[6].push_back("КЛМНОПРСТУФХЦЧ");
	keyboard[6].push_back("ШЩЪЫЬЭЮЯØðßÐÞþ");

// 	keyboard.resize(2);
//
// 	keyboard[0].push_back("abcdefghijklm _\"'`.,:;!?");
// 	keyboard[0].push_back("nopqrstuvwxyz 0123456789");
// 	keyboard[0].push_back("¡¿*+-/\\&<=>|()[]{}@#$%^~");
// 	keyboard[0].push_back("àáèéìíòóùúýäëïöüÿâêîôûåã");
// 	keyboard[0].push_back("õñæçабвгдеёжзийклмнопрст");
// 	keyboard[0].push_back("уфхцчшщъыьэюяøðßÐÞþ");
// 	keyboard[0].push_back("čďěľĺňôřŕšťůž");
//
// 	keyboard[1].push_back("ABCDEFGHIJKLM _\"'`.,:;!?");
// 	keyboard[1].push_back("NOPQRSTUVWXYZ 0123456789");
// 	keyboard[1].push_back("¡¿*+-/\\&<=>|()[]{}@#$%^~");
// 	keyboard[1].push_back("ÀÁÈÉÌÍÒÓÙÚÝÄËÏÖÜŸÂÊÎÔÛÅÃ");
// 	keyboard[1].push_back("ÕÑÆÇАБВГДЕЁЖЗИЙКЛМНОПРСТ");
// 	keyboard[1].push_back("УФХЦЧШЩЪЫЬЭЮЯØðßÐÞþ");
// 	keyboard[1].push_back("ČĎĚĽĹŇÔŘŔŠŤŮŽ");

	setKeyboard(0);
}

void InputDialog::setKeyboard(int kb) {
	kb = constrain(kb,0,keyboard.size()-1);
	curKeyboard = kb;
	this->kb = &(keyboard[kb]);
	kbLength = this->kb->at(0).length();
	for (int x = 0, l = kbLength; x<l; x++)
		if (gmenu2x->font->utf8Code(this->kb->at(0)[x])) {
			kbLength--;
			x++;
		}
}

bool InputDialog::exec() {
	SDL_Rect box = {0, 50, 0, gmenu2x->font->getHeight()+4};

	Uint32 caretTick = 0, curTick;
	bool caretOn = true;

	bool close = false, ok = true;
	while (!close) {
		gmenu2x->bg->blit(gmenu2x->s,0,0);
		gmenu2x->writeTitle(text);

		gmenu2x->drawButton(gmenu2x->s, "y", gmenu2x->tr["Change keys"],
		gmenu2x->drawButton(gmenu2x->s, "b", gmenu2x->tr["Confirm"],
		gmenu2x->drawButton(gmenu2x->s, "r", gmenu2x->tr["Space"],
		gmenu2x->drawButton(gmenu2x->s, "l", gmenu2x->tr["Backspace"],
		gmenu2x->drawButton(gmenu2x->s, "x", "", 5)-10))));

		box.w = gmenu2x->font->getTextWidth(input)+18;
		box.x = 160-box.w/2;
		gmenu2x->s->box(box.x, box.y, box.w, box.h, gmenu2x->selectionColor);
		gmenu2x->s->rectangle(box.x, box.y, box.w, box.h, gmenu2x->selectionColor);

		gmenu2x->s->write(gmenu2x->font, input, box.x+5, box.y+box.h-2, SFontHAlignLeft, SFontVAlignBottom);

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
			if (selRow==(int)kb->size()) selCol = selCol<8 ? 0 : 1;
		}
		if ( gmenu2x->joy[GP2X_BUTTON_X] || gmenu2x->joy[GP2X_BUTTON_L] ) {
			//                                      check for utf8 characters
			input = input.substr(0,input.length()-( gmenu2x->font->utf8Code(input[input.length()-2]) ? 2 : 1));
		}
		if ( gmenu2x->joy[GP2X_BUTTON_R    ] ) input += " ";
		if ( gmenu2x->joy[GP2X_BUTTON_Y    ] ) {
			if (curKeyboard==6)
				setKeyboard(0);
			else
				setKeyboard(curKeyboard+1);
		}
		if ( gmenu2x->joy[GP2X_BUTTON_B] || gmenu2x->joy[GP2X_BUTTON_CLICK] ) {
			if (selRow==kb->size()) {
				if (selCol==0)
					ok = false;
				close = true;
			} else {
				bool utf8;
				for (uint x=0, xc=0; x<kb->at(selRow).length(); x++) {
					utf8 = gmenu2x->font->utf8Code(kb->at(selRow)[x]);
					if (xc==selCol) input += kb->at(selRow).substr(x, utf8 ? 2 : 1);
					if (utf8) x++;
					xc++;
				}
			}
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
					if (selRow==(int)kb->size()) selCol = selCol<8 ? 0 : 1;
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_BACKSPACE ) {
					//                                      check for utf8 characters
					input = input.substr(0,input.length()-( gmenu2x->font->utf8Code(input[input.length()-2]) ? 2 : 1 ));
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_LSHIFT    ) {
					if (curKeyboard==6)
						setKeyboard(0);
					else
						setKeyboard(curKeyboard+1);
				}
				if ( gmenu2x->event.key.keysym.sym==SDLK_RETURN    ) {
					if (selRow==(int)kb->size()) {
						if (selCol==0)
							ok = false;
						close = true;
					} else {
						bool utf8;
						int xc=0;
						for (uint x=0; x<kb->at(selRow).length(); x++) {
							utf8 = gmenu2x->font->utf8Code(kb->at(selRow)[x]);
							if (xc==selCol) input += kb->at(selRow).substr(x, utf8 ? 2 : 1);
							if (utf8) x++;
							xc++;
						}
					}
				}
			}
		}
#endif
	}

	return ok;
}

void InputDialog::drawVirtualKeyboard() {
	//keyboard border
	gmenu2x->s->rectangle(157-kbLength*5, 73, kbLength*10+4, kb->size()*15+18, gmenu2x->selectionColor);
	uint left = 160-kbLength*5;

	if (selCol<0) selCol = selRow==(int)kb->size() ? 1 : kbLength-1;
	if (selCol>=(int)kbLength) selCol = 0;
	if (selRow<0) selRow = kb->size()-1;
	if (selRow>(int)kb->size()) selRow = 0;

	//selection
	if (selRow<(int)kb->size())
		gmenu2x->s->box(left+selCol*10-1, 75+selRow*15, 10, 13, gmenu2x->selectionColor);
	else {
		if (selCol>1) selCol = 0;
		if (selCol<0) selCol = 1;
		gmenu2x->s->box(left+selCol*kbLength*5-1, 75+kb->size()*15, kbLength*5, 14, gmenu2x->selectionColor);
	}

	//keys
	for (uint l=0; l<kb->size(); l++) {
		string line = kb->at(l);
		for (uint x=0, xc=0; x<line.length(); x++) {
			string charX;
			//utf8 characters
			if (gmenu2x->font->utf8Code(line[x])) {
				charX = line.substr(x,2);
				x++;
			} else
				charX = line[x];
			gmenu2x->s->write(gmenu2x->font, charX, left+4+xc*10, 81+l*15, SFontHAlignCenter, SFontVAlignMiddle);
			xc++;
		}
	}

	//Ok/Cancel
	gmenu2x->s->write(gmenu2x->font, gmenu2x->tr["Cancel"], (int)(160-kbLength*2.5), 81+kb->size()*15, SFontHAlignCenter, SFontVAlignMiddle);
	gmenu2x->s->write(gmenu2x->font, gmenu2x->tr["OK"], (int)(160+kbLength*2.5), 81+kb->size()*15, SFontHAlignCenter, SFontVAlignMiddle);
}
