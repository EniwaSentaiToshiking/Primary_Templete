#ifndef COURCEMONITOR_H
#define COURCEMONITOR_H

#include "ColorSensor.h"

#define buffersize 10
#define gray_buffer_max 1000
#define gray_limit 4

using namespace ev3api;

class CourceMonitor
{

  private:
    int black, white, glay;
    int target_color;
    int buffer[buffersize] = {};
    int bufferSubscript;
    int bandMax, bandMin;

    int gray_buffer[gray_buffer_max] = {};
    int gray_buffer_num = 0;
    int gray_count = 0;

    ColorSensor *colorSensor;

  public:
    CourceMonitor();
    int getCurrentColor();
    int lowpassFilter(int colorsensor);
    int bandFilter(int colorsensor);
    int getTargetColor();
    void setColor(char color_initial);
    void setTargetColor();
    bool isGrayLine(int current_color);
    int getColor(char color_initial);
    void detectCorrectStartPosition();
    bool isSetColor(char color_initial);
    virtual ~CourceMonitor();
};

#endif
