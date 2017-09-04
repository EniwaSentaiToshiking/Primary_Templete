#ifndef STAIRSCENARIO_H 
#define STAIRSCENARIO_H

#include "Motor.h"
#include "Clock.h"
#include "CourceMonitor.h"
#include "PIDController.h"
#include "BalancingWalker.h"
#include "TailController.h"
#include "PID.h"
#include "GyroSensor.h"
#include "Measure.h"

#include "Logger.h"

using namespace ev3api;

class StairScenario {
  enum StairScenarioState{
    PREPARE = 0,
    GOTOSTAIR,
    BACK,
    STEP1,
    GOTOSTAIR2,
    BACK2,
    SPIN1,
    STANDUP,
    GOTOSTAIR3,
    // BACK3,
    STEP2,
    SPIN2,
    END
  };

private:
  Clock *clock;
  TailController *tailController;
  BalancingWalker *balancingWalker;
  Motor* leftMotor;
  Motor* rightMotor;
  CourceMonitor* courceMonitor;
  PIDController* pidController;
  GyroSensor* gyroSensor; 
  Measure* measure;
  
  void nextState();
  void goStraight(int);
  void goLineTrace(int);
  void goBalancingWalk(int);
  bool inTime(int, int);
  StairScenarioState stairState;
  int rotation;
  int time;

  Logger *log;
public:
  StairScenario(BalancingWalker*, TailController* );
  ~StairScenario();
  void run();
};

#endif