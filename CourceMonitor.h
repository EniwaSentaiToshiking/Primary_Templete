#ifndef COURCEMONITOR_H
#define COURCEMONITOR_H
#define buffersize 10

#include "ColorSensor.h"

using namespace ev3api;

class CourceMonitor
{

  private:
    int black, white, glay;
    int target_color;
    int buffer[buffersize] = {};
    int bufferSubscript;
    int bandMax, bandMin;

    ColorSensor *colorSensor;

  public:
    CourceMonitor();
    int getCurrentColor();
    int lowpassFilter(int colorsensor);
    int bandFilter(int colorsensor);
    int getTargetColor();
    void setColor(char color_initial);
    void setTargetColor();
    virtual ~CourceMonitor();
};

#endif
