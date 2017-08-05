#include "LotManager.h"

LotManager::LotManager()
{
    current_lot = 0;

    lot_list[0] = new Lot(0, 0, 30, 0.00, 0.00, 0.00);
    lot_list[1] = new Lot(100, 0, 0, 0.00, 0.00, 0.00);
}

LotManager::~LotManager()
{
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
    if (current_lot < int((sizeof(lot_list) / sizeof(lot_list[0]) - 1)))
    {
        current_lot++;
        ev3_speaker_play_tone(880, 100);
    }
}