#ifndef LOOKUPMETHOD_H
#define LOOKUPMETHOD_H

#include "Clock.h"
#include "SonarAlert.h"
#include "BalancingWalker.h"
#include "TailController.h"
#include "TailWalker.h"

using namespace ev3api;

class LookupMethod
{

private:
  enum State
  {
    TRANSITION_TO_TAIL_RUN,
    FIRST_PASS_GATE,
    SECOND_PASS_GATE,
    THIRD_PASS_GATE,
    SEARCH_LINE,
    LINE_TRACE
  };

  Clock *clock;
  SonarAlert *sonarAlert;
  BalancingWalker *balancingWalker;
  TailController *tailController;
  TailWalker *tailWalker;

public:
  bool isBackLine = false;

  LookupMethod(BalancingWalker *balancingWalker, TailController *tailController);
  void run(int color);
  bool isGate(int distance);

  virtual ~LookupMethod();
};

#endif