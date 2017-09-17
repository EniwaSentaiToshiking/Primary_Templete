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
            black = 3;
        }
        break;
    case 'w':
        if(color > 30)
        {
            white = 47;
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
    target_color = 25;
}

bool CourceMonitor::isGrayLine(int current_color){
   
    gray_buffer[gray_buffer_num] = current_color;

    if (gray_buffer_num == gray_buffer_max-1)
    {
        gray_buffer_num = 0;
    }
    else
    {
        gray_buffer_num++;
    }

    gray_count++;

    if (gray_count == gray_buffer_max)
    {
        ev3_speaker_play_tone(480, 100);
    }

    if(gray_count > 1400){
      int sum = 0;

      for (int i = 0; i < gray_buffer_max; i++){
        sum = sum + gray_buffer[i];
      }

      float average = ((float)sum / (float)(gray_buffer_max + 1));

      if (-((float)current_color - average) > gray_limit){  //取得した輝度値（黒）-平均値（灰色）>閾値,color<灰色,count>灰色をとる時間
        return true;
      }
    }
    return false;
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
