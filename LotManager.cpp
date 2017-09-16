#include "LotManager.h"

LotManager::LotManager(int flag)
{
    current_lot = 0;

    /**
     *  Lot
     *  @arg (x0, x1, y0, y1, speed, p, i, d)
     *  @con x0 < x1, y0 < y1
     */

    if(flag==0){
        courseR();
    }else{
        courseL();
    }

    mea = new Measure();

}

LotManager::~LotManager()
{
    delete mea;
}

void LotManager::courseR()
{
    lot_list[0] = new Lot(0, 180, -30, 30, 140, 0.4, 0.01, 0.03);
    lot_list[1] = new Lot(180, 200, -30, 30, 110, 1.1, 0.01, 0.07);
    lot_list[2] = new Lot(0, 180, -210, -10, 110, 0.9, 0.02, 0.07);
    lot_list[3] = new Lot(100, 140, -100, -50, 100, 1.5, 0.01, 0.05);
    lot_list[4] = new Lot(75, 125, -150, -100, 110, 0.9, 0.01, 0.04);
    lot_list[5] = new Lot(0, 250, -250, -200, 140, 0.4, 0.01, 0.03);
    lot_list[6] = new Lot(0, 250, -430, -375, 30, 0.86, 0.00, 0.04);
    lot_list[7] = new Lot(170, 220, -430, 0, 20, 0.4, 0.00, 0.03);
}

void LotManager::courseL()
{
    lot_list[0] = new Lot(0, 180, -30, 30, 140, 0.4, 0.01, 0.03);
    lot_list[1] = new Lot(180, 220, -30, 30, 110, 1.4, 0.01, 0.05);
    lot_list[2] = new Lot(150, 200, -50, -20, 110, 0.9, 0.01, 0.04);
    lot_list[3] = new Lot(0, 30, -100, -75, 100, 1.5, 0.01, 0.06);
    lot_list[4] = new Lot(50, 100, -200, -75, 100, 1.4, 0.01, 0.06);
    lot_list[5] = new Lot(0, 250, -250, -200, 140, 0.4, 0.01, 0.03);
    lot_list[6] = new Lot(0, 250, -400, -360, 60, 0.86, 0.00, 0.04);
    lot_list[7] = new Lot(160, 250, -700, 0, 20, 0.4, 0.00, 0.03);
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

        if (mea->point_x > lot_list[next_lot]->x0 && mea->point_x < lot_list[next_lot]->x1){
            if (mea->point_y > lot_list[next_lot]->y0 && mea->point_y < lot_list[next_lot]->y1){
                ev3_speaker_play_tone (480,100);
                return true;
            }
        }
    }

    return false;
}
