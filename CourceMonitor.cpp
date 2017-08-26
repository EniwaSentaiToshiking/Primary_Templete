#include "CourceMonitor.h"

CourceMonitor::CourceMonitor()
{
    colorSensor = new ColorSensor(PORT_3);
    black = 0;
    white = 40;
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
}

bool CourceMonitor::isGrayLine(int current_color){
   
    gray_buffer[gray_buffer_num] = current_color;
    int sum = 0;

    for (int i = 0; i <= gray_buffer_max; i++)
    {
        sum = sum + gray_buffer[i];
    }

    if (gray_buffer_num == gray_buffer_max)
    {
        gray_buffer_num = 0;
    }
    else
    {
        gray_buffer_num++;
    }

    float average = ((float)sum / (float)gray_buffer_max);

    if (average <= 15 && average >= 13)
    {
        gray_count++;
    }

    if (gray_count == 50)
    {
        ev3_speaker_play_tone(480, 100);
    }

    if (-((float)current_color - average) > gray_limit && current_color < 13 && gray_count >= 20)  //取得した輝度値（黒）-平均値（灰色）>閾値,color<灰色,count>灰色をとる時間
    {
        return true;
    }
    else
    {
        return false;
    }
}
