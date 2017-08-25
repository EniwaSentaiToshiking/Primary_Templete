#include "LotManager.h"

LotManager::LotManager()
{
    current_lot = 0;

    /** 
     *  Lot
     *  @arg (x0, x1, y0, y1, speed, p, i, d)
     *  @con x0 < x1, y0 < y1 
     */
    lot_list[0] = new Lot(0, 0, -10, 10, 30, 0.00, 0.00, 0.00);
    lot_list[1] = new Lot(10, 20, -10, 10, 0, 0.00, 0.00, 0.00);

    mea = new Measure();
}

LotManager::~LotManager()
{
    delete mea;
}

int LotManager::getCurrentLot()
{
    return current_lot;
}

int LotManager::getCurrentLotSpeed()
{
    return lot_list[current_lot]->speed;
}

PID *LotManager::getCurrentLotPID()
{
    return lot_list[current_lot]->pid;
}

void LotManager::changeCurrentLot()
{
    current_lot++;
    ev3_speaker_play_tone(880, 100);
}

bool LotManager::isChangeCurrentLot()
{
    mea->measure();

    if (current_lot < int((sizeof(lot_list) / sizeof(lot_list[0]) - 1)))
    {
        int next_lot = current_lot + 1;

        if (mea->point_x > lot_list[next_lot]->x0 && mea->point_x < lot_list[next_lot]->x1)
            if (mea->point_y > lot_list[next_lot]->y0 && mea->point_y < lot_list[next_lot]->y1)
                return true;
    }

    return false;
}