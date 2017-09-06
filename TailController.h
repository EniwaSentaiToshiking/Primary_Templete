#ifndef TailController_H
#define TailController_H

#include "Motor.h"
#include "Clock.h"

using namespace ev3api;

#define PORT EV3_PORT_A

class TailController
{
	private:
	Clock *clock;
	int current_angle;

  public:
	TailController();
	void rotate(int angle, uint32_t speed, bool block);
	void standUpBody(int target_angle);
	void bendBody(int targer_angle);
	void reset();
	int getCurrentAngle();
	void rocketStart();

	virtual ~TailController();
};
#endif