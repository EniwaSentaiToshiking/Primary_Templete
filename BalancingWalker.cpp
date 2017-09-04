#include "BalancingWalker.h"

BalancingWalker::BalancingWalker()
{
  gyroSensor = new GyroSensor(PORT_4);
  leftMotor = new Motor(PORT_C);
  rightMotor = new Motor(PORT_B);
  balancer = new Balancer();
  forward = 0;
  turn = 0;
  offset = 0;

  init();
}

BalancingWalker::~BalancingWalker()
{
  setCommand(0, 0, 0);
  leftMotor->reset();
  rightMotor->reset();

  delete gyroSensor;
  delete rightMotor;
  delete leftMotor;
  delete balancer;
}

void BalancingWalker::run()
{
  int16_t angle = gyroSensor->getAnglerVelocity();
  int rightMotorEnc = rightMotor->getCount();
  int leftMotorEnc = leftMotor->getCount();

  balancer->setCommand(this->forward, this->turn, this->offset);

  int battery = ev3_battery_voltage_mV();
  balancer->update(angle, rightMotorEnc, leftMotorEnc, battery);

  leftMotor->setPWM(balancer->getPwmLeft());
  rightMotor->setPWM(balancer->getPwmRight());
}

void BalancingWalker::init()
{
  int offset = gyroSensor->getAnglerVelocity();
  gyroSensor->setOffset(offset);

  leftMotor->reset();
  rightMotor->reset();

  balancer->init(offset);
}

/**
 * PWM値を設定する
 * @param forward 前進値
 * @param turn    旋回値
 */
void BalancingWalker::setCommand(int forward, int turn, int offset)
{
  this->forward = forward;
  this->turn = turn;
  this->offset = offset;
}

bool BalancingWalker::isTipOver()
{
  if (gyroSensor->getAnglerVelocity() <= -350 || gyroSensor->getAnglerVelocity() >= 350)
  {
    return true;
  }

  return false;
}

int BalancingWalker::getGyroOffset(){
  return this->offset;
}