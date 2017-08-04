#ifndef COURCEMONITOR_H
#define COURCEMONITOR_H

#include "ColorSensor.h"

using namespace ev3api;

class CourceMonitor
{

  private:
    int black, white, glay;
    int target_color;

    ColorSensor *colorSensor;

  public:
    CourceMonitor();
    int getCurrentColor();
    int getTargetColor();
    virtual ~CourceMonitor();
};

#endif