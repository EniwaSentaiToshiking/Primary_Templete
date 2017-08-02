#include "Calibration.h"

Calibration::Calibration(TouchSensor *gTouchSensor, ColorSensor *gColorSensor, UI *gUI, GyroSensor *gyroSensor)
{

  /* Color　Detection*/
  LIGHT_WHITE = 40;
  LIGHT_BLACK = 0;
  LIGHT_GRAY = 20;

  for (int i = 0; i < 4; i++)
  {
    lcd_white[i] = {};
    lcd_black[i] = {};
    lcd_gray[i] = {};
  }

  touch_counter = 0;
  prev_touch = 0;

  m_TouchSensor = gTouchSensor;
  m_ColorSensor = gColorSensor;
  m_UI = gUI;
  m_GyroSensor = gyroSensor;
}

Calibration::~Calibration()
{
  touch_counter = 0;
}

void Calibration::initCali()
{

  if (m_TouchSensor->isPressed() && prev_touch == 0) /*touchsensor*/
  {

    if (touch_counter == 0)
    {
      LIGHT_WHITE = m_ColorSensor->getBrightness(); /*sensing white*/
      sprintf(lcd_white, "WHITE = %d", LIGHT_WHITE);
      m_UI->lcdDraw(lcd_white);
      ev3_speaker_play_tone(880, 100);
      touch_counter = 1;
    }
    else if (touch_counter == 1)
    {
      LIGHT_BLACK = m_ColorSensor->getBrightness(); /*sensing black*/
      sprintf(lcd_black, "BLACK = %d", LIGHT_BLACK);
      m_UI->lcdDraw(lcd_black);
      ev3_speaker_play_tone(880, 100);
      touch_counter = 2;
    }
    else if (touch_counter == 2)
    {
      LIGHT_GRAY = m_ColorSensor->getBrightness(); /*sensing black*/
      sprintf(lcd_gray, "GLAY = %d", LIGHT_GRAY);
      m_UI->lcdDraw(lcd_gray);
      ev3_speaker_play_tone(880, 100);
      touch_counter = 3;
    }
  }
  prev_touch = m_TouchSensor->isPressed();
}

uint8_t Calibration::calc_avarage_color()
{

  return (LIGHT_BLACK + LIGHT_WHITE) / 2;
}
