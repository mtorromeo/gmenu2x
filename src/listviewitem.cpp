#include "listview.h"
#include "listviewitem.h"

ListViewItem::ListViewItem(ListView * parent, string text) {
	this->parent = parent;
	rect.h = 16;
	rect.w = parent->getWidth();
}

ListViewItem::~ ListViewItem() {}

void ListViewItem::setPosition(int x, int y) {
	rect.x = x;
	rect.y = y;
}

void ListViewItem::paint() {
	parent->gmenu2x->s->write(parent->gmenu2x->font, text, rect.x, rect.y, SFontHAlignLeft, SFontVAlignMiddle);
}

int ListViewItem::getHeight() {
	return rect.h;
}

void ListViewItem::handleTS() {
	if (parent->gmenu2x->ts.inRect(rect))
		onClick();
}

void ListViewItem::onClick() {}
