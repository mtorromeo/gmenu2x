#include "iconbutton.h"

using namespace std;
using namespace fastdelegate;

IconButton::IconButton(GMenu2X *gmenu2x, string icon) : Button(gmenu2x) {
	this->gmenu2x = gmenu2x;
	this->icon = icon;
}

void IconButton::paint() {
	gmenu2x->sc[icon]->blit(gmenu2x->s,rect);
}

bool IconButton::paintHover() {
	return true;
}

string IconButton::getIcon() {
	return icon;
}

void IconButton::setIcon(string icon) {
	this->icon = icon;
}

void IconButton::setAction(ButtonAction action) {
	this->action = action;
}
