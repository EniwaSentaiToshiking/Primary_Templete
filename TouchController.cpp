#include "TouchController.h"

TouchController::TouchController()
{
    state = false;
    prev_state = false;
    touchSensor = new TouchSensor(PORT_1);
}

TouchController::~TouchController()
{
    state = false;
    prev_state = false;
    delete touchSensor;
}

bool TouchController::isPressed()
{
    state = touchSensor->isPressed();

    if (prev_state != state)
    {
        prev_state = state;

        if (!state)
            return true;
    }

    return false;
}