#include "TailController.h"

TailController::TailController()
{
	ev3_motor_config(PORT, LARGE_MOTOR);
	current_angle = 0;
	reset();
}

TailController::~TailController()
{
	reset();
	current_angle = 0;
}

void TailController::rotate(int angle, uint32_t speed, bool block)
{

	if (angle != current_angle)
	{
		ev3_motor_rotate(PORT, angle - current_angle, speed, block);
		current_angle = angle;
	}
}

void TailController::reset()
{
	ev3_motor_reset_counts(PORT);
}
