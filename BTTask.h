#ifndef BTTask_H
#define BTTask_H

#include "ev3api.h"
#include <stdio.h>

#define CMD_START '1'

class BTTask
{

  private:
	FILE *bt;

  public:
	BTTask();
	bool isStart();
	virtual ~BTTask();
};

#endif