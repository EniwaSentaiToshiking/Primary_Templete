#ifndef EV3_UNIT_DOUBLEMOTOR_H_
#define EV3_UNIT_DOUBLEMOTOR_H_

#include "Motor.h"
#include "PID.h"
#include "PIDController.h"
#include "Logger.h"

using namespace ev3api;

class DoubleMotor
{
private:
    Motor* leftMotor;
    Motor* rightMotor;
    PID*   pid;
    PIDController* pidController;
    int leftPWM = 0;
    int rightPWM = 0;
    void correctIndividualDifference(int pwm);
    void correctBatteryDefference(int pwm);

public:
    DoubleMotor();
    ~DoubleMotor();
    void setPWM(int leftPWM, int rightPWM);
    void setLinearPWM(int PWM);
    int getRightCount();
    int getLeftCount();
    void reset();
};

#endif