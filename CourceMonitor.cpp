#include "CourceMonitor.h"

CourceMonitor::CourceMonitor()
{
    colorSensor = new ColorSensor(PORT_3);
    black = 0;
    white = 40;
    glay = (white + black) / 2;
    target_color = (white + black) / 2;
    push = 0;
}

CourceMonitor::~CourceMonitor()
{
    delete colorSensor;
}

int CourceMonitor::getCurrentColor()
{
    return colorSensor->getBrightness();
}

int CourceMonitor::lowpassFilter(int colorsensor)
{
  buffer[push] = colorsensor;

  int lowpassfilter = 0;
  int sum = 0;
  for(int i = 0; i < 10; i++)
  {
    sum += buffer[i];
  }
  lowpassfilter = sum/10;
  buffer[push] = lowpassfilter;
  push++;

  if(push > 10)
  {
    push = 0;
  }

  return lowpassfilter;
}

int CourceMonitor::bandFilter(int colorvalue)
{
  int bandfilter = (float)colorvalue * 0.01 * (white - black);
  return bandfilter;
}

int CourceMonitor::getTargetColor()
{
    return this->target_color;
}

void CourceMonitor::setColor(char color_initial)
{

    int color = colorSensor->getBrightness();

    switch (color_initial)
    {
    case 'b':
        black = color;
        break;
    case 'w':
        white = color;
        break;
    case 'g':
        glay = color;
        break;
    }
}

void CourceMonitor::setTargetColor()
{
    target_color = (white + black) / 2;
    for(int i = 0; i < 10; i++){
      buffer[i] = target_color;
    }
}
