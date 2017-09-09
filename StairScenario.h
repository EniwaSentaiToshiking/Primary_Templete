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
  // 上から順番に処理をswitchで行う
  enum StairScenarioState {
    DETECT1_1 = 0,
    STEP1,
    DETECT1_2,
    BACK1,
    SPIN1,
    DETECT2,
    STEP2,
    SPIN2,
    SPIN_HALF,
    STEP3,
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
  
  // 次の状態に遷移
  void nextState();
  // PWM
  void goStraight(int);
  // ライントレース
  void goLineTrace(int);
  // 倒立振子運動
  void goBalancingWalk(int);
  // 尻尾運動
  void goTailWalk(int,int);
  // 尻尾持ち上げ
  void tailUp();
  // 位置推定初期化
  void measureReset();
  // 検知
  bool isDetectedStep();
  void spin(int);
  bool inTime(int, int);
  StairScenarioState stairState;
  int encodeOffset;
  int time;

  double THRESHOLD = 60;
  int MAX = 1000000; //大きな数字（番兵）

  Logger *log;
public:
  StairScenario(BalancingWalker*, TailController* );
  ~StairScenario();
  void run();
};

#endif