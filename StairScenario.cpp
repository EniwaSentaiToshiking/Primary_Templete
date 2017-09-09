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
  balancingWalker = bw;
  tailController = tc;

  // 状態初期化
  stairState = (StairScenarioState)0;

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

// 次の状態に遷移＆タイム測定リセット＆自己位置推定リセット
void StairScenario::nextState() {
  clock->reset();
  stairState = (StairScenarioState)(stairState + 1);
  measureReset();
}

// 自己位置推定リセット
void StairScenario::measureReset() {
  measure->measure();
  measure->distance_reset();
}

// 前に進む（P制御でエンコード調整）
void StairScenario::goStraight(int pwm) {
  int leftCount = leftMotor->getCount();
  int rightCount= rightMotor->getCount();
  int comp = leftCount - rightCount;
  int leftPWM,rightPWM;
  if(comp > 0) {
    leftPWM = pwm - comp * 0.1;
    rightPWM = pwm;
  } else {
    leftPWM = pwm;
    rightPWM = pwm + comp * 0.1;
  }
  leftMotor->setPWM(leftPWM);
  rightMotor->setPWM(rightPWM);
}

// ライントレース
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

// 倒立振子運動
void StairScenario::goBalancingWalk(int speed) {
  balancingWalker->setCommand(speed, 0, balancingWalker->getGyroOffset()); 
  balancingWalker->linearRun();
}

void  StairScenario::goTailWalk(int speed, int angle) {
  tailController->rotate(angle, 80, false);
  goStraight(speed);
}

void StairScenario::tailUp() {
  tailController->rotate(90, 10, false);
  goStraight(20);
}

// time1ミリ秒からtime2ミリ秒の間にいるか
bool StairScenario::inTime(int time1,int time2) {
  int time = clock->now();
  return (time > time1 && time < time2);
}

// ジャイロセンサから段差推定
bool StairScenario::isDetectedStep() {
  return fabs(gyroSensor->getAnglerVelocity()) > THRESHOLD;
}

// 回転
void StairScenario::spin(int encodeOffset) {
  leftMotor->setPWM(10);
  rightMotor->setPWM(-10);
  if(leftMotor->getCount() - encodeOffset >= 720) {
    goStraight(0);
    encodeOffset = leftMotor->getCount();
    nextState();
  }
}

void StairScenario::run() {
  log->logging(gyroSensor->getAnglerVelocity());
  switch(stairState) {
    // 一段目段差検知
    case DETECT1_1:
      goTailWalk(20, 70);
      if (isDetectedStep()) {
        ev3_speaker_play_tone(300, 100);
        nextState();
      }
      break;

    // 登る
    case STEP1:
      if(inTime(0, 5000)) {
        goTailWalk(0, 70);
      }
      if(inTime(5000, 100000)) {
        tailUp();
      }
      if(inTime(1000000, MAX)) {
        nextState();
      }
      break;

    // 二段目段差検知
    case DETECT1_2:
      goTailWalk(10, 70);
      if (isDetectedStep()) {
        ev3_speaker_play_tone(300, 100);
        nextState();
      }
      break;

    // 回転のために戻る
    case BACK1:
      goTailWalk(-10,80);
      measure->measure();
      if((measure->point_x) < - 10.0) {
        nextState();
        encodeOffset = leftMotor->getCount();
      }
      break;

    // 一段目の回転
    case SPIN1:
      spin(encodeOffset);
      break;

    // 二段目段差検知
    case DETECT2:
      goTailWalk(10, 70);
      if (isDetectedStep()) {
        ev3_speaker_play_tone(300, 100);
        nextState();
      }
      break;

    // 登る
    case STEP2:
      if(inTime(0, 2000)) {
        tailUp();
        encodeOffset = leftMotor->getCount();
      }
      break;

    // 二段目の回転
    case SPIN2:
      spin(encodeOffset);

    // 半回転
    case SPIN_HALF:
      leftMotor->setPWM(10);
      rightMotor->setPWM(-10);
      if(leftMotor->getCount() - encodeOffset >= 360) {
        goStraight(0);
        nextState();
      }

    // 段を降りる
    case STEP3:
      goTailWalk(20, 70);
      if (isDetectedStep()) {
        ev3_speaker_play_tone(300, 100);
        nextState();
      }
      break;

    // 終了
    case END:
      goTailWalk(0, 80);
      break;
  }
}