#ifndef PEASANT_H
#define PEASANT_H

#include "Unit.h"

class Peasant : public Unit {
    public:
        Peasant(int id, float pos);
        
        void attack(Entity* target) override;
        void update(float dt) override;
};

#endif