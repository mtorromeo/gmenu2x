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

#include "inputdialog.h"

using namespace std;
using namespace fastdelegate;

InputDialog::InputDialog(GMenu2X *gmenu2x, string text, string startvalue, string title, string icon) {
	this->gmenu2x = gmenu2x;
	if (title=="") {
		this->title = text;
		this->text = "";
	} else {
		this->title = title;
		this->text = text;
	}
	this->icon = "";
	if (icon!="" && gmenu2x->sc[icon] != NULL)
		this->icon = icon;

	input = startvalue;
	selCol = 0;
	selRow = 0;
	keyboard.resize(7);

	keyboard[0].push_back("abcdefghijklm");
	keyboard[0].push_back("nopqrstuvwxyz");
	keyboard[0].push_back("0123456789.  ");

	keyboard[1].push_back("ABCDEFGHIJKLM");
	keyboard[1].push_back("NOPQRSTUVWXYZ");
	keyboard[1].push_back("_\"'`.,:;!?   ");


	keyboard[2].push_back("¡¿*+-/\\&<=>|");
	keyboard[2].push_back("()[]{}@#$%^~");
	keyboard[2].push_back("_\"'`.,:;!?  ");


	keyboard[3].push_back("àáèéìíòóùúýäõ");
	keyboard[3].push_back("ëïöüÿâêîôûåãñ");
	keyboard[3].push_back("čďěľĺňôřŕšťůž");
	keyboard[3].push_back("ąćęłńśżź     ");

	keyboard[4].push_back("ÀÁÈÉÌÍÒÓÙÚÝÄÕ");
	keyboard[4].push_back("ËÏÖÜŸÂÊÎÔÛÅÃÑ");
	keyboard[4].push_back("ČĎĚĽĹŇÔŘŔŠŤŮŽ");
	keyboard[4].push_back("ĄĆĘŁŃŚŻŹ     ");


	keyboard[5].push_back("æçабвгдеёжзий ");
	keyboard[5].push_back("клмнопрстуфхцч");
	keyboard[5].push_back("шщъыьэюяøðßÐÞþ");

	keyboard[6].push_back("ÆÇАБВГДЕЁЖЗИЙ ");
	keyboard[6].push_back("КЛМНОПРСТУФХЦЧ");
	keyboard[6].push_back("ШЩЪЫЬЭЮЯØðßÐÞþ");

	setKeyboard(0);

	ButtonAction actBackspace = MakeDelegate(this, &InputDialog::backspace);

	btnBackspaceX = new IconButton(gmenu2x, "skin:imgs/buttons/x.png");
	btnBackspaceX->setAction(actBackspace);

	btnBackspaceL = new IconButton(gmenu2x, "skin:imgs/buttons/l.png", gmenu2x->tr["Backspace"]);
	btnBackspaceL->setAction(actBackspace);

	btnSpace = new IconButton(gmenu2x, "skin:imgs/buttons/r.png", gmenu2x->tr["Space"]);
	btnSpace->setAction(MakeDelegate(this, &InputDialog::space));

	btnConfirm = new IconButton(gmenu2x, "skin:imgs/buttons/b.png", gmenu2x->tr["Confirm"]);
	btnConfirm->setAction(MakeDelegate(this, &InputDialog::confirm));

	btnChangeKeys = new IconButton(gmenu2x, "skin:imgs/buttons/y.png", gmenu2x->tr["Change keys"]);
	btnChangeKeys->setAction(MakeDelegate(this, &InputDialog::changeKeys));
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

	kbLeft = 160 - kbLength*KEY_WIDTH/2;
	kbWidth = kbLength*KEY_WIDTH+3;
	kbHeight = (this->kb->size()+1)*KEY_HEIGHT+3;

	kbRect.x = kbLeft-3;
	kbRect.y = KB_TOP-2;
	kbRect.w = kbWidth;
	kbRect.h = kbHeight;
}

bool InputDialog::exec() {
	SDL_Rect box = {0, 60, 0, gmenu2x->font->getHeight()+4};

	Uint32 caretTick = 0, curTick;
	bool caretOn = true;

	uint action;
	close = false;
	ok = true;
	while (!close) {
		gmenu2x->bg->blit(gmenu2x->s,0,0);
		gmenu2x->writeTitle(title);
		gmenu2x->writeSubTitle(text);
		gmenu2x->drawTitleIcon(icon);

		gmenu2x->drawButton(gmenu2x->s, "y", gmenu2x->tr["Change keys"],
		gmenu2x->drawButton(gmenu2x->s, "b", gmenu2x->tr["Confirm"],
		gmenu2x->drawButton(gmenu2x->s, "r", gmenu2x->tr["Space"],
		gmenu2x->drawButton(btnBackspaceL,
		gmenu2x->drawButton(btnBackspaceX)-6))));

		box.w = gmenu2x->font->getTextWidth(input)+18;
		box.x = 160-box.w/2;
		gmenu2x->s->box(box.x, box.y, box.w, box.h, gmenu2x->skinConfColors["selectionBg"]);
		gmenu2x->s->rectangle(box.x, box.y, box.w, box.h, gmenu2x->skinConfColors["selectionBg"]);

		gmenu2x->s->write(gmenu2x->font, input, box.x+5, box.y+box.h-2, SFontHAlignLeft, SFontVAlignBottom);

		curTick = SDL_GetTicks();
		if (curTick-caretTick>=600) {
			caretOn = !caretOn;
			caretTick = curTick;
		}

		if (caretOn) gmenu2x->s->box(box.x+box.w-12, box.y+3, 8, box.h-6, gmenu2x->skinConfColors["selectionBg"]);

		if (gmenu2x->f200) gmenu2x->ts.poll();
		action = drawVirtualKeyboard();
		gmenu2x->s->flip();

		gmenu2x->input.update();
		if ( gmenu2x->input[ACTION_START] ) action = ID_ACTION_CLOSE;
		if ( gmenu2x->input[ACTION_UP   ] ) action = ID_ACTION_UP;
		if ( gmenu2x->input[ACTION_DOWN ] ) action = ID_ACTION_DOWN;
		if ( gmenu2x->input[ACTION_LEFT ] ) action = ID_ACTION_LEFT;
		if ( gmenu2x->input[ACTION_RIGHT] ) action = ID_ACTION_RIGHT;
		if ( gmenu2x->input[ACTION_B]     ) action = ID_ACTION_SELECT;
		if ( gmenu2x->input[ACTION_Y]     ) action = ID_ACTION_KB_CHANGE;
		if ( gmenu2x->input[ACTION_X] || gmenu2x->input[ACTION_L] ) action = ID_ACTION_BACKSPACE;
		if ( gmenu2x->input[ACTION_R    ] ) action = ID_ACTION_SPACE;

		switch (action) {
			case ID_ACTION_CLOSE: {
				ok = false;
				close = true;
			} break;
			case ID_ACTION_UP: {
				selRow--;
			} break;
			case ID_ACTION_DOWN: {
				selRow++;
				if (selRow==(int)kb->size()) selCol = selCol<8 ? 0 : 1;
			} break;
			case ID_ACTION_LEFT: {
				selCol--;
			} break;
			case ID_ACTION_RIGHT: {
				selCol++;
			} break;
			case ID_ACTION_BACKSPACE: backspace(); break;
			case ID_ACTION_SPACE: space(); break;
			case ID_ACTION_KB_CHANGE: changeKeys(); break;
			case ID_ACTION_SELECT: confirm(); break;
		}
	}

	return ok;
}

void InputDialog::backspace() {
	//                                      check for utf8 characters
	input = input.substr(0,input.length()-( gmenu2x->font->utf8Code(input[input.length()-2]) ? 2 : 1 ));
}

void InputDialog::space() {
	//                                      check for utf8 characters
	input += " ";
}

void InputDialog::confirm() {
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

void InputDialog::changeKeys() {
	if (curKeyboard==6)
		setKeyboard(0);
	else
		setKeyboard(curKeyboard+1);
}

int InputDialog::drawVirtualKeyboard() {
	int action = ID_NO_ACTION;

	//keyboard border
	gmenu2x->s->rectangle(kbRect, gmenu2x->skinConfColors["selectionBg"]);

	if (selCol<0) selCol = selRow==(int)kb->size() ? 1 : kbLength-1;
	if (selCol>=(int)kbLength) selCol = 0;
	if (selRow<0) selRow = kb->size()-1;
	if (selRow>(int)kb->size()) selRow = 0;

	//selection
	if (selRow<(int)kb->size())
		gmenu2x->s->box(kbLeft+selCol*KEY_WIDTH-1, KB_TOP+selRow*KEY_HEIGHT, KEY_WIDTH-1, KEY_HEIGHT-2, gmenu2x->skinConfColors["selectionBg"]);
	else {
		if (selCol>1) selCol = 0;
		if (selCol<0) selCol = 1;
		gmenu2x->s->box(kbLeft+selCol*kbLength*KEY_WIDTH/2-1, KB_TOP+kb->size()*KEY_HEIGHT, kbLength*KEY_WIDTH/2-1, KEY_HEIGHT-1, gmenu2x->skinConfColors["selectionBg"]);
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

			SDL_Rect re = {kbLeft+xc*KEY_WIDTH-1, KB_TOP+l*KEY_HEIGHT, KEY_WIDTH-1, KEY_HEIGHT-2};

			//if ts on rect, change selection
			if (gmenu2x->f200 && gmenu2x->ts.pressed() && gmenu2x->ts.inRect(re)) {
				selCol = xc;
				selRow = l;
			}

			gmenu2x->s->rectangle(re, gmenu2x->skinConfColors["selectionBg"]);
			gmenu2x->s->write(gmenu2x->font, charX, kbLeft+xc*KEY_WIDTH+KEY_WIDTH/2-1, KB_TOP+l*KEY_HEIGHT+KEY_HEIGHT/2, SFontHAlignCenter, SFontVAlignMiddle);
			xc++;
		}
	}

	//Ok/Cancel
	SDL_Rect re = {kbLeft-1, KB_TOP+kb->size()*KEY_HEIGHT, kbLength*KEY_WIDTH/2-1, KEY_HEIGHT-1};
	gmenu2x->s->rectangle(re, gmenu2x->skinConfColors["selectionBg"]);
	if (gmenu2x->f200 && gmenu2x->ts.pressed() && gmenu2x->ts.inRect(re)) {
		selCol = 0;
		selRow = kb->size();
	}
	gmenu2x->s->write(gmenu2x->font, gmenu2x->tr["Cancel"], (int)(160-kbLength*KEY_WIDTH/4), KB_TOP+kb->size()*KEY_HEIGHT+KEY_HEIGHT/2, SFontHAlignCenter, SFontVAlignMiddle);

	re.x = kbLeft+kbLength*KEY_WIDTH/2-1;
	gmenu2x->s->rectangle(re, gmenu2x->skinConfColors["selectionBg"]);
	if (gmenu2x->f200 && gmenu2x->ts.pressed() && gmenu2x->ts.inRect(re)) {
		selCol = 1;
		selRow = kb->size();
	}
	gmenu2x->s->write(gmenu2x->font, gmenu2x->tr["OK"], (int)(160+kbLength*KEY_WIDTH/4), KB_TOP+kb->size()*KEY_HEIGHT+KEY_HEIGHT/2, SFontHAlignCenter, SFontVAlignMiddle);

	//if ts released
	if (gmenu2x->f200 && gmenu2x->ts.wasPressed && !gmenu2x->ts.pressed() && gmenu2x->ts.inRect(kbRect))
		action = ID_ACTION_SELECT;

	return action;
}
