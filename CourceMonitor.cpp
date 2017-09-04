#include "CourceMonitor.h"

CourceMonitor::CourceMonitor()
{
    colorSensor = new ColorSensor(PORT_3);
    black = -1;
    white = -1;
    glay = (white + black) / 2;
    target_color = (white + black) / 2;
    bufferSubscript = 0;
    bandMax = 50;
    bandMin = 5;
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
  buffer[bufferSubscript] = colorsensor;

  int lowpassfilteringValue = 0;
  int sum = 0;
  for(int i = 0; i < buffersize; i++)
  {
    sum += buffer[i];
  }
  lowpassfilteringValue = sum/buffersize;
  buffer[bufferSubscript] = lowpassfilteringValue;
  bufferSubscript++;

  if(bufferSubscript > buffersize)
  {
    bufferSubscript = 0;
  }

  return lowpassfilteringValue;
}

int CourceMonitor::bandFilter(int colorsensor)
{
  int bandfilteringValue = bandMax - (bandMax - bandMin)*(float)(colorsensor - white) / (black - white);
  return bandfilteringValue;
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
        if(color < 10)
        {
            black = color;
        }
        break;
    case 'w':
        if(color > 30)
        {
            white = color;
        }
        break;
    case 'g':
        glay = color;
        break;
    }
}

int CourceMonitor::getColor(char color_initial)
{
    switch (color_initial)
    {
    case 'b':
        return this->black;
        break;
    case 'w':
        return this->white;
        break;
    case 'g':
        return this->glay;
        break;
    }

    return 0;
}

void CourceMonitor::setTargetColor()
{
    target_color = (white + black) / 2;
}

void CourceMonitor::detectCorrectStartPosition()
{
    int color = colorSensor->getBrightness();

    if(color == target_color + 1 || color  == target_color - 1)
    {
        ev3_speaker_play_tone(300, 100);
    }
}

bool CourceMonitor::isSetColor(char color_initial)
{
    if(getColor(color_initial) == -1)
    {
        ev3_speaker_play_tone(300, 100);
        return false;
    }

    ev3_speaker_play_tone(880, 100);
    return true;
}