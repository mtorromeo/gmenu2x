#include "listview.h"

ListView::ListView(GMenu2X *gmenu2x) {
	this->gmenu2x = gmenu2x;
	firstDisplayItem = selectedItem = 0;
	itemsPerPage = 11;
}

ListView::~ ListView() {}

ListViewItem * ListView::add(ListViewItem *item) {
	items.push_back(item);
	return item;
}

ListViewItem * ListView::add(string text) {
	ListViewItem *item = new ListViewItem(this,text);
	return add(item);
}

void ListView::del(ListViewItem * item) {
	vector<ListViewItem*>::iterator p = find(items.begin(), items.end(), item);
	if (p != items.end())
		items.erase(p);
}

void ListView::del(int itemIndex) {
	items.erase(items.begin()+itemIndex);
}

void ListView::clear() {
	items.clear();
}

ListViewItem * ListView::operator [](int index) {
	return items[index];
}

void ListView::setPosition(int x, int y) {
	rect.x = x;
	rect.y = y;
}

void ListView::setSize(int w, int h) {
	rect.w = w;
	rect.h = h;
}

void ListView::paint() {
	gmenu2x->s->setClipRect(rect);

	//Selection
	int iY = selectedItem-firstDisplayItem;
	iY = rect.y+(iY*16);
	if (selectedItem<(int)items.size())
		gmenu2x->s->box(1, iY, 309, 14, gmenu2x->selectionColor);

	//Items
	iY = rect.y;
	for (int i=firstDisplayItem; i<(int)items.size() && i<firstDisplayItem+itemsPerPage; i++) {
		items[i]->setPosition(4,iY);
		items[i]->paint();
		iY += items[i]->getHeight();
	}

	gmenu2x->drawScrollBar(itemsPerPage, items.size(), firstDisplayItem, 42,175);

	gmenu2x->s->clearClipRect();
}

void ListView::handleInput() {
	for (int i=firstDisplayItem; i<(int)items.size() && i<firstDisplayItem+itemsPerPage; i++)
		items[i]->handleTS();
}

int ListView::getWidth() {
	return rect.w;
}
