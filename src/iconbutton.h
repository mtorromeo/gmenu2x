#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <string>
#include "button.h"

using std::string;

class GMenu2X;

class IconButton : public Button {
protected:
	string icon, label;
	int labelPosition, labelMargin;
	unsigned short labelHAlign, labelVAlign;
	void recalcSize();
	SDL_Rect iconRect, labelRect;

public:
	static const int DISP_RIGHT = 0;
	static const int DISP_LEFT = 1;
	static const int DISP_TOP = 2;
	static const int DISP_BOTTOM = 3;

	IconButton(GMenu2X *gmenu2x, string icon, string label="");
	virtual ~IconButton() {};

	virtual void paint();
	virtual bool paintHover();

	void setPosition(int x, int y);

	string getLabel();
	void setLabel(string label);
	void setLabelPosition(int pos, int margin);

	string getIcon();
	void setIcon(string icon);

	void setAction(ButtonAction action);
};

#endif
