#ifndef FONTHELPER_H
#define FONTHELPER_H

#include "surface.h"

#include <string>
#include <vector>
#include <SDL_ttf.h>

#ifdef _WIN32
    typedef unsigned int uint;
#endif
using std::vector;
using std::string;

enum FHHAlign {
	HAlignLeft,
	HAlignRight,
	HAlignCenter
};

enum FHVAlign {
	VAlignTop,
	VAlignBottom,
	VAlignMiddle
};

class Surface;

class FontHelper {
private:

	int height, halfHeight;
	TTF_Font *font, *fontOutline;
	RGBAColor textColor, outlineColor;

public:
	FontHelper(const string &font, int size, RGBAColor textColor = (RGBAColor){255,255,255}, RGBAColor outlineColor = (RGBAColor){5,5,5});
	~FontHelper();

	bool utf8Code(unsigned char c);

	void write(SDL_Surface *s, const string &text, int x, int y);
	void write(SDL_Surface* surface, const string& text, int x, int y, const unsigned short halign, const unsigned short valign = 0);
	void write(SDL_Surface* surface, vector<string> *text, int x, int y, const unsigned short halign=0, const unsigned short valign = 0);
	void write(Surface* surface, const string& text, int x, int y, const unsigned short halign=0, const unsigned short valign = 0);

	uint getLineWidth(const string& text);
	uint getTextWidth(const string& text);
	uint getTextWidth(vector<string> *text);
	
	uint getHeight() { return height; };
	uint getHalfHeight() { return halfHeight; };
	
	FontHelper *setColor(RGBAColor color);
	FontHelper *setOutlineColor(RGBAColor color);
};

#endif /* FONTHELPER_H */
