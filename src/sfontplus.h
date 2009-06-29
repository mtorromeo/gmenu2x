#ifndef SFONTPLUS_H
#define SFONTPLUS_H

#include <SDL.h>
#include <string>
#include <vector>

#define SFONTPLUS_CHARSET "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~¡¿ÀÁÈÉÌÍÒÓÙÚÝÄËÏÖÜŸÂÊÎÔÛÅÃÕÑÆÇČĎĚĽĹŇÔŘŔŠŤŮŽàáèéìíòóùúýäëïöüÿâêîôûåãõñæçčďěľĺňôřŕšťžůðßÐÞþАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюяØøąćęłńśżźĄĆĘŁŃŚŻŹ"
#ifdef _WIN32
    typedef unsigned int uint;
#endif
using std::vector;
using std::string;

const unsigned short SFontHAlignLeft   = 0;
const unsigned short SFontHAlignRight  = 1;
const unsigned short SFontHAlignCenter = 2;
const unsigned short SFontVAlignTop    = 0;
const unsigned short SFontVAlignBottom = 1;
const unsigned short SFontVAlignMiddle = 2;

#ifdef TARGET_PANDORA
	#define FONTSIZE 12
#else
	#define FONTSIZE 9
#endif

class Surface;

class SFontPlus {
private:

	vector<uint> charpos;
	string characters;
	uint height, lineHeight, halfHeight, halfLineHeight;
	bool ttf;
	
	void postInit();

public:
	Surface *surface;
	SFontPlus();
	SFontPlus(SDL_Surface *font);
	SFontPlus(string font, bool ttf = false, SDL_Color textColor = (SDL_Color){255,255,255}, SDL_Color outlineColor = (SDL_Color){5,5,5});
	~SFontPlus();

	bool utf8Code(unsigned char c);

	void initTTF(string fontfile, Uint32 flags = SDL_HWSURFACE|SDL_SRCALPHA, SDL_Color textColor = (SDL_Color){255,255,255}, SDL_Color outlineColor = (SDL_Color){5,5,5}, string characters = SFONTPLUS_CHARSET);
	void initFont(SDL_Surface *font, string characters = SFONTPLUS_CHARSET);
	void initFont(string font, string characters = SFONTPLUS_CHARSET);
	void freeFont();
	
	bool isTTF();

	void write(SDL_Surface *s, string text, int x, int y);
	void write(SDL_Surface* surface, const string& text, int x, int y, const unsigned short halign, const unsigned short valign = 0);
	void write(SDL_Surface* surface, vector<string> *text, int x, int y, const unsigned short halign=0, const unsigned short valign = 0);
	void write(Surface* surface, const string& text, int x, int y, const unsigned short halign=0, const unsigned short valign = 0);

	uint getLineWidth(const string& text);
	uint getTextWidth(const string& text);
	uint getTextWidth(vector<string> *text);
	
	uint getHeight();
	uint getHalfHeight();
	uint getLineHeight();
	uint getHalfLineHeight();
};

#endif /* SFONTPLUS_H */
