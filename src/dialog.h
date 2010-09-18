#ifndef __DIALOG_H__
#define __DIALOG_H__

#include <string>

class GMenu2X;
class Surface;

class Dialog
{
public:
	Dialog(GMenu2X *gmenu2x);

protected:
	void drawTitleIcon(const std::string &icon, bool skinRes = false, Surface *s = NULL);
	void writeTitle(const std::string &title, Surface *s = NULL);
	void writeSubTitle(const std::string &subtitle, Surface *s = NULL);

	GMenu2X *gmenu2x;
};

#endif
