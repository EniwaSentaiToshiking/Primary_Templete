#ifndef TAILWALKER_H
#define TAILWALKER_H

#include "Motor.h"
#include "Clock.h"
#include "Measure.h"

using namespace ev3api;

#define TURN_PWM 20

class TailWalker
{
  private:
    Motor *leftMotor;
    Motor *rightMotor;
    Clock *clock;
    Measure *mea;

  public:
    TailWalker();
    void balance();
    void forward(int pwm, float distance);
    void backward(int pwm, float distance);
    void keepOnMovingForward(int pwm);
    void keepOnMovingBackward(int pwm);
    void stop();
    void leftTurn(int motor_count);
    void rightTurn(int motor_count);
    void lineTrace(int color, int target_color);
    void reset_distance();
    float getDistance();
    virtual ~TailWalker();
};

#endif
