#include "asfont.h"
#include "surface.h"
#include "utilities.h"

#include <iostream>

using namespace std;

ASFont::ASFont(SDL_Surface* font) {
	this->font.initFont(font);
	halfHeight = getHeight()/2;
	halfLineHeight = getLineHeight()/2;
}

ASFont::ASFont(Surface* font) {
	this->font.initFont(font->raw);
	halfHeight = getHeight()/2;
	halfLineHeight = getLineHeight()/2;
}

ASFont::ASFont(string font) {
	this->font.initFont(font);
	halfHeight = getHeight()/2;
	halfLineHeight = getLineHeight()/2;
}

ASFont::~ASFont() {
	font.freeFont();
}

bool ASFont::utf8Code(unsigned char c) {
	return font.utf8Code(c);
}

void ASFont::write(SDL_Surface* surface, const char* text, int x, int y) {
	font.write(surface, text, x, y);
}

void ASFont::write(SDL_Surface* surface, const std::string& text, int x, int y, const unsigned short halign, const unsigned short valign) {
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

	font.write(surface, text, x, y);
}
void ASFont::write(SDL_Surface* surface, vector<string> *text, int x, int y, const unsigned short halign, const unsigned short valign) {
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

		font.write(surface, text->at(i), x, y+getHeight()*i);
	}
}

void ASFont::write(Surface* surface, const std::string& text, int x, int y, const unsigned short halign, const unsigned short valign) {
	if (text.find("\n",0)!=string::npos) {
		vector<string> textArr;
		split(textArr,text,"\n");
		write(surface->raw, &textArr, x, y, halign, valign);
	} else
		write(surface->raw, text, x, y, halign, valign);
}

int ASFont::getHeight() {
	return font.getHeight();
}
int ASFont::getHalfHeight() {
	return halfHeight;
}

int ASFont::getLineHeight() {
	return font.getLineHeight();
}
int ASFont::getHalfLineHeight() {
	return halfLineHeight;
}

int ASFont::getTextWidth(const char* text) {
	return font.getTextWidth(text);
}
int ASFont::getTextWidth(const std::string& text) {
	if (text.find("\n",0)!=string::npos) {
		vector<string> textArr;
		split(textArr,text,"\n");
		return getTextWidth(&textArr);
	} else
		return getTextWidth(text.c_str());
}
int ASFont::getTextWidth(vector<string> *text) {
	int w = 0;
	for (uint i=0; i<text->size(); i++)
		w = max( getTextWidth(text->at(i).c_str()), w );
	return w;
}
