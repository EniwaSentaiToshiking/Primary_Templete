#ifndef RUNMANAGER_H
#define RUNMAMAGER_H

#include "ev3api.h"
#include "Clock.h"
#include "TailController.h"
#include "BalancingWalker.h"
#include "TouchSensor.h"

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

    TouchSensor *touchSensor;

    void execUndefined();
    void execWaitingForStart();
    void execLineTracing();
    void execScenarioTracing();

  public:
    RunManager();
    void run();

    virtual ~RunManager();
};

#endif