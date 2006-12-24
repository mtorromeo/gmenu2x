//Advanced SFont by Massimiliano Torromeo (cpp wrapper around SFont)

#ifndef ASFONT_H
#define ASFONT_H

#include <string>
#include <vector>
#include <SDL.h>
#include "sfontplus.h"

using std::string;
using std::vector;

const unsigned short SFontHAlignLeft   = 0;
const unsigned short SFontHAlignRight  = 1;
const unsigned short SFontHAlignCenter = 2;
const unsigned short SFontVAlignTop    = 0;
const unsigned short SFontVAlignBottom = 1;
const unsigned short SFontVAlignMiddle = 2;

class Surface;

class ASFont {
public:
	ASFont(SDL_Surface* font);
	ASFont(Surface* font);
	ASFont(string font);
	~ASFont();

	int getHeight();
	int getHalfHeight();
	int getTextWidth(const char* text);
	int getTextWidth(const string& text);
	int getTextWidth(vector<string> *text);
	void write(SDL_Surface* surface, const char* text, int x, int y);
	void write(SDL_Surface* surface, const std::string& text, int x, int y, const unsigned short halign = 0, const unsigned short valign = 0);
	void write(SDL_Surface* surface, vector<string> *text, int x, int y, const unsigned short halign = 0, const unsigned short valign = 0);
	void write(Surface* surface, const std::string& text, int x, int y, const unsigned short halign = 0, const unsigned short valign = 0);

private:
	SFontPlus font;
	int halfHeight;
};

#endif /* ASFONT_H */
