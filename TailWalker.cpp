#include "TailWalker.h"

TailWalker::TailWalker()
{
    leftMotor = new Motor(PORT_C);
    rightMotor = new Motor(PORT_B);
    clock = new Clock();
}

TailWalker::~TailWalker() {}

void TailWalker::balance()
{
    leftMotor->setPWM(15);
    rightMotor->setPWM(15);
    clock->sleep(300);
    stop();
}

void TailWalker::forward(int pwm, int time)
{
    clock->reset();
    while (clock->now() <= float(time))
    {
        leftMotor->setPWM(pwm);
        rightMotor->setPWM(pwm);
    }
    stop();
}

void TailWalker::backward(int pwm, int time)
{
    clock->reset();
    while (clock->now() >= float(time))
    {
        leftMotor->setPWM(pwm);
        rightMotor->setPWM(pwm);
    }
    stop();
}

void TailWalker::keepOnMovingForward(int pwm)
{
    leftMotor->setPWM(pwm);
    rightMotor->setPWM(pwm);
}

void TailWalker::keepOnMovingBackward(int pwm)
{
    leftMotor->setPWM(pwm * -1);
    rightMotor->setPWM(pwm * -1);
}

void TailWalker::stop()
{
    leftMotor->setPWM(0);
    rightMotor->setPWM(0);
    clock->sleep(300);
}

void TailWalker::leftTurn(int motor_count)
{
    float begin_motor_count = leftMotor->getCount();

    while (leftMotor->getCount() - begin_motor_count < motor_count)
    {
        leftMotor->setPWM(TURN_PWM);
        rightMotor->setPWM(TURN_PWM * -1);
    }
    stop();
}

void TailWalker::rightTurn(int motor_count)
{
    float begin_motor_count = rightMotor->getCount();

    while (rightMotor->getCount() - begin_motor_count < motor_count)
    {
        leftMotor->setPWM(TURN_PWM * -1);
        rightMotor->setPWM(TURN_PWM);
    }
    stop();
}

void TailWalker::lineTrace(int color, int target_color)
{
    if (color >= target_color)
    {
        rightMotor->setPWM(6);
        leftMotor->setPWM(9);
    }
    else
    {
        rightMotor->setPWM(9);
        leftMotor->setPWM(6);
    }
}