#include "RunManager.h"

RunManager::RunManager()
{
    clock = new Clock();
    tailController = new TailController();
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
    tailController->rotate(90, 80, true);
    clock->sleep(10);
}

/**
 * 開始待ち状態の処理
 **/
void RunManager::execWaitingForStart()
{
    clock->sleep(10);
}

/**
 * ライントレース状態の処理
 **/
void RunManager::execLineTracing()
{
}

/**
 * ゴール後の処理
 */
void RunManager::execScenarioTracing()
{
}
