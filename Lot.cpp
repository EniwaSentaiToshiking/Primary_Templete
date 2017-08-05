#include "Lot.h"

Lot::Lot(int x, int y, int speed, float p, float i, float d)
{
    this->x = x;
    this->y = y;
    this->speed = speed;
    pid = new PID(p, i, d);
}

Lot::~Lot()
{
}