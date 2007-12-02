#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <string>
#include "button.h"

using std::string;

class GMenu2X;

class IconButton : public Button {
protected:
	string icon;

public:
	IconButton(GMenu2X *gmenu2x, string icon);
	virtual ~IconButton() {};

	virtual void paint();
	virtual bool paintHover();

	string getIcon();
	void setIcon(string icon);

	void setAction(ButtonAction action);
};

#endif
