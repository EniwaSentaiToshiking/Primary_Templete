#include "StairScenario.h"

StairScenario::StairScenario(TailController *tc)
{
    tailController = tc;
    tailWalker = new TailWalker();
    clock = new Clock();
}

StairScenario::~StairScenario()
{
    delete clock;
    delete tailController;
    delete tailWalker;
}

bool StairScenario::run(int color)
{

    static State state = PREPARE;
    float beginDistance = tailWalker->getDistance();

    switch (state)
    {
    case PREPARE:
        tailController->rotate(85, 50, false);
        tailWalker->balance();
        state = DETECT1;
        tailWalker->bufferInit();
        clock->sleep(1000);
        tailController->standUpBody(90);
        clock->reset();
        break;
    // 一段目段差検知
    case DETECT1:
        tailController->rotate(tailController->getCurrentAngle(), 50, false);
        tailWalker->lineTrace(color, 15);
        if (clock->now() > 1000)
        {
            if (detectStair())
            {
                ev3_speaker_play_tone(880, 100);
                tailWalker->backward(5, 5);
                tailWalker->forward(6, 30);
                state = STEP1;
            }
        }
        break;

    // 登る
    case STEP1:
        tailWalker->backward(5, 2);
        tailWalker->stop();
        tailController->standUpBody(100);

        beginDistance = tailWalker->getDistance();

        tailController->rotate(113, 100, true);
        while (tailWalker->getDistance() - beginDistance < 7)
        {
            tailWalker->keepOnMovingForward(50);
            tailController->rotate(75, 100, false);
        }
        tailWalker->stop();
        state = SPIN1;
        break;

    // 一段目の回転
    case SPIN1:
        tailController->standUpBody(85);
        tailWalker->forward(10, 2);
        tailWalker->leftTurn(370);
        tailWalker->bufferInit();
        tailController->standUpBody(90);
        state = DETECT2;
        clock->reset();
        break;

    // 二段目段差検知
    case DETECT2:
        tailController->rotate(90, 50, false);
        tailWalker->lineTrace(color, 12);

        if (clock->now() > 1000)
        {
            if (detectStair())
            {
                ev3_speaker_play_tone(880, 100);
                tailWalker->backward(5, 5);
                tailWalker->forward(6, 30);
                state = STEP2;
            }
        }
        break;

    // 登る
    case STEP2:
        tailWalker->backward(5, 2);
        tailWalker->stop();
        tailController->standUpBody(100);

        beginDistance = tailWalker->getDistance();

        tailController->rotate(113, 100, true);
        while (tailWalker->getDistance() - beginDistance < 7)
        {
            tailWalker->keepOnMovingForward(50);
            tailController->rotate(75, 100, false);
        }
        tailWalker->stop();
        state = SPIN2;
        break;

    // 二段目の回転
    case SPIN2:
        tailController->standUpBody(85);
        tailWalker->forward(10, 5);
        tailWalker->leftTurn(370);
        clock->sleep(100);
        tailWalker->backward(5, 3);
        state = SPIN_HALF;
        break;

    // 半回転
    case SPIN_HALF:
        tailWalker->leftTurn(93);
        tailController->standUpBody(90);
        //tailWalker->forward(5,2); <- もし本番で黒ラインど真ん中に入ってしまうようなら解放
        state = STEP3;
        break;

    // 段ギリギリまで進む
    case STEP3:
        tailController->rotate(90, 30, false);
        tailWalker->lineTrace(color, 15);
        if (color <= 6)
        {
            tailWalker->stop();
            state = STEP4;
            clock->reset();
        }
        break;
    case STEP4:

        beginDistance = tailWalker->getDistance();

        while (tailWalker->getDistance() - beginDistance < 18)
        {
            if(tailWalker->getDistance() - beginDistance < 5)
            {
                tailController->rotate(80, 30, false);
            }else if(tailWalker->getDistance() - beginDistance >= 5 &&  tailWalker->getDistance() - beginDistance < 12)
            {
                tailController->rotate(55, 100, false);
            }else 
            {
                tailController->rotate(80, 100, false);
            }
            tailWalker->keepOnMovingForward(15);            
        }
        tailWalker->stop();
        clock->sleep(1000);
        tailController->standUpBody(93);
        state = END;
        break;

    // 終了
    case END:
        return true;
        break;
    }

    return false;
}

bool StairScenario::detectStair()
{
    static bool isLeftMotorStop = false;
    static bool isRightMotorStop = false;

    if (tailWalker->get4msLeftMotorCount())
        isLeftMotorStop = true;
    if (tailWalker->get4msRightMotorCount())
        isRightMotorStop = true;
    if (isLeftMotorStop && isRightMotorStop)
    {
        isLeftMotorStop = false;
        isRightMotorStop = false;
        return true;
    }

    return false;
}