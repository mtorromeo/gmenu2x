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
#include "messagebox.h"

using namespace std;

MessageBox::MessageBox(GMenu2X *gmenu2x, string text, string icon) {
	this->gmenu2x = gmenu2x;
	this->text = text;
	this->icon = icon;
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
	bg.box(x-2, 97, boxW+5, 47, 255,255,255);
	//draw inner rectangle
	bg.rectangle(x, 99, boxW, 42, 80,80,80);
	//text
	x += 10;
	if (gmenu2x->sc[icon] != NULL) {
		gmenu2x->sc[icon]->blit( &bg, x-3, 104 );
		x += 37;
	}
	bg.write( gmenu2x->font, text, x, 121, SFontHAlignLeft, SFontVAlignMiddle );

	/*
	gmenu2x->drawButton(&bg, "S", "Confirm",
	gmenu2x->drawButton(&bg, "B", "Enter folder",
	gmenu2x->drawButton(&bg, "A", "Up one folder", 10)));
	*/
	
	bg.blit(gmenu2x->s,0,0);
	gmenu2x->s->flip();

	while (result<0) {
#ifdef TARGET_GP2X
		gmenu2x->joy.update();
		if ( (gmenu2x->joy[GP2X_BUTTON_B] || gmenu2x->joy[GP2X_BUTTON_CLICK]) && selected<directories.size() ) result = 1;
		if ( gmenu2x->joy[GP2X_BUTTON_START] ) result = 0;
#else
		while (SDL_PollEvent(&gmenu2x->event)) {
			if ( gmenu2x->event.type == SDL_QUIT ) result = 0;
			if ( gmenu2x->event.type==SDL_KEYDOWN ) {
				if ( gmenu2x->event.key.keysym.sym==SDLK_ESCAPE ) result = 0;
				if ( gmenu2x->event.key.keysym.sym==SDLK_RETURN ) result = 1;
			}
		}
#endif
	}

	return result;
}
