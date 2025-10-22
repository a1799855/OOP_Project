#ifndef PEASANT_H
#define PEASANT_H

#include "Unit.h"

// Creates Peasant unit

class Peasant : public Unit {
    public:
        Peasant(int id, float pos, int speed);
};

#endif