#ifndef __BUTTONBOX_H__
#define __BUTTONBOX_H__

#include <vector>

class GMenu2X;
class Button;

class ButtonBox
{
public:
	ButtonBox(GMenu2X *gmenu2x);
	~ButtonBox();

	void add(Button *button);

	void paint(unsigned int posX);
	void handleTS();
private:
	typedef std::vector<Button*> ButtonList;

	ButtonList buttons;
	GMenu2X *gmenu2x;
};

#endif
