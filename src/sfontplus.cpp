#include "sfontplus.h"
#include "surface.h"
#include "utilities.h"

#include <cassert>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

using namespace std;

SFontPlus::SFontPlus() {
	surface = NULL;
	ttf = false;
}

SFontPlus::SFontPlus(SDL_Surface* font) {
	surface = NULL;
	ttf = false;
	initFont(font);
}

SFontPlus::SFontPlus(string font, bool ttf, SDL_Color textColor, SDL_Color outlineColor) {
	surface = NULL;
	this->ttf = false;
	if (ttf)
		initTTF(font, SDL_HWSURFACE|SDL_SRCALPHA, textColor, outlineColor);
	else
		initFont(font);
}

SFontPlus::~SFontPlus() {
	freeFont();
}

bool SFontPlus::utf8Code(unsigned char c) {
	return (c>=194 && c<=198) || c==208 || c==209;
}

void SFontPlus::initTTF(string fontfile, Uint32 flags,  SDL_Color textColor, SDL_Color outlineColor, string characters) {
	if (!TTF_WasInit()) TTF_Init();
	TTF_Font *font = TTF_OpenFont(fontfile.c_str(), FONTSIZE);
	if (font != NULL) {
		ttf = true;
		freeFont();
		this->characters = characters;
		
		int w,h;
		if (TTF_SizeUTF8(font, characters.c_str(), &w,&h) == 0) {
			lineHeight = h;
			
			surface = new Surface(w+2*characters.length(), h+2, flags);
			Uint32 colorkey = SDL_MapRGB(surface->format(), 0, 255, 255);
			SDL_SetColorKey(surface->raw, SDL_SRCCOLORKEY, colorkey);
			SDL_FillRect(surface->raw, NULL, colorkey);
			
			SDL_Rect dstRect;
			int charX = 0, xOffset = 0;
			const char *c = NULL;
			for (uint i=0; i<characters.length(); i++) {
				if (utf8Code(characters[i])) continue;
				
				charpos.push_back(charX);
				charpos.push_back(charX+2);
			
				if (i>0 && utf8Code(characters[i-1]))
					c = characters.substr(i-1,2).c_str();
				else
					c = characters.substr(i,1).c_str();
					
				int charWidth;
				TTF_SizeUTF8(font, c, &charWidth,NULL);
				SDL_Surface *tmpSurface = TTF_RenderUTF8_Solid(font, c, outlineColor);
				if (tmpSurface != NULL) {
					SDL_SetAlpha(tmpSurface, SDL_RLEACCEL, 128);
				
					for (xOffset=0; xOffset<=2; xOffset++) {
						for (dstRect.y=0; dstRect.y<=2; dstRect.y++) {
							if (!(xOffset==1 && dstRect.y==1)) {
								dstRect.x = xOffset+charX;
								SDL_BlitSurface(tmpSurface, NULL, surface->raw, &dstRect);
							}
						}
					}
					
					dstRect.x = charX+1;
					dstRect.y = 1;
					SDL_Surface *tmpSurface2 = TTF_RenderUTF8_Blended(font, c, textColor);
					if (tmpSurface2 != NULL) {
						SDL_BlitSurface(tmpSurface2, NULL, surface->raw, &dstRect);
					}
					
				}
				
				charX += charWidth+2;
			}
		}
		
		TTF_CloseFont(font);
	}
	
	postInit();
}

void SFontPlus::initFont(string font, string characters) {
	SDL_Surface *buf = IMG_Load(font.c_str());
	if (!buf) {
		//assume ttf file
		initTTF(font);
	} else {
		initFont( SDL_DisplayFormatAlpha(buf), characters );
		SDL_FreeSurface(buf);
	}
}

void SFontPlus::initFont(SDL_Surface *font, string characters) {
	freeFont();
	this->characters = characters;
	if (font==NULL) return;

	surface = new Surface(font);
	Uint32 pink = SDL_MapRGB(surface->format(), 255,0,255);

#ifdef _DEBUG
	bool utf8 = false;
	for (uint x=0; x<characters.length(); x++) {
		if (!utf8) utf8 = (unsigned char)characters[x]>128;
		if (utf8) printf("%d\n", (unsigned char)characters[x]);
	}
#endif

	uint c = 0;

	surface->lock();
	for (uint x=0; x<(uint)surface->raw->w && c<characters.length(); x++) {
		if (surface->pixel(x,0) == pink) {
			uint startx = x;
			charpos.push_back(x);

			x++;
			while (x<(uint)surface->raw->w && surface->pixel(x,0) == pink) x++;
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
	surface->unlock();
	Uint32 colKey = surface->pixel(0,surface->raw->h-1);
	SDL_SetColorKey(surface->raw, SDL_SRCCOLORKEY, colKey);

	string::size_type pos = characters.find("0")*2;
	SDL_Rect srcrect = {charpos[pos], 1, charpos[pos+2] - charpos[pos], surface->raw->h-1};
	uint y = srcrect.h+1;
	bool nonKeyFound = false;
	while (y-->0 && !nonKeyFound) {
		uint x = srcrect.w+1;
		while (x-->0 && !nonKeyFound)
			nonKeyFound = surface->pixel(x+srcrect.x,y+srcrect.y) != colKey;
	}
	lineHeight = y+1;
	
	postInit();
}

void SFontPlus::postInit() {
	halfHeight = getHeight()/2;
	halfLineHeight = getLineHeight()/2;
}

void SFontPlus::freeFont() {
	if (surface!=NULL) {
		free(surface);
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
	srcrect.h = dstrect.h = surface->raw->h-1;

	for(uint i=0; i<text.length() && x<surface->raw->w; i++) {
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

		SDL_BlitSurface(surface->raw, &srcrect, s, &dstrect);

		x += charpos[pos+2] - charpos[pos+1];
	}
}

void SFontPlus::write(SDL_Surface* surface, const string& text, int x, int y, const unsigned short halign, const unsigned short valign) {
	switch (halign) {
	case SFontHAlignCenter:
		x -= getTextWidth(text)/2;
		break;
	case SFontHAlignRight:
		x -= getTextWidth(text);
		break;
	}

	switch (valign) {
	case SFontVAlignMiddle:
		y -= getHalfHeight();
		break;
	case SFontVAlignBottom:
		y -= getHeight();
		break;
	}

	write(surface, text, x, y);
}

void SFontPlus::write(SDL_Surface* surface, vector<string> *text, int x, int y, const unsigned short halign, const unsigned short valign) {
	switch (valign) {
	case SFontVAlignMiddle:
		y -= getHalfHeight()*text->size();
		break;
	case SFontVAlignBottom:
		y -= getHeight()*text->size();
		break;
	}

	for (uint i=0; i<text->size(); i++) {
		int ix = x;
		switch (halign) {
		case SFontHAlignCenter:
			ix -= getTextWidth(text->at(i))/2;
			break;
		case SFontHAlignRight:
			ix -= getTextWidth(text->at(i));
			break;
		}

		write(surface, text->at(i), x, y+getHeight()*i);
	}
}

void SFontPlus::write(Surface* surface, const string& text, int x, int y, const unsigned short halign, const unsigned short valign) {
	if (text.find("\n",0)!=string::npos) {
		vector<string> textArr;
		split(textArr,text,"\n");
		write(surface->raw, &textArr, x, y, halign, valign);
	} else
		write(surface->raw, text, x, y, halign, valign);
}

uint SFontPlus::getLineWidth(const string& text) {
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
uint SFontPlus::getTextWidth(const string& text) {
	if (text.find("\n",0)!=string::npos) {
		vector<string> textArr;
		split(textArr,text,"\n");
		return getTextWidth(&textArr);
	} else
		return getLineWidth(text);
}
uint SFontPlus::getTextWidth(vector<string> *text) {
	int w = 0;
	for (uint i=0; i<text->size(); i++)
		w = max( getLineWidth(text->at(i)), w );
	return w;
}

uint SFontPlus::getHeight() {
	return surface->raw->h - 1;
}
uint SFontPlus::getHalfHeight() {
	return halfHeight;
}

uint SFontPlus::getLineHeight() {
	return lineHeight;
}
uint SFontPlus::getHalfLineHeight() {
	return halfLineHeight;
}
