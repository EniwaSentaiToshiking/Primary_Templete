#include "RunManager.h"

RunManager::RunManager()
{
    clock = new Clock();
    tailController = new TailController();
    balancingWalker = new BalancingWalker();
    touchSensor = new TouchSensor(PORT_1);
    run_state = UNDEFINED;
}

RunManager::~RunManager()
{
}

void RunManager::run()
{
    switch(run_state){
        case UNDEFINED:
            execUndefined();
        break;

        case WAITING_FOR_START:
            execWaitingForStart();
        break;

        case LINE_TRACE:
            execLineTracing();
        break;

        case SCENARIO_TRACE:
            execScenarioTracing();
        break;
        default:
        break;
    }
}

/**
 * 未定義状態の処理
 **/
void RunManager::execUndefined()
{
    tailController->rotate(93, 80, true);
    if(touchSensor->isPressed()) run_state = WAITING_FOR_START;
    clock->sleep(10);
}

/**
 * 開始待ち状態の処理
 **/
void RunManager::execWaitingForStart()
{
    tailController->rotate(93, 80, true);
    if(touchSensor->isPressed()) run_state = LINE_TRACE;
    clock->sleep(10);
}

/**
 * ライントレース状態の処理
 **/
void RunManager::execLineTracing()
{
    tailController->rotate(0, 80, false);
    balancingWalker->setCommand(30,0,0);
    balancingWalker->run();
}

/**
 * ゴール後の処理
 */
void RunManager::execScenarioTracing()
{
}
