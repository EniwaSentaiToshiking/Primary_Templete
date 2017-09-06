#ifndef EV3_UNIT_BALANCINGWALKER_H_
#define EV3_UNIT_BALANCINGWALKER_H_

#include "GyroSensor.h"
#include "Motor.h"
#include "BalancerCpp.h"

using namespace ev3api;

class BalancingWalker {
public:

    BalancingWalker();
    virtual ~BalancingWalker();

    void init();
    void run();
    void stay();
    void setCommand(int forward, int turn, int offset);
    bool isTipOver();
    void stopRun();

private:
    const GyroSensor* gyroSensor;
    Motor* leftMotor;
    Motor* rightMotor;
    Balancer* balancer;
    int forward;
    int turn;
    int offset;
};

#endif  // EV3_UNIT_BALANCINGWALKER_H_
