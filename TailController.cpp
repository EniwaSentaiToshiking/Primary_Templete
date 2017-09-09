#include "TailController.h"

TailController::TailController()
{
	ev3_motor_config(PORT, LARGE_MOTOR);
	clock = new Clock();
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

void TailController::standUpBody(int target_angle)
{
	for (int i = current_angle; i <= target_angle; i++)
	{
		rotate(i, 10, true);
		clock->sleep(4);
	}
	clock->sleep(1000);
}

void TailController::bendBody(int target_angle)
{
	for (int i = current_angle; i >= target_angle; i--)
	{
		rotate(i, 10, true);
		clock->sleep(300);
	}

	clock->sleep(1000);
}

void TailController::reset()
{
	ev3_motor_reset_counts(PORT);
	current_angle = 0;
}

int TailController::getCurrentAngle(){
	return this->current_angle;
}