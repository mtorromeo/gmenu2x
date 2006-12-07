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
#include "textdialog.h"

using namespace std;

TextDialog::TextDialog(GMenu2X *gmenu2x, string title, string description, string icon, vector<string> *text) {
	this->gmenu2x = gmenu2x;
	this->text = text;
	this->title = title;
	this->description = description;
	this->icon = icon;
	preProcess();
}

void TextDialog::preProcess() {
	uint i=0;
	string row;
	
	while (i<text->size()) {
		//clean this row
		row = trim(text->at(i));
		
		//check if this row is not too long
		if (gmenu2x->font->getTextWidth(row)>305) {
			vector<string> words;
			split(words, row, " ");
			
			uint numWords = words.size();
			//find the maximum number of rows that can be printed on screen
			while (gmenu2x->font->getTextWidth(row)>305 && numWords>0) {
				numWords--;
				row = "";
				for (uint x=0; x<numWords; x++)
					row += words[x] + " ";
				row = trim(row);
			}
			
			//if numWords==0 then the string must be printed as-is, it cannot be split
			if (numWords>0) {
				vector<string>::iterator it = text->begin();
				it += i;
			
				//delete the original string and replace with the shorter version
				text->erase(it);
				text->insert(it, row);
				
				//build the remaining text in another row
				row = "";
				for (uint x=numWords; x<words.size(); x++)
					row += words[x] + " ";
				row = trim(row);
				
				if (!row.empty())
					text->insert(it+1, row);
			}
		}
		i++;
	}
}

void TextDialog::exec() {
	bool close = false;

	Surface bg("imgs/bg.png");
	gmenu2x->drawTopBar(&bg);
	gmenu2x->drawBottomBar(&bg);
	
	//link icon
	Surface sIcon(icon);
	sIcon.blit(&bg,4,4);
	//selector text
	bg.write(gmenu2x->font,title,40,13, SFontHAlignLeft, SFontVAlignMiddle);
	bg.write(gmenu2x->font,description,40,27, SFontHAlignLeft, SFontVAlignMiddle);

	gmenu2x->drawButton(&bg, "v", "Scroll",
	gmenu2x->drawButton(&bg, "^", "", 10)-4);

	uint firstRow = 0, rowsPerPage = 180/gmenu2x->font->getHeight(), i;
	int rowY;
	while (!close) {
		bg.blit(gmenu2x->s,0,0);

		//Text
		gmenu2x->s->setClipRect(0,412,311,180);
		gmenu2x->s->clearClipRect();
		
		for (i=firstRow; i<firstRow+rowsPerPage && i<text->size(); i++) {
			if (text->at(i)=="----") { //draw a line
				rowY = 42+(int)((i-firstRow+0.5)*gmenu2x->font->getHeight());
				gmenu2x->s->hline(5,rowY,305,255,255,255,255);
				gmenu2x->s->hline(5,rowY+1,305,0,0,0,255);
			} else {
				rowY = 42+(i-firstRow)*gmenu2x->font->getHeight();
				gmenu2x->font->write(gmenu2x->s, text->at(i), 5, rowY);
			}
		}

		gmenu2x->drawScrollBar(rowsPerPage,text->size(),firstRow,42,175);
		gmenu2x->s->flip();


#ifdef TARGET_GP2X
		gmenu2x->joy.update();
		if ( gmenu2x->joy[GP2X_BUTTON_UP] && firstRow>0 ) firstRow--;
		if ( gmenu2x->joy[GP2X_BUTTON_DOWN] && firstRow+rowsPerPage<text->size() ) firstRow++;
		if ( gmenu2x->joy[GP2X_BUTTON_START] ) close = true;
#else
		while (SDL_PollEvent(&gmenu2x->event)) {
			if ( gmenu2x->event.type == SDL_QUIT ) close = true;
			if ( gmenu2x->event.type==SDL_KEYDOWN ) {
				if ( gmenu2x->event.key.keysym.sym==SDLK_ESCAPE ) close = true;
				if ( gmenu2x->event.key.keysym.sym==SDLK_UP && firstRow>0 ) firstRow--;
				if ( gmenu2x->event.key.keysym.sym==SDLK_DOWN && firstRow+rowsPerPage<text->size() ) firstRow++;
			}
		}
#endif
	}
}
