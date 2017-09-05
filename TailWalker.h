#ifndef TAILWALKER_H
#define TAILWALKER_H

#include "Motor.h"
#include "Clock.h"

using namespace ev3api;

#define TURN_PWM 10

class TailWalker
{
  private:
    Motor *leftMotor;
    Motor *rightMotor;
    Clock *clock;

  public:
    TailWalker();
    void balance();
    void forward(int pwm, int time);
    void backward(int pwm, int time);
    void keepOnMovingForward(int pwm);
    void keepOnMovingBackward(int pwm);
    void stop();
    void leftTurn(int motor_count);
    void rightTurn(int motor_count);
    void lineTrace(int color, int target_color);

    virtual ~TailWalker();
};

#endif
