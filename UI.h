#ifndef UI_H
#define UI_H

#include "ev3api.h"

#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6)
#define CALIB_FONT_HEIGHT (8)

class UI
{
private:
	int string_count;

public:
	UI();
	void lcdDraw(const char *string);
	virtual ~UI();
};

#endif
