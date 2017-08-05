#ifndef LOT_H
#define LOT_H

#include "PID.h"

class Lot
{
  public:
    int x, y;
    int speed;
    PID *pid;

    Lot(int x, int y, int speed, float p, float i, float d);
    virtual ~Lot();
};

#endif