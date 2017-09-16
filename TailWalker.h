#ifndef TAILWALKER_H
#define TAILWALKER_H

#include "Motor.h"
#include "Clock.h"
#include "Measure.h"

using namespace ev3api;

#define TURN_PWM 20
#define BUFFER_SIZE 4

class TailWalker
{
  private:
    Motor *leftMotor;
    Motor *rightMotor;
    Clock *clock;
    Measure *mea;
    int right_buffer[BUFFER_SIZE];
    int left_buffer[BUFFER_SIZE];
    int left_buffer_count = 0;
    int right_buffer_count = 0;

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
    bool get4msRightMotorCount();
    bool get4msLeftMotorCount();
    void bufferInit();
    virtual ~TailWalker();
};

#endif
