#include "asfont.h"
#include "surface.h"

ASFont::ASFont(SDL_Surface* surface) {
	font = SFont_InitFont(surface);
	halfHeight = getHeight()/2;
}

ASFont::ASFont(Surface* surface) {
	font = SFont_InitFont(surface->raw);
	halfHeight = getHeight()/2;
}

ASFont::~ASFont() {
	SFont_FreeFont(font);
}

void ASFont::write(SDL_Surface* surface, const char* text, int x, int y) {
	SFont_Write(surface, font, x, y, text);
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

	write(surface, text.c_str(), x, y);
}

void ASFont::write(Surface* surface, const std::string& text, int x, int y, const unsigned short halign, const unsigned short valign) {
	write(surface->raw, text, x, y, halign, valign);
}

int ASFont::getHeight() {
	return SFont_TextHeight(font);
}

int ASFont::getHalfHeight() {
	return halfHeight;
}

int ASFont::getTextWidth(const char* text) {
	return SFont_TextWidth(font, text);
}

int ASFont::getTextWidth(const std::string& text) {
	return getTextWidth(text.c_str());
}

