#include "RunManager.h"

RunManager::RunManager()
{
    clock = new Clock();
    tailController = new TailController();
    balancingWalker = new BalancingWalker();
    touchController = new TouchController();
    courceMonitor = new CourceMonitor();
    pidController = new PIDController();
    btTask = new BTTask();
    lotManager = new LotManager();
    ui = new UI();
    run_state = UNDEFINED;
}

RunManager::~RunManager()
{
}

void RunManager::run()
{
    switch (run_state)
    {
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
    calibration();
    run_state = WAITING_FOR_START;
}

/**
 * 開始待ち状態の処理
 **/
void RunManager::execWaitingForStart()
{
    tailController->rotate(93, 80, true);
    if (touchController->isPressed() || btTask->isStart())
        run_state = LINE_TRACE;
    clock->sleep(10);
}

/**
 * ライントレース状態の処理
 **/
void RunManager::execLineTracing()
{
    tailController->rotate(0, 80, false);

    if (lotManager->isChangeCurrentLot())
        lotManager->changeCurrentLot();

    int current_color = courceMonitor->getCurrentColor();
    int target_color = courceMonitor->getTargetColor();
    int speed = lotManager->getCurrentLotSpeed();
    PID *pid = lotManager->getCurrentLotPID();

    int turn = 0;

    if (speed >= 0)
    {
        turn = pidController->getTurn(pid, current_color, target_color, speed * -1, speed);
    }
    else
    {
        turn = pidController->getTurn(pid, current_color, target_color, speed, speed * -1);
    }

    balancingWalker->setCommand(speed, turn, 0);
    balancingWalker->run();
}

/**
 * ゴール後の処理
 */
void RunManager::execScenarioTracing()
{
}

void RunManager::calibration()
{
    int count = 0;
    while (count < 3)
    {
        if (touchController->isPressed())
        {
            ev3_speaker_play_tone(880, 100);

            switch (count)
            {
            case 0:
                courceMonitor->setColor('b');
                break;
            case 1:
                courceMonitor->setColor('w');
                break;

            case 2:
                courceMonitor->setColor('g');
                break;
            }
            count++;
        }

        clock->sleep(10);
    }

    courceMonitor->setTargetColor();
}
