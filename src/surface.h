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
#ifndef SURFACE_H
#define SURFACE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "asfont.h"

using std::string;

struct RGBAColor {
	unsigned short r,g,b,a;
};

/**
Wrapper around SDL_Surface

	@author Massimiliano Torromeo <massimiliano.torromeo@gmail.com>
*/
class Surface {
private:
	bool locked;
	int halfW, halfH;

public:
	Surface();
	Surface(string img, string skin="", bool alpha=true);
	Surface(string img, bool alpha, string skin="");
	Surface(SDL_Surface *s, SDL_PixelFormat *fmt = NULL, Uint32 flags = 0);
	Surface(Surface *s);
	Surface(int w, int h, Uint32 flags = SDL_HWSURFACE|SDL_SRCALPHA);
	~Surface();

	SDL_Surface *raw;

	void free();
	void load(string img, bool alpha=true, string skin="");
	void lock();
	void unlock();
	void flip();
	SDL_PixelFormat *format();

	void putPixel(int,int,SDL_Color);
	void putPixel(int,int,Uint32);
	SDL_Color pixelColor(int,int);
	Uint32 pixel(int,int);

	void blendAdd(Surface*, int,int);

	void clearClipRect();
	void setClipRect(int x, int y, int w, int h);

	bool blit(Surface *destination, int x, int y, int w=0, int h=0, int a=-1);
	bool blit(Surface *destination, SDL_Rect container, const unsigned short halign=0, const unsigned short valign=0);
	bool blit(SDL_Surface *destination, int x, int y, int w=0, int h=0, int a=-1);
	bool blitCenter(Surface *destination, int x, int y, int w=0, int h=0, int a=-1);
	bool blitCenter(SDL_Surface *destination, int x, int y, int w=0, int h=0, int a=-1);
	bool blitRight(Surface *destination, int x, int y, int w=0, int h=0, int a=-1);
	bool blitRight(SDL_Surface *destination, int x, int y, int w=0, int h=0, int a=-1);

	void write(ASFont *font, string text, int x, int y, const unsigned short halign=0, const unsigned short valign=0);

	int box(Sint16, Sint16, Sint16, Sint16, Uint8, Uint8, Uint8, Uint8);
	int box(Sint16, Sint16, Sint16, Sint16, Uint8, Uint8, Uint8);
	int box(Sint16, Sint16, Sint16, Sint16, RGBAColor);
	int rectangle(Sint16, Sint16, Sint16, Sint16, Uint8, Uint8, Uint8, Uint8);
	int rectangle(Sint16, Sint16, Sint16, Sint16, Uint8, Uint8, Uint8);
	int rectangle(Sint16, Sint16, Sint16, Sint16, RGBAColor);
	int hline(Sint16, Sint16, Sint16, Uint8, Uint8, Uint8, Uint8);
	int hline(Sint16, Sint16, Sint16, RGBAColor);

	void operator = (SDL_Surface*);
	void operator = (Surface*);
};

#endif
