#include "BTTask.h"

BTTask::BTTask()
{

    bt = ev3_serial_open_file(EV3_SERIAL_BT);
    assert(bt != NULL);
}

BTTask::~BTTask()
{
    fclose(bt);
}

bool BTTask::isStart()
{
    bool start = false;

    uint8_t c = fgetc(bt);

    if (c == CMD_START)
        start = true;

    fputc(c, bt);

    return start;
}
