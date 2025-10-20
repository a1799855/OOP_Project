#ifndef KNIGHT_H
#define KNIGHT_H

#include "Unit.h"

class Knight : public Unit {
    public:
        Knight(int id, float pos);
        
        void attack(Entity* target) override;
        void update(float dt) override;
};

#endif