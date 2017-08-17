#include "DoubleMotor.h"
#include "PID.h"
#include "PIDController.h"

DoubleMotor::DoubleMotor()
{
  leftMotor  = new Motor(PORT_C);
  rightMotor = new Motor(PORT_B);
  pidController = new PIDController();
  pid        = new PID(0.5, 0.0, 0.01); //Iは使わないので0.0
}

DoubleMotor::~DoubleMotor()
{
  delete leftMotor;
  delete rightMotor;
  delete pid;
  delete pidController;
}   

void DoubleMotor::reset() {
  this->leftMotor->reset();
  this->rightMotor->reset();
}

int DoubleMotor::getRightCount() {
  return this->rightMotor->getCount();
}

int DoubleMotor::getLeftCount() {
  return this->leftMotor->getCount();
}

void DoubleMotor::setPWM(int leftPWM, int rightPWM)
{ 
  this->leftMotor ->setPWM(leftPWM);
  this->rightMotor->setPWM(rightPWM);   
}

void DoubleMotor::setLinearPWM(int pwm) {
  // 補正してからモータ動かす
  this->correctIndividualDifference(pwm);
  this->correctBatteryDefference(pwm);
  this->leftMotor->setPWM(this->leftPWM);
  this->rightMotor->setPWM(this->rightPWM);
}


void DoubleMotor::correctIndividualDifference(int pwm) {
  int leftCount  = leftMotor ->getCount();
  int rightCount = rightMotor->getCount();
  // 小さい値を目標値にする
  bool lowLeft = leftCount <  rightCount;
  int targetCount = lowLeft ? leftCount : rightCount;
  int nowCount = !lowLeft ? leftCount : rightCount;
  
  double correction = 
     this->pidController->getTurn(this->pid, nowCount, targetCount, -130, 130);

  if (lowLeft) {
    this->leftPWM = pwm;
    this->rightPWM = pwm - correction;
  } else {
    this->leftPWM = pwm - correction;
    this->rightPWM = pwm;
  }
}

void DoubleMotor::correctBatteryDefference(int pwm) {
}