#ifndef LOTMANAGER_H
#define LOTMANAGER_H

#include "Lot.h"
#include "Measure.h"
#include "ev3api.h"
#include "Logger.h"

class LotManager
{

  private:
    int current_lot;
    Lot *lot_list[8];
    Measure *mea;
    Logger *posx_logger;
    Logger *posy_logger;

  public:
    LotManager();
    virtual ~LotManager();

    int getCurrentLot();
    int getCurrentLotSpeed();
    PID *getCurrentLotPID();
    void changeCurrentLot();
    bool isChangeCurrentLot();
    void courseR();
    void courseL();
};

#endif