#include "iconbutton.h"
#include "gmenu2x.h"

using namespace std;
using namespace fastdelegate;

IconButton::IconButton(GMenu2X *gmenu2x, string icon, string label) : Button(gmenu2x) {
	this->gmenu2x = gmenu2x;
	this->icon = icon;
	labelPosition = IconButton::DISP_RIGHT;
	labelMargin = 2;
	this->setLabel(label);
}

void IconButton::setPosition(int x, int y) {
	if (rect.x != x && rect.y != y) {
		Button::setPosition(x,y);
		recalcSize();
	}
}

void IconButton::paint() {
	uint margin = labelMargin;
	if (gmenu2x->sc[icon] == NULL || label == "")
		margin = 0;
	if (gmenu2x->sc[icon] != NULL)
		gmenu2x->sc[icon]->blit(gmenu2x->s,iconRect);
	if (label != "")
		gmenu2x->s->write(gmenu2x->font, label, labelRect.x, labelRect.y, labelHAlign, labelVAlign);
}

bool IconButton::paintHover() {
	return true;
}

void IconButton::recalcSize() {
	uint h = 0, w = 0;
	uint margin = labelMargin;

	if (gmenu2x->sc[icon] == NULL || label == "")
		margin = 0;

	if (gmenu2x->sc[icon] != NULL) {
		w += gmenu2x->sc[icon]->raw->w;
		h += gmenu2x->sc[icon]->raw->h;
		iconRect.w = w;
		iconRect.h = h;
		iconRect.x = rect.x;
		iconRect.y = rect.y;
	} else {
		iconRect.x = 0;
		iconRect.y = 0;
		iconRect.w = 0;
		iconRect.h = 0;
	}

	if (label != "") {
		labelRect.w = gmenu2x->font->getTextWidth(label);
		labelRect.h = gmenu2x->font->getHeight();
		if (labelPosition == IconButton::DISP_LEFT || labelPosition == IconButton::DISP_RIGHT) {
			w += margin + labelRect.w;
			//if (labelRect.h > h) h = labelRect.h;
			labelHAlign = SFontHAlignLeft;
			labelVAlign = SFontVAlignMiddle;
		} else {
			h += margin + labelRect.h;
			//if (labelRect.w > w) w = labelRect.w;
			labelHAlign = SFontHAlignCenter;
			labelVAlign = SFontVAlignTop;
		}

		switch (labelPosition) {
			case IconButton::DISP_BOTTOM:
				labelRect.x = iconRect.x + iconRect.w/2;
				labelRect.y = iconRect.y + iconRect.h + margin;
			break;
			case IconButton::DISP_TOP:
				labelRect.x = iconRect.x + iconRect.w/2;
				labelRect.y = rect.y;
				iconRect.y += labelRect.h + margin;
			break;
			case IconButton::DISP_LEFT:
				labelRect.x = rect.x;
				labelRect.y = rect.y+h/2;
				iconRect.x += labelRect.w + margin;
			break;
			default:
				labelRect.x = iconRect.x + iconRect.w + margin;
				labelRect.y = rect.y+h/2;
			break;
		}
	}
	setSize(w, h);
}

string IconButton::getLabel() {
	return label;
}

void IconButton::setLabel(string label) {
	this->label = label;
}

void IconButton::setLabelPosition(int pos, int margin) {
	labelPosition = pos;
	labelMargin = margin;
	recalcSize();
}

string IconButton::getIcon() {
	return icon;
}

void IconButton::setIcon(string icon) {
	this->icon = icon;
	recalcSize();
}

void IconButton::setAction(ButtonAction action) {
	this->action = action;
}
