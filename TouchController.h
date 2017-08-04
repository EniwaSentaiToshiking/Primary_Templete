#ifndef TOUCHCONTROLLER_H
#define TOUCHCONTROLLER_H

#include "TouchSensor.h"

using namespace ev3api;

class TouchController
{

  private:
    TouchSensor *touchSensor;
    bool prev_state;
    bool state;

  public:
    TouchController();
    bool isPressed();
    virtual ~TouchController();
};

#endif