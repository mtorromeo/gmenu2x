#include "sfontplus.h"

#include <cassert>
#include <SDL_image.h>
#include <iostream>

using namespace std;

Uint32 SFontPlus::getPixel(Sint32 x, Sint32 y) {
	assert(x>=0);
	assert(x<surface->w);

	Uint32 Bpp = surface->format->BytesPerPixel;

	// Get the pixel
	switch(Bpp) {
		case 1:
			return *((Uint8 *)surface->pixels + y * surface->pitch + x);
		break;
		case 2:
			return *((Uint16 *)surface->pixels + y * surface->pitch/2 + x);
		break;
		case 3: { // Format/endian independent
			Uint8 *bits = ((Uint8 *)surface->pixels)+y*surface->pitch+x*Bpp;
			Uint8 r, g, b;
			r = *((bits)+surface->format->Rshift/8);
			g = *((bits)+surface->format->Gshift/8);
			b = *((bits)+surface->format->Bshift/8);
			return SDL_MapRGB(surface->format, r, g, b);
		}
		break;
		case 4:
			return *((Uint32 *)surface->pixels + y * surface->pitch/4 + x);
		break;
	}

	return 0;
}

SFontPlus::SFontPlus() {
	surface = NULL;
}

SFontPlus::SFontPlus(SDL_Surface* font) {
	surface = NULL;
	initFont(font);
}

SFontPlus::SFontPlus(string font) {
	surface = NULL;
	initFont(font);
}

SFontPlus::~SFontPlus() {
	freeFont();
}

bool SFontPlus::utf8Code(unsigned char c) {
	return c==194 || c==195 || c==208 || c==209;
}

void SFontPlus::initFont(string font, string characters) {
	SDL_Surface *buf = IMG_Load(font.c_str());
	if (buf!=NULL) {
		initFont( SDL_DisplayFormatAlpha(buf), characters );
		SDL_FreeSurface(buf);
	}
}

void SFontPlus::initFont(SDL_Surface *font, string characters) {
	freeFont();
	this->characters = characters;
	if (font==NULL) return;

	surface = font;
	Uint32 pink = SDL_MapRGB(surface->format, 255,0,255);

#ifndef _DEBUG
	bool utf8 = false;
	for (uint x=0; x<characters.length(); x++) {
		if (!utf8) utf8 = (unsigned char)characters[x]>128;
		if (utf8) printf("%d\n", (unsigned char)characters[x]);
	}
#endif

	uint c = 0;

	SDL_LockSurface(surface);
	for (uint x=0; x<(uint)surface->w && c<characters.length(); x++) {
		if (getPixel(x,0) == pink) {
			uint startx = x;
			charpos.push_back(x);

			x++;
			while (x<(uint)surface->w && getPixel(x,0) == pink) x++;
			charpos.push_back(x);

			//utf8 characters
			if (c>0 && utf8Code(characters[c-1])) {
				charpos.push_back(startx);
				charpos.push_back(x);
				c++;
			}

			c++;
		}
	}
	SDL_UnlockSurface(surface);
	SDL_SetColorKey(surface, SDL_SRCCOLORKEY, getPixel(0,surface->h-1));
}

void SFontPlus::freeFont() {
	if (surface!=NULL) {
		SDL_FreeSurface(surface);
		surface = NULL;
	}
}

void SFontPlus::write(SDL_Surface *s, string text, int x, int y) {
	if (text.empty()) return;

	string::size_type pos;
	SDL_Rect srcrect, dstrect;

	// these values won't change in the loop
	srcrect.y = 1;
	dstrect.y = y;
	srcrect.h = dstrect.h = surface->h-1;

	for(uint i=0; i<text.length() && x<surface->w; i++) {
		//Utf8 characters
		if (utf8Code(text[i]) && i+1<text.length()) {
			pos = characters.find(text.substr(i,2));
			i++;
		} else
			pos = characters.find(text[i]);
		if (pos == string::npos) {
			x += charpos[2]-charpos[1];
			continue;
		}

		pos *= 2;

		srcrect.x = charpos[pos];
		srcrect.w = charpos[pos+2] - charpos[pos];
		dstrect.x = x - charpos[pos+1] + charpos[pos];

		SDL_BlitSurface(surface, &srcrect, s, &dstrect);

		x += charpos[pos+2] - charpos[pos+1];
	}
}

uint SFontPlus::getTextWidth(string text) {
	string::size_type pos;
	int width = 0;

	for(uint x=0; x<text.length(); x++) {
		//Utf8 characters
		if (utf8Code(text[x]) && x+1<text.length()) {
			pos = characters.find(text.substr(x,2));
			x++;
		} else
			pos = characters.find(text[x]);
		if (pos == string::npos) {
			width += charpos[2]-charpos[1];
			continue;
		}

		pos *= 2;
		width += charpos[pos+2] - charpos[pos+1];
	}

	return width;
}

uint SFontPlus::getHeight() {
	return surface->h - 1;
}
