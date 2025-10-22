#ifndef KNIGHT_H
#define KNIGHT_H

#include "Unit.h"

class Knight : public Unit {
    public:
        Knight(int id, float pos, int speed);
        bool canPassAllies() const override { return true; }
};

#endif