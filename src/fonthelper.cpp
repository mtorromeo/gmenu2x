#include "fonthelper.h"
#include "utilities.h"
#include "debug.h"

FontHelper::FontHelper(const string &font, int size, RGBAColor textColor, RGBAColor outlineColor)
	: textColor(textColor),
	  outlineColor(outlineColor) {
	if (!TTF_WasInit()) {
		DEBUG("Initializing font");
		if (TTF_Init() == -1) {
			ERROR("TTF_Init: %s", TTF_GetError());
			exit(2);
		}
	}
	this->font = TTF_OpenFont(font.c_str(), size);
	if (!this->font) {
		ERROR("TTF_OpenFont %s: %s", font.c_str(), TTF_GetError());
		exit(2);
	}
	fontOutline = TTF_OpenFont(font.c_str(), size);
	if (!fontOutline) {
		ERROR("TTF_OpenFont %s: %s", font.c_str(), TTF_GetError());
		exit(2);
	}
	TTF_SetFontHinting(this->font, TTF_HINTING_NORMAL);
	TTF_SetFontHinting(fontOutline, TTF_HINTING_NORMAL);
	TTF_SetFontOutline(fontOutline, 1);
	height = 0;
	// Get maximum line height with a sample text
	TTF_SizeUTF8(fontOutline, "AZ|¹0987654321", NULL, &height);
	halfHeight = height/2;
}

FontHelper::~FontHelper() {
	TTF_CloseFont(font);
	TTF_CloseFont(fontOutline);
}

bool FontHelper::utf8Code(unsigned char c) {
	return (c>=194 && c<=198) || c==208 || c==209;
}

FontHelper *FontHelper::setColor(RGBAColor color) {
	textColor = color;
	return this;
}

FontHelper *FontHelper::setOutlineColor(RGBAColor color) {
	outlineColor = color;
	return this;
}

void FontHelper::write(SDL_Surface *s, const string &text, int x, int y) {
	if (text.empty()) return;

	Surface bg;
	bg.raw = TTF_RenderUTF8_Blended(fontOutline, text.c_str(), rgbatosdl(outlineColor));

	Surface fg;
	fg.raw = TTF_RenderUTF8_Blended(font, text.c_str(), rgbatosdl(textColor));

	// Modify alpha channel of outline and text and merge them in the process
	RGBAColor fgcol, bgcol;
	for (int iy=0; iy<bg.raw->h; iy++)
		for (int ix=0; ix<bg.raw->w; ix++) {
			bgcol = bg.pixelColor(ix, iy);
			if (bgcol.a != 0) {
				bgcol.a = bgcol.a * outlineColor.a / 255;
			}
			if (ix > 0 && ix-1 < fg.raw->w && iy > 0 && iy-1 < fg.raw->h) {
				fgcol = fg.pixelColor(ix-1, iy-1);
				if (fgcol.a > 50) {
					bgcol = fgcol;
					bgcol.a = bgcol.a * textColor.a / 255;
				}
			}
			bg.putPixel(ix, iy, bgcol);
		}

	bg.blit(s, x,y);
}

void FontHelper::write(SDL_Surface* surface, const string& text, int x, int y, const unsigned short halign, const unsigned short valign) {
	switch (halign) {
		case HAlignCenter:
			x -= getTextWidth(text)/2;
		break;
		case HAlignRight:
			x -= getTextWidth(text);
		break;
	}

	switch (valign) {
		case VAlignMiddle:
			y -= getHalfHeight();
		break;
		case VAlignBottom:
			y -= getHeight();
		break;
	}

	write(surface, text, x, y);
}

void FontHelper::write(SDL_Surface* surface, vector<string> *text, int x, int y, const unsigned short halign, const unsigned short valign) {
	switch (valign) {
		case VAlignMiddle:
			y -= getHalfHeight()*text->size();
		break;
		case VAlignBottom:
			y -= getHeight()*text->size();
		break;
	}

	for (uint i=0; i<text->size(); i++) {
		int ix = x;
		switch (halign) {
			case HAlignCenter:
				ix -= getTextWidth(text->at(i))/2;
			break;
			case HAlignRight:
				ix -= getTextWidth(text->at(i));
			break;
		}

		write(surface, text->at(i), x, y+getHeight()*i);
	}
}

void FontHelper::write(Surface* surface, const string& text, int x, int y, const unsigned short halign, const unsigned short valign) {
	if (text.find("\n",0)!=string::npos) {
		vector<string> textArr;
		split(textArr,text,"\n");
		write(surface->raw, &textArr, x, y, halign, valign);
	} else
		write(surface->raw, text, x, y, halign, valign);
}

uint FontHelper::getLineWidth(const string& text) {
	int width = 0;
	TTF_SizeUTF8(fontOutline, text.c_str(), &width, NULL);
	return width;
}
uint FontHelper::getTextWidth(const string& text) {
	if (text.find("\n",0)!=string::npos) {
		vector<string> textArr;
		split(textArr,text,"\n");
		return getTextWidth(&textArr);
	} else
		return getLineWidth(text);
}
uint FontHelper::getTextWidth(vector<string> *text) {
	int w = 0;
	for (uint i=0; i<text->size(); i++)
		w = max( getLineWidth(text->at(i)), w );
	return w;
}
