#include "StairScenario.h"
#include <cmath>

StairScenario::StairScenario(BalancingWalker* bw, TailController* tc) {
  clock = new Clock();
  tailController = new TailController();
  leftMotor = new Motor(PORT_B);
  rightMotor = new Motor(PORT_C);
  courceMonitor = new CourceMonitor();
  pidController = new PIDController();
  gyroSensor = new GyroSensor(PORT_4);
  measure = new Measure();
  stairState = PREPARE;
  balancingWalker = bw;
  tailController = tc;

  log = new Logger("test.log");
}

StairScenario::~StairScenario() {
  delete clock;
  delete tailController;
  delete leftMotor;
  delete rightMotor;
  delete courceMonitor;
  delete pidController;
  delete gyroSensor;
  delete measure;
  delete log;
}

void StairScenario::nextState() {
  clock->reset();
  stairState = (StairScenarioState)(stairState + 1);
}

void StairScenario::goStraight(int pwm) {
  leftMotor->setPWM(pwm);
  rightMotor->setPWM(pwm);
}

void StairScenario::goLineTrace(int speed) {
  int current_color = courceMonitor->getCurrentColor();
  int lowpassfiltering_color = courceMonitor->lowpassFilter(current_color);
  int bandfiltering_color = courceMonitor->bandFilter(lowpassfiltering_color);
  int target_color = courceMonitor->getTargetColor();
  PID *pid = new PID(1.0, 0.0, 0.5);

  int turn;
  if (speed >= 0)
  {
      turn = pidController->getTurn(pid, bandfiltering_color, target_color, speed * -1, speed);
  }
  else
  {
      turn = pidController->getTurn(pid, bandfiltering_color, target_color, speed, speed * -1);
  }

  balancingWalker->setCommand(speed, turn, 0);
  balancingWalker->run();
}

void StairScenario::goBalancingWalk(int speed) {
  balancingWalker->setCommand(speed, 0, balancingWalker->getGyroOffset()); 
  // balancingWalker->run();
  balancingWalker->linearRun();
}

bool StairScenario::inTime(int time1,int time2) {
  int time = clock->now();
  return (time > time1 && time < time2);
}

void StairScenario::run() {
  switch(stairState) {
    case PREPARE:
      tailController->rotate(0, 100, false);
      goBalancingWalk(0);
      nextState();
      break;
      
    case GOTOSTAIR:
      if(inTime(0, 1000)) {
        goBalancingWalk(0);
      } 
      if(inTime(1000  , 100000000)) {
        goBalancingWalk(10);
        // 段差検知
        if (fabs(gyroSensor->getAnglerVelocity()) > THRESHOLD) {
          ev3_speaker_play_tone(600, 100);
          measure->measure();
          measure->distance_reset();
          nextState();
        }
      } 
      break;

    // case BACK:
    //   if(inTime(0, 1000000000)) {
    //     goBalancingWalk(-10);
    //     measure->measure();
    //     if((measure->point_x) < - 4.0) {
    //       ev3_speaker_play_tone(400,100);
    //       measure->measure();
    //       measure->distance_reset();
    //       nextState();
    //     }
    //   } 
    //   break;

    case STEP1:
      tailController->rotate(0, 80, false);
      if(inTime(0  , 200000000)) {
        goBalancingWalk(80);
      }
      measure->measure();
      if((measure->point_x) >  4.0) {
        ev3_speaker_play_tone(300, 100);
        goBalancingWalk(0);
        rotation = leftMotor->getCount();
        measure->measure();
        measure->distance_reset();
        nextState();
      }
      break;

    case GOTOSTAIR2:
      if(inTime(0, 1000)) {
        goBalancingWalk(50);
      }
      if(inTime(1000  , 100000000)) {
        goBalancingWalk(10);
        // 段差検知
        if (fabs(gyroSensor->getAnglerVelocity()) > THRESHOLD) {
          ev3_speaker_play_tone(100, 100);
          measure->measure();
          measure->distance_reset();
          nextState();
        }
      } 
      break;

    case BACK2:
      goBalancingWalk(-30);
      measure->measure();
      if((measure->point_x) < - 10.0) {
        ev3_speaker_play_tone(400,100);
        nextState();
      }
      break;

    case SPIN1:
      if(inTime(0  , 1000)) {
        goStraight(5);
        tailController->rotate(75, 50, true);
      }
      if(inTime(1000  , 2000)) {
        goStraight(-5);
        tailController->rotate(75, 50, true);
        rotation = leftMotor->getCount();
      }
      if(inTime(2000  , 1000000000)) {
        leftMotor->setPWM(10);
        rightMotor->setPWM(-10);
        if(leftMotor->getCount() - rotation >= 750) {
          ev3_speaker_play_tone(800,100);
          balancingWalker->resetWheel();
          goStraight(0);
          nextState();
        }
      }
      break;

    case STANDUP:
        // tailController->standUpBody(80);
        tailController->rotate(79, 10, true);
        ev3_speaker_play_tone(400,100);
        clock->wait(800);
        tailController->rotate(80, 10, true);
        clock->wait(800);
        tailController->rotate(83, 10, true);
        clock->wait(800);
        tailController->rotate(85, 10, true);
        clock->wait(800);
        tailController->rotate(87, 10, true);
        clock->wait(800);
        tailController->rotate(89, 10, true);
        goStraight(5);
        clock->wait(400);
        tailController->rotate(93, 10, true);
        ev3_speaker_play_tone(900,100);
        nextState();
        break;

    case GOTOSTAIR3:
      if(inTime(0, 1000)) {
        tailController->rotate(0,50,false);
        goBalancingWalk(0);
      }
      if(inTime(100  , 100000000)) {
        tailController->rotate(0,50,false);
        goBalancingWalk(20);
        // 段差検知
        if (fabs(gyroSensor->getAnglerVelocity()) > THRESHOLD) {
          ev3_speaker_play_tone(600, 100);
          measure->measure();
          measure->distance_reset();
          nextState();
        }
      } 
      break;

    case STEP2:
      if(inTime(0  , 100000000)) {
        tailController->rotate(0, 80, false);
        goBalancingWalk(80);
        measure->measure();
        if(measure->point_x > 4.0) {
          ev3_speaker_play_tone(400, 100);
          measure->measure();
          measure->distance_reset();
          goBalancingWalk(0);
          nextState();
        }
      }
      break;
      
    case SPIN2:
      if(inTime(0, 3000)) {
        goBalancingWalk(0);
      }
      if(inTime(3000, 5000)) {
        goStraight(5);
        tailController->rotate(75, 80, false);
      }
      if(inTime(5000, 10000)) {
        goStraight(0);
        tailController->rotate(75, 80, false);
        rotation = leftMotor->getCount();
      }
      if(inTime(10000,10000000)) {
        leftMotor->setPWM(10);
        rightMotor->setPWM(-10);
        if(leftMotor->getCount() - rotation >= 1200) {
          nextState();
        }
      }
      break;

    case END:
      break;
  }
}