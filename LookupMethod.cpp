#include "LookupMethod.h"

LookupMethod::LookupMethod(BalancingWalker *balancingWalker, TailController *tailController)
{
    clock = new Clock();
    sonarAlert = new SonarAlert();
    this->balancingWalker = balancingWalker;
    this->tailController = tailController;
    tailWalker = new TailWalker();
}

LookupMethod::~LookupMethod() {}

bool LookupMethod::run()
{

    static State state = TRANSITION_TO_TAIL_RUN;

    switch (state)
    {
    case TRANSITION_TO_TAIL_RUN:
        tailWalker->reset_distance();
        tailController->rotate(85, 50, false);
        if (clock->now() < 1000)
        {
            balancingWalker->stopRun();
        }
        else
        {
            tailController->rotate(85, 50, false);
            tailWalker->balance();
            state = FIRST_PASS_GATE;
        }
        break;

    case FIRST_PASS_GATE:
        tailController->bendBody(70);
        tailWalker->forward(10, 25);
        state = SECOND_PASS_GATE;
        break;

    case SECOND_PASS_GATE:
        tailController->standUpBody(90);
        tailWalker->leftTurn(183);
        while (!isGate(10))
        {
            tailWalker->keepOnMovingForward(5);
        }
        tailWalker->stop();
        tailController->bendBody(70);
        tailWalker->forward(10, 25);
        state = THIRD_PASS_GATE;

    case THIRD_PASS_GATE:
        tailController->standUpBody(90);
        tailWalker->leftTurn(183);
        while (!isGate(10))
        {
            tailWalker->keepOnMovingForward(5);
        }
        tailWalker->stop();
        tailController->bendBody(70);
        tailWalker->forward(10, 25);
        state = SEARCH_LINE;
        break;

    case SEARCH_LINE:
        tailController->standUpBody(93);
        state = LINE_TRACE;
        break;
        
    case LINE_TRACE:
        return true;
        break;
    }

    return false;
}

bool LookupMethod::isGate(int distance)
{
    return sonarAlert->isAlert(distance);
}