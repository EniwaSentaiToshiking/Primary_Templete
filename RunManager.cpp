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
    filteringColor_logger = new Logger("lowpassColor.txt");
    lookupMethod = new LookupMethod(balancingWalker, tailController);
    tailWalker = new TailWalker();
    run_state = UNDEFINED;
}

RunManager::~RunManager()
{
    delete tailController;
    delete balancingWalker;
    delete touchController;
    delete courceMonitor;
    delete pidController;
    delete btTask;
    delete lotManager;
    delete ui;
    delete filteringColor_logger;
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
    tailController->rotate(100, 80, true);
    calibration();
    run_state = WAITING_FOR_START;
}

/**
 * 開始待ち状態の処理
 **/
void RunManager::execWaitingForStart()
{
    tailController->rotate(95, 80, true);
    if (touchController->isPressed() || btTask->isStart())
        run_state = LINE_TRACE;
    clock->sleep(10);
}

/**
 * ライントレース状態の処理
 **/
void RunManager::execLineTracing()
{

    tailController->rocketStart();
    tailController->rotate(0, 80, false);

    if (lotManager->isChangeCurrentLot())
        lotManager->changeCurrentLot();

    int current_color = getCourceColor();
    int target_color = courceMonitor->getTargetColor();
    int speed = lotManager->getCurrentLotSpeed();
    PID *pid = lotManager->getCurrentLotPID();

    filteringColor_logger->logging(current_color);

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

    if(lookupMethod->isGate(10))
    {
        run_state = SCENARIO_TRACE;
        clock->reset();
    }
}

/**
 * ゴール後の処理
 */
void RunManager::execScenarioTracing()
{
    if (lookupMethod->run())
    {
        tailWalker->lineTrace(getCourceColor(), 23);
    }
}

void RunManager::calibration()
{
    int count = 0;

    while (count < 4)
    {
        if(count == 3){
            courceMonitor->detectCorrectStartPosition(); 
        }

        if (touchController->isPressed())
        {
            switch (count)
            {
            case 0:
                courceMonitor->setColor('b');
                
                if(courceMonitor->isSetColor('b'))
                {
                    displayToLCD(courceMonitor->getColor('b'));
                    count++;
                }
                break;
            case 1:
                courceMonitor->setColor('w');
                
                if(courceMonitor->isSetColor('w'))
                {
                    displayToLCD(courceMonitor->getColor('w'));
                    courceMonitor->setTargetColor();
                    count++;
                }
                break;

            case 2:
                courceMonitor->setColor('g');
                displayToLCD(courceMonitor->getColor('g'));
                ev3_speaker_play_tone(880, 100);
                count++;
                break;
            default:
                count++;
                ev3_speaker_play_tone(880, 100);
                break;
            }
        }

        clock->sleep(10);
    }
}

bool RunManager::isTipOver()
{
    return balancingWalker->isTipOver();
}

void RunManager::displayToLCD(int color){
    char color_string[256];
    sprintf(color_string, "%d", color);
    ui->lcdDraw(color_string);
}

int RunManager::getCourceColor(){
    int current_color = courceMonitor->getCurrentColor();
    int bandfiltering_color = courceMonitor->bandFilter(current_color);
    return bandfiltering_color;
}