#ifndef RUNMANAGER_H
#define RUNMAMAGER_H

#include "ev3api.h"
#include "Clock.h"
#include "TailController.h"
#include "BalancingWalker.h"
#include "CourceMonitor.h"
#include "PIDController.h"
#include "TouchController.h"
#include "BTTask.h"
#include "LotManager.h"
#include "UI.h"
#include "Logger.h"
#include "LookupMethod.h"
#include "TailWalker.h"
#include "Garage.h"
#include "StairScenario.h"

using namespace ev3api;

class RunManager
{

private:
  enum State
  {
    UNDEFINED,         //未定義
    WAITING_FOR_START, //スタート待ち
    LINE_TRACE,        //走行中
    SCENARIO_TRACE,    //難所
    GARAGE_IN
  };

  enum CourseState 
  {
    R,
    L
  };

  State run_state;
  const CourseState course_state = R;

  Clock *clock;
  TailController *tailController;
  BalancingWalker *balancingWalker;
  CourceMonitor *courceMonitor;
  PIDController *pidController;
  BTTask *btTask;
  LotManager *lotManager;
  UI *ui;
  Logger *filteringColor_logger;
  LookupMethod *lookupMethod;
  TouchController *touchController;
  TailWalker *tailWalker;
  Garage *garage;
  StairScenario *stairScenario;

  void execUndefined();
  void execWaitingForStart();
  void execLineTracing();
  void execScenarioTracing();
  void execGarageIn();
  void calibration();
  void displayToLCD(int color);
  int getCourceColor();
  void grayChecker(int color);
  bool isClearScenario(int color);

public:
  RunManager();
  void run();
  bool isTipOver();
  virtual ~RunManager();
};

#endif
