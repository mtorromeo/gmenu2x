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

#include <SDL_gfxPrimitives.h>

#include <iostream>
using namespace std;

#include "surface.h"
#include "utilities.h"

Surface::Surface() {
	raw = NULL;
}

Surface::Surface(string img) {
	raw = NULL;
	load(img);
	halfW = raw->w/2;
	halfH = raw->h/2;
}

Surface::Surface(SDL_Surface *s) {
	raw = SDL_ConvertSurface( s, s->format, s->flags );
	halfW = raw->w/2;
	halfH = raw->h/2;
}

Surface::Surface(Surface *s) {
	raw = SDL_ConvertSurface( s->raw, s->raw->format, s->raw->flags );
	halfW = raw->w/2;
	halfH = raw->h/2;
}

Surface::Surface(int w, int h, Uint32 flags) {
	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif
	raw = SDL_CreateRGBSurface( flags, w, h, 16, rmask, gmask, bmask, amask );
	halfW = w/2;
	halfH = h/2;
}

Surface::~Surface() {
	free();
}

void Surface::free() {
	if (raw!=NULL) SDL_FreeSurface( raw );
}

SDL_PixelFormat *Surface::format() {
	if (raw==NULL)
		return NULL;
	else
		return raw->format;
}

void Surface::load(string img) {
	free();
	SDL_Surface *buf = IMG_Load(img.c_str());
	if (buf!=NULL) {
		//raw = SDL_DisplayFormat(buf);
		raw = SDL_DisplayFormatAlpha(buf);
		SDL_FreeSurface(buf);
	}
}

void Surface::lock() {
	if ( SDL_MUSTLOCK(raw) && !locked ) {
		if ( SDL_LockSurface(raw) < 0 ) {
			fprintf(stderr, "Can't lock surface: %s\n", SDL_GetError());
			SDL_Quit();
		}
		locked = true;
	}
}

void Surface::unlock() {
	if ( SDL_MUSTLOCK(raw) && locked ) {
		SDL_UnlockSurface(raw);
		locked = false;
	}
}

void Surface::flip() {
	SDL_Flip(raw);
}

bool Surface::blit(SDL_Surface *destination, int x, int y, int w, int h) {
	SDL_Rect src = {0,0,w,h};
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	return SDL_BlitSurface(raw, (w==0 || h==0) ? NULL : &src, destination, &dest);
}
bool Surface::blit(Surface *destination, int x, int y, int w, int h) {
	return blit(destination->raw,x,y,w,h);
}

bool Surface::blitCenter(SDL_Surface *destination, int x, int y, int w, int h) {
	int oh, ow;
	if (w==0) ow = halfW; else ow = min(halfW,w/2);
	if (h==0) oh = halfH; else oh = min(halfH,h/2);
	return blit(destination,x-ow,y-oh,w,h);
}
bool Surface::blitCenter(Surface *destination, int x, int y, int w, int h) {
	return blitCenter(destination->raw,x,y,w,h);
}

bool Surface::blitRight(SDL_Surface *destination, int x, int y, int w, int h) {
	return blit(destination,x-min(raw->w,w),y,w,h);
}
bool Surface::blitRight(Surface *destination, int x, int y, int w, int h) {
	return blitRight(destination->raw,x,y,w,h);
}

void Surface::putPixel(int x, int y, Uint32 color) {
	int bpp = raw->format->BytesPerPixel;
	// Here p is the address to the pixel we want to set
	Uint8 *p = (Uint8 *)raw->pixels + y * raw->pitch + x * bpp;

	switch(bpp) {
	case 1:
			*p = color;
			break;
	case 2:
			*(Uint16 *)p = color;
			break;
	case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
					p[0] = (color >> 16) & 0xff;
					p[1] = (color >> 8) & 0xff;
					p[2] = color & 0xff;
			} else {
					p[0] = color & 0xff;
					p[1] = (color >> 8) & 0xff;
					p[2] = (color >> 16) & 0xff;
			}
			break;
	case 4:
			*(Uint32 *)p = color;
			break;
	}
}

void Surface::write(ASFont *font, string text, int x, int y, const unsigned short halign, const unsigned short valign) {
	font->write(this,text,x,y,halign,valign);
}

void Surface::operator = (Surface *s) {
	raw = s->raw;
	raw->refcount++;
}

int Surface::box(Sint16 x, Sint16 y, Sint16 w, Sint16 h, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	return boxRGBA(raw,x,y,x+w,y+h,r,g,b,a);
}
int Surface::box(Sint16 x, Sint16 y, Sint16 w, Sint16 h, RGBAColor c) {
	return box(x,y,w,h,c.r,c.g,c.b,c.a);
}

int Surface::rectangle(Sint16 x, Sint16 y, Sint16 w, Sint16 h, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	return rectangleRGBA(raw,x,y,x+w,y+h,r,g,b,a);
}
int Surface::rectangle(Sint16 x, Sint16 y, Sint16 w, Sint16 h, RGBAColor c) {
	return rectangle(x,y,w,h,c.r,c.g,c.b,c.a);
}

int Surface::hline(Sint16 x, Sint16 y, Sint16 w, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	return hlineRGBA(raw,x,x+w,y,r,g,b,a);
}
int Surface::hline(Sint16 x, Sint16 y, Sint16 w, RGBAColor c) {
	return hline(x,y,w,c.r,c.g,c.b,c.a);
}
