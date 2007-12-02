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

Surface::Surface(string img, bool alpha, string skin) {
	raw = NULL;
	load(img, alpha, skin);
	halfW = raw->w/2;
	halfH = raw->h/2;
}

Surface::Surface(string img, string skin, bool alpha) {
	raw = NULL;
	load(img, alpha, skin);
	halfW = raw->w/2;
	halfH = raw->h/2;
}

Surface::Surface(SDL_Surface *s, SDL_PixelFormat *fmt, Uint32 flags) {
	this->operator =(s);
	if (fmt!=NULL || flags!=0) {
		if (fmt==NULL) fmt = s->format;
		if (flags==0) flags = s->flags;
		raw = SDL_ConvertSurface( s, fmt, flags );
	}
}

Surface::Surface(Surface *s) {
	this->operator =(s->raw);
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

void Surface::load(string img, bool alpha, string skin) {
	free();

	string skinpath;
	if (!skin.empty() && !img.empty() && img[0]!='/') {
		skinpath = "skins/"+skin+"/"+img;
		if (!fileExists(skinpath))
			skinpath = "skins/Default/"+img;
		img = skinpath;
	}

	SDL_Surface *buf = IMG_Load(img.c_str());
	if (buf!=NULL) {
		if (alpha)
			raw = SDL_DisplayFormatAlpha(buf);
		else
			raw = SDL_DisplayFormat(buf);
		SDL_FreeSurface(buf);
	} else {
		cout << "Couldn't load surface " << img << endl;
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

bool Surface::blit(SDL_Surface *destination, int x, int y, int w, int h, int a) {
	if (destination == NULL || a==0) return false;

	SDL_Rect src = {0,0,w,h};
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	if (a>0 && a!=raw->format->alpha)
		SDL_SetAlpha(raw, SDL_SRCALPHA|SDL_RLEACCEL, a);
	return SDL_BlitSurface(raw, (w==0 || h==0) ? NULL : &src, destination, &dest);
}
bool Surface::blit(Surface *destination, int x, int y, int w, int h, int a) {
	return blit(destination->raw,x,y,w,h,a);
}

bool Surface::blitCenter(SDL_Surface *destination, int x, int y, int w, int h, int a) {
	int oh, ow;
	if (w==0) ow = halfW; else ow = min(halfW,w/2);
	if (h==0) oh = halfH; else oh = min(halfH,h/2);
	return blit(destination,x-ow,y-oh,w,h,a);
}
bool Surface::blitCenter(Surface *destination, int x, int y, int w, int h, int a) {
	return blitCenter(destination->raw,x,y,w,h,a);
}

bool Surface::blitRight(SDL_Surface *destination, int x, int y, int w, int h, int a) {
	if (!w) w = raw->w;
	return blit(destination,x-min(raw->w,w),y,w,h,a);
}
bool Surface::blitRight(Surface *destination, int x, int y, int w, int h, int a) {
	if (!w) w = raw->w;
	return blitRight(destination->raw,x,y,w,h,a);
}

void Surface::putPixel(int x, int y, SDL_Color color) {
	putPixel(x,y, SDL_MapRGB( raw->format , color.r , color.g , color.b ));
}

void Surface::putPixel(int x, int y, Uint32 color) {
	//determine position
	char* pPosition = ( char* ) raw->pixels ;
	//offset by y
	pPosition += ( raw->pitch * y ) ;
	//offset by x
	pPosition += ( raw->format->BytesPerPixel * x ) ;
	//copy pixel data
	memcpy ( pPosition , &color , raw->format->BytesPerPixel ) ;
}

SDL_Color Surface::pixelColor(int x, int y) {
	SDL_Color color;
	Uint32 col = pixel(x,y);
	SDL_GetRGB( col, raw->format, &color.r, &color.g, &color.b );
	return color;
}

Uint32 Surface::pixel(int x, int y) {
	//determine position
	char* pPosition = ( char* ) raw->pixels ;
	//offset by y
	pPosition += ( raw->pitch * y ) ;
	//offset by x
	pPosition += ( raw->format->BytesPerPixel * x ) ;
	//copy pixel data
	Uint32 col = 0;
	memcpy ( &col , pPosition , raw->format->BytesPerPixel ) ;
	return col;
}

void Surface::blendAdd(Surface *target, int x, int y) {
	SDL_Color targetcol, blendcol;
	for (int iy=0; iy<raw->h; iy++)
		if (iy+y >= 0 && iy+y < target->raw->h)
			for (int ix=0; ix<raw->w; ix++) {
				if (ix+x >= 0 && ix+x < target->raw->w) {
					blendcol = pixelColor(ix,iy);
					targetcol = target->pixelColor(ix+x,iy+y);
					targetcol.r = min(targetcol.r+blendcol.r, 255);
					targetcol.g = min(targetcol.g+blendcol.g, 255);
					targetcol.b = min(targetcol.b+blendcol.b, 255);
					target->putPixel(ix+x,iy+y,targetcol);
				}
			}

/*
	Uint32 bcol, tcol;
	char *pPos, *tpPos;
	for (int iy=0; iy<raw->h; iy++)
		if (iy+y >= 0 && iy+y < target->raw->h) {
			pPos = (char*)raw->pixels + raw->pitch*iy;
			tpPos = (char*)target->raw->pixels + target->raw->pitch*(iy+y);

			for (int ix=0; ix<raw->w; ix++) {
				memcpy(&bcol, pPos, raw->format->BytesPerPixel);
				memcpy(&tcol, tpPos, target->raw->format->BytesPerPixel);
				//memcpy(tpPos, &bcol, target->raw->format->BytesPerPixel);
				pPos += raw->format->BytesPerPixel;
				tpPos += target->raw->format->BytesPerPixel;
				target->putPixel(ix+x,iy+y,bcol);
			}
		}
*/
}

void Surface::write(ASFont *font, string text, int x, int y, const unsigned short halign, const unsigned short valign) {
	font->write(this,text,x,y,halign,valign);
}

void Surface::operator = (SDL_Surface *s) {
	raw = SDL_DisplayFormat(s);
	halfW = raw->w/2;
	halfH = raw->h/2;
}

void Surface::operator = (Surface *s) {
	this->operator =(s->raw);
}

int Surface::box(Sint16 x, Sint16 y, Sint16 w, Sint16 h, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	return boxRGBA(raw,x,y,x+w-1,y+h-1,r,g,b,a);
}
int Surface::box(Sint16 x, Sint16 y, Sint16 w, Sint16 h, Uint8 r, Uint8 g, Uint8 b) {
	SDL_Rect re = {x,y,w,h};
	return SDL_FillRect(raw, &re, SDL_MapRGBA(format(),r,g,b,255));
}
int Surface::box(Sint16 x, Sint16 y, Sint16 w, Sint16 h, RGBAColor c) {
	return box(x,y,w,h,c.r,c.g,c.b,c.a);
}

int Surface::rectangle(Sint16 x, Sint16 y, Sint16 w, Sint16 h, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	return rectangleRGBA(raw,x,y,x+w-1,y+h-1,r,g,b,a);
}
int Surface::rectangle(Sint16 x, Sint16 y, Sint16 w, Sint16 h, Uint8 r, Uint8 g, Uint8 b) {
	return rectangleColor(raw, x,y,x+w-1,y+h-1, SDL_MapRGBA(format(),r,g,b,255));
}
int Surface::rectangle(Sint16 x, Sint16 y, Sint16 w, Sint16 h, RGBAColor c) {
	return rectangle(x,y,w,h,c.r,c.g,c.b,c.a);
}

int Surface::hline(Sint16 x, Sint16 y, Sint16 w, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	return hlineRGBA(raw,x,x+w-1,y,r,g,b,a);
}
int Surface::hline(Sint16 x, Sint16 y, Sint16 w, RGBAColor c) {
	return hline(x,y,w-1,c.r,c.g,c.b,c.a);
}

void Surface::clearClipRect() {
	SDL_SetClipRect(raw,NULL);
}

void Surface::setClipRect(int x, int y, int w, int h) {
	SDL_Rect rect = {x,y,w,h};
	setClipRect(rect);
}

void Surface::setClipRect(SDL_Rect rect) {
	SDL_SetClipRect(raw,&rect);
}

bool Surface::blit(Surface *destination, SDL_Rect container, const unsigned short halign, const unsigned short valign) {
	switch (halign) {
	case SFontHAlignCenter:
		container.x += container.w/2-halfW;
		break;
	case SFontHAlignRight:
		container.x += container.w-raw->w;
		break;
	}

	switch (valign) {
	case SFontVAlignMiddle:
		container.y += container.h/2-halfH;
		break;
	case SFontVAlignBottom:
		container.y += container.h-raw->h;
		break;
	}

	return blit(destination,container.x,container.y);
}
