#ifndef KNIGHT_H
#define KNIGHT_H

#include "Unit.h"

// Creates Knight unit

class Knight : public Unit {
    public:
        Knight(int id, float pos, int speed);
        bool canPassAllies() const override { return true; }    // Can overtake teammates
};

#endif