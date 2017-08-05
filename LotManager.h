#ifndef LOTMANAGER_H
#define LOTMANAGER_H

#include "Lot.h"
#include "ev3api.h"

class LotManager
{

  private:
    int current_lot;
    Lot *lot_list[2];

  public:
    LotManager();
    virtual ~LotManager();

    int getCurrentLot();
    int getCurrentLotSpeed();
    PID *getCurrentLotPID();
    void changeCurrentLot();
};

#endif