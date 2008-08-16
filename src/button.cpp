#include "button.h"
#include "gmenu2x.h"

using namespace std;
using namespace fastdelegate;

Button::Button(GMenu2X * gmenu2x, bool doubleClick) {
	this->gmenu2x = gmenu2x;
	this->doubleClick = doubleClick;
	lastTick = 0;
	action = MakeDelegate(this, &Button::voidAction);
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

void Button::paint() {
	if (gmenu2x->ts.inRect(rect))
		if (!paintHover()) return;
}

bool Button::paintHover() {
	return false;
}

bool Button::isPressed() {
	return gmenu2x->ts.pressed() && gmenu2x->ts.inRect(rect);
}

bool Button::isReleased() {
	return gmenu2x->ts.released() && gmenu2x->ts.inRect(rect);
}

bool Button::handleTS() {
	if (isReleased()) {
		if (doubleClick) {
			int tickNow = SDL_GetTicks();
			if (tickNow - lastTick < 400)
				exec();
			lastTick = tickNow;
		} else {
			exec();
		}
		return true;
	}
	return false;
}

void Button::exec() {
	gmenu2x->ts.setHandled();
	action();
}

SDL_Rect Button::getRect() {
	return rect;
}

void Button::setSize(int w, int h) {
	rect.w = w;
	rect.h = h;
}

void Button::setPosition(int x, int y) {
	rect.x = x;
	rect.y = y;
}

void Button::setAction(ButtonAction action) {
	this->action = action;
}
