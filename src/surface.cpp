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
#include "surface.h"

Surface::Surface() {
	raw = NULL;
}

Surface::Surface(string img) {
	raw = NULL;
	load(img);
}

Surface::Surface(int w, int h) {
	SDL_JoystickOpen(0);
	//raw = SDL_SetVideoMode(w, h, 16, SDL_SWSURFACE);
	raw = SDL_SetVideoMode(w, h, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
	SDL_ShowCursor(0);
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

bool Surface::blit(SDL_Surface *destination, int x, int y) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	return SDL_BlitSurface(raw, NULL, destination, &dest);
}

bool Surface::blit(Surface *destination, int x, int y) {
	return blit(destination->raw,x,y);
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

void Surface::operator = (Surface *s) {
	raw = s->raw;
	raw->refcount++;
}
