
#include "button.h"
#include "gmenu2x.h"

#include "buttonbox.h"

ButtonBox::ButtonBox(GMenu2X *gmenu2x) : gmenu2x(gmenu2x)
{
}

ButtonBox::~ButtonBox()
{
	for (ButtonList::const_iterator it = buttons.begin(); it != buttons.end(); ++it)
		delete *it;
}

void ButtonBox::add(Button *button)
{
	buttons.push_back(button);
}

void ButtonBox::paint(unsigned int posX)
{
	for (ButtonList::const_iterator it = buttons.begin(); it != buttons.end(); ++it)
		posX = gmenu2x->drawButton(*it, posX);
}

void ButtonBox::handleTS()
{
	for (ButtonList::iterator it = buttons.begin(); it != buttons.end(); ++it)
		(*it)->handleTS();
}
