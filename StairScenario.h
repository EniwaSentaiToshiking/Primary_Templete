#ifndef STAIRSCENARIO_H 
#define STAIRSCENARIO_H

#include "Clock.h"
#include "TailController.h"
#include "TailWalker.h"

using namespace ev3api;

class StairScenario {
  // 上から順番に処理をswitchで行う
  enum State {
    PREPARE,
    DETECT1,
    STEP1,
    SPIN1,
    DETECT2,
    STEP2,
    SPIN2,
    SPIN_HALF,
    STEP3,
    STEP4,
    END
  };

private:
  Clock *clock;
  TailController *tailController;
  TailWalker *tailWalker;

  bool detectStair();

public:
  StairScenario(TailController* tc);
  ~StairScenario();
  bool run(int color);
};

#endif