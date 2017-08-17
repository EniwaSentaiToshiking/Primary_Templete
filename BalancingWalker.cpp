#include "BalancingWalker.h"

BalancingWalker::BalancingWalker()
{
  gyroSensor = new GyroSensor(PORT_4);
  motors = new DoubleMotor();
  balancer = new Balancer();
  forward = 0;
  turn = 0;
  offset = 0;

  init();
}

BalancingWalker::~BalancingWalker()
{
  setCommand(0, 0, 0);
  motors->reset();

  delete gyroSensor;
  delete motors;
  delete balancer;
}

void BalancingWalker::run()
{
  int16_t angle = gyroSensor->getAnglerVelocity();
  int rightMotorEnc = this->motors->getRightCount();
  int leftMotorEnc =  this->motors->getLeftCount(); 

  balancer->setCommand(this->forward, this->turn, this->offset);

  int battery = ev3_battery_voltage_mV();
  balancer->update(angle, rightMotorEnc, leftMotorEnc, battery);

  motors->setLinearPWM(balancer->getPwmLeft());
}

void BalancingWalker::init()
{
  int offset = gyroSensor->getAnglerVelocity();
  motors->reset();
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