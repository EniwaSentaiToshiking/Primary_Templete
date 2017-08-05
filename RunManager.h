#ifndef RUNMANAGER_H
#define RUNMAMAGER_H

#include "ev3api.h"
#include "Clock.h"
#include "TailController.h"
#include "BalancingWalker.h"
#include "CourceMonitor.h"
#include "PID.h"
#include "TouchController.h"
#include "BTTask.h"

using namespace ev3api;

class RunManager
{

private:
  enum State
  {
    UNDEFINED,         //未定義
    WAITING_FOR_START, //スタート待ち
    LINE_TRACE,        //走行中
    SCENARIO_TRACE     //難所
  };

  State run_state;

  Clock *clock;
  TailController *tailController;
  BalancingWalker *balancingWalker;
  CourceMonitor *courceMonitor;
  PID *pid;
  BTTask *btTask;

  TouchController *touchController;

  void execUndefined();
  void execWaitingForStart();
  void execLineTracing();
  void execScenarioTracing();
  void calibration();

public:
  RunManager();
  void run();

  virtual ~RunManager();
};

#endif