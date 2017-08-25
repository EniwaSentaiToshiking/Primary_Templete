#include "WheelCorrect.h"
#include "PID.h"
#include "PIDController.h"

WheelCorrect::WheelCorrect()
{
  leftMotor  = new Motor(PORT_C);
  rightMotor = new Motor(PORT_B);
  pidController = new PIDController();
  p = new PID(0.5, 0.0, 0.0);
}

WheelCorrect::~WheelCorrect()
{
  delete leftMotor;
  delete rightMotor;
  delete p;
  delete pidController;
}   


void WheelCorrect::calcLinearPWM(int leftPWM, int rightPWM) {
  this->leftPWM = leftPWM;
  this->rightPWM = rightPWM;
  this->correctBatteryDifference(leftPWM, rightPWM);
  this->correctIndividualDifference(leftPWM, rightPWM);
}

int WheelCorrect::getLeftPWM() {
  return this->leftPWM;
}

int WheelCorrect::getRightPWM() {
  return this->rightPWM;
}

void WheelCorrect::correctIndividualDifference(int leftPWM, int rightPWM) {
  int leftCount  = this->leftMotor->getCount();
  int rightCount = this->rightMotor->getCount();

  bool leftIsLow = leftCount <  rightCount;
  int targetCount = leftIsLow ? leftCount : rightCount;
  int nowCount = leftIsLow ? rightCount : leftCount;
  
  double correction = 
     this->pidController->getTurn(this->p, nowCount, targetCount, -130, 130);

  if (leftIsLow) {
    this->leftPWM = leftPWM;
    this->rightPWM = rightPWM - correction;
  } else {
    this->leftPWM = leftPWM - correction;
    this->rightPWM = rightPWM;
  }
}

void WheelCorrect::correctBatteryDifference(int leftPWM, int rightPWM) {
  int battery = ev3_battery_voltage_mV();
  this->leftPWM  = leftPWM *  (double)battery / this->BATTERY;
  this->rightPWM = rightPWM * (double)battery / this->BATTERY;
}