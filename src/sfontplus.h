#ifndef SFONTPLUS_H
#define SFONTPLUS_H

#include <SDL.h>
#include <string>
#include <vector>
#include <SDL_ttf.h>

#ifdef _WIN32
    typedef unsigned int uint;
#endif
using std::vector;
using std::string;

enum SFontHAlign {
	SFontHAlignLeft,
	SFontHAlignRight,
	SFontHAlignCenter
};

enum SFontVAlign {
	SFontVAlignTop,
	SFontVAlignBottom,
	SFontVAlignMiddle
};

#ifdef TARGET_PANDORA
	#define FONTSIZE 12
#else
	#define FONTSIZE 9
#endif

class Surface;

class SFontPlus {
private:

	int height, halfHeight;
	TTF_Font *font, *fontOutline;
	SDL_Color textColor, outlineColor;

public:
	SFontPlus(const string &font, SDL_Color textColor = (SDL_Color){255,255,255}, SDL_Color outlineColor = (SDL_Color){5,5,5});
	~SFontPlus();

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
};

#endif /* SFONTPLUS_H */
