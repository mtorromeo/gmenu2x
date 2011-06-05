#include <string>
#include <iostream>

#include "browsedialog.h"

#include "FastDelegate.h"
#include "filelister.h"
#include "gmenu2x.h"

using namespace fastdelegate;
using namespace std;

BrowseDialog::BrowseDialog(GMenu2X *gmenu2x, const string &title, const string &subtitle)
	: Dialog(gmenu2x), title(title), subtitle(subtitle), ts_pressed(false), buttonBox(gmenu2x) {
	IconButton *btn;

	btn = new IconButton(gmenu2x, "skin:imgs/buttons/x.png", gmenu2x->tr["Up one folder"]);
	btn->setAction(MakeDelegate(this, &BrowseDialog::directoryUp));
	buttonBox.add(btn);

	btn = new IconButton(gmenu2x, "skin:imgs/buttons/b.png", gmenu2x->tr["Enter folder"]);
	btn->setAction(MakeDelegate(this, &BrowseDialog::directoryEnter));
	buttonBox.add(btn);

	btn = new IconButton(gmenu2x, "skin:imgs/buttons/start.png", gmenu2x->tr["Confirm"]);
	btn->setAction(MakeDelegate(this, &BrowseDialog::confirm));
	buttonBox.add(btn);

	iconGoUp = gmenu2x->sc.skinRes("imgs/go-up.png");
	iconFolder = gmenu2x->sc.skinRes("imgs/folder.png");
	iconFile = gmenu2x->sc.skinRes("imgs/file.png");
}

BrowseDialog::~BrowseDialog() {}

bool BrowseDialog::exec() {
	if (!fl)
		return false;

	string path = fl->getPath();
	if (path.empty() || !fileExists(path) || path.compare(0,CARD_ROOT_LEN,CARD_ROOT)!=0)
		setPath(CARD_ROOT);

	fl->browse();

	rowHeight = gmenu2x->font->getHeight()+2;
	clipRect = (SDL_Rect){0, gmenu2x->skinConfInt["topBarHeight"]+2, gmenu2x->resX-9, gmenu2x->resY - gmenu2x->skinConfInt["topBarHeight"] - 25};
	touchRect = (SDL_Rect){2, gmenu2x->skinConfInt["topBarHeight"]+4, gmenu2x->resX-12, clipRect.h};
	numRows = (clipRect.h + 2) / rowHeight;

	selected = 0;
	close = false;
	while (!close) {
		if (gmenu2x->f200) gmenu2x->ts.poll();

		paint();

		handleInput();
	}

	return result;
}

BrowseDialog::Action BrowseDialog::getAction() {
	BrowseDialog::Action action = BrowseDialog::ACT_NONE;

	if (gmenu2x->input[MENU])
		action = BrowseDialog::ACT_CLOSE;
	else if (gmenu2x->input[UP])
		action = BrowseDialog::ACT_UP;
	else if (gmenu2x->input[PAGEUP])
		action = BrowseDialog::ACT_SCROLLUP;
	else if (gmenu2x->input[DOWN])
		action = BrowseDialog::ACT_DOWN;
	else if (gmenu2x->input[PAGEDOWN])
		action = BrowseDialog::ACT_SCROLLDOWN;
	else if (gmenu2x->input[CANCEL] || gmenu2x->input[LEFT])
		action = BrowseDialog::ACT_GOUP;
	else if (gmenu2x->input[CONFIRM])
		action = BrowseDialog::ACT_SELECT;
	else if (gmenu2x->input[SETTINGS])
		action = BrowseDialog::ACT_CONFIRM;

	return action;
}

void BrowseDialog::handleInput() {
	BrowseDialog::Action action;

	gmenu2x->input.update();

	if (ts_pressed && !gmenu2x->ts.pressed()) {
		action = BrowseDialog::ACT_SELECT;
		ts_pressed = false;
	} else {
		action = getAction();
	}

	if (gmenu2x->f200 && gmenu2x->ts.pressed() && !gmenu2x->ts.inRect(touchRect)) ts_pressed = false;

	if (action == BrowseDialog::ACT_SELECT && (*fl)[selected] == "..")
		action = BrowseDialog::ACT_GOUP;
	switch (action) {
	case BrowseDialog::ACT_CLOSE:
		close = true;
		result = false;
		break;
	case BrowseDialog::ACT_UP:
		if (selected == 0)
			selected = fl->size() - 1;
		else
			selected -= 1;
		break;
	case BrowseDialog::ACT_SCROLLUP:
		if (selected <= numRows - 2)
			selected = 0;
		else
			selected -= numRows - 2;
		break;
	case BrowseDialog::ACT_DOWN:
		if (fl->size() - 1 <= selected)
			selected = 0;
		else
			selected += 1;
		break;
	case BrowseDialog::ACT_SCROLLDOWN:
		if (selected+(numRows-2)>=fl->size())
			selected = fl->size()-1;
		else
			selected += numRows-2;
		break;
	case BrowseDialog::ACT_GOUP:
		directoryUp();
		break;
	case BrowseDialog::ACT_SELECT:
		if (fl->isDirectory(selected)) {
			directoryEnter();
			break;
		}
		/* Falltrough */
	case BrowseDialog::ACT_CONFIRM:
		confirm();
		break;
	default:
		break;
	}

	buttonBox.handleTS();
}

void BrowseDialog::directoryUp() {
	string path = fl->getPath();
	string::size_type p = path.rfind("/");

	if (p == path.size() - 1)
		p = path.rfind("/", p - 1);

	if (p == string::npos || p < 4 || path.compare(0, CARD_ROOT_LEN, CARD_ROOT) != 0) {
		close = true;
		result = false;
	} else {
		selected = 0;
		setPath(path.substr(0, p));
	}
}

void BrowseDialog::directoryEnter() {
	string path = fl->getPath();
	if (path[path.size()-1] != '/')
			path += "/";
	setPath(path + fl->at(selected));
	selected = 0;
}

void BrowseDialog::confirm() {
	result = true;
	close = true;
}

void BrowseDialog::paint() {
	unsigned int i, iY;
	unsigned int firstElement=0, lastElement;
	unsigned int offsetY;
	Surface *icon;

	gmenu2x->bg->blit(gmenu2x->s, 0, 0);
	drawTitleIcon("icons/explorer.png", true);
	writeTitle(title);
	writeSubTitle(subtitle);

	buttonBox.paint(5);

	if (selected>firstElement+numRows-1)
		firstElement = selected-numRows+1;
	else if (selected < firstElement)
		firstElement = selected;

	offsetY = gmenu2x->skinConfInt["topBarHeight"] + 2;

	//Selection
	iY = selected-firstElement;
	iY = offsetY + iY*rowHeight;
	gmenu2x->s->box(2, iY, gmenu2x->resX-12, rowHeight-2, gmenu2x->skinConfColors[COLOR_SELECTION_BG]);

	lastElement = firstElement + numRows;
	if (lastElement > fl->size())
		lastElement = fl->size();

	beforeFileList();

	//Files & Directories
	gmenu2x->s->setClipRect(clipRect);
	for (i = firstElement; i < lastElement; i++) {
		if (fl->isDirectory(i)) {
			if ((*fl)[i]=="..")
				icon = iconGoUp;
			else
				icon = iconFolder;
		} else {
			icon = iconFile;
		}
		icon->blit(gmenu2x->s, 5, offsetY);
		gmenu2x->s->write(gmenu2x->font, (*fl)[i], 24, offsetY + 6, HAlignLeft, VAlignMiddle);

		if (gmenu2x->f200 && gmenu2x->ts.pressed() && gmenu2x->ts.inRect(touchRect.x, offsetY + 3, touchRect.w, rowHeight)) {
			ts_pressed = true;
			selected = i;
		}

		offsetY += rowHeight;
	}
	gmenu2x->s->clearClipRect();

	gmenu2x->drawScrollBar(numRows, fl->size(), firstElement, clipRect.y, clipRect.h);
	gmenu2x->s->flip();
}
