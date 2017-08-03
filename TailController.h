#ifndef TailController_H
#define TailController_H

#include "Motor.h"

using namespace ev3api;

#define PORT EV3_PORT_A

class TailController
{
	private:
  int current_angle;

  public:
	TailController();
	void rotate(int angle, uint32_t speed, bool block);
	void reset();

	virtual ~TailController();	
};
#endif