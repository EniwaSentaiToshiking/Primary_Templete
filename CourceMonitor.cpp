#include "CourceMonitor.h"

CourceMonitor::CourceMonitor()
{
    colorSensor = new ColorSensor(PORT_3);
    black = 0;
    white = 40;
    glay = (white + black) / 2;
    target_color = (white + black) / 2;
}

CourceMonitor::~CourceMonitor()
{
}

int CourceMonitor::getCurrentColor()
{
    return colorSensor->getBrightness();
}

int CourceMonitor::getTargetColor()
{
    return this->target_color;
}