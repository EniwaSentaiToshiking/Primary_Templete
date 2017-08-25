#ifndef EV3_UNIT_WHEELCORRECT_H_
#define EV3_UNIT_WHEELCORRECT_H_

#include "Motor.h"
#include "PID.h"
#include "PIDController.h"

using namespace ev3api;

class WheelCorrect
{
private:
    Motor* leftMotor;
    Motor* rightMotor;
    PID*   p;
    PIDController* pidController;
    int leftPWM = 0;
    int rightPWM = 0;
    double BATTERY = 7500.0;
    void correctBatteryDifference(int leftPWM, int rightPWM);
    void correctIndividualDifference(int leftPWM, int rightPWM);

public:
    WheelCorrect();
    ~WheelCorrect();
    void calcLinearPWM(int leftPWM, int rightPWM);
    int getLeftPWM();
    int getRightPWM();
};

#endif
