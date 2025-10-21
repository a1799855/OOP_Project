#ifndef ARCHER_H
#define ARCHER_H

#include "Unit.h"
#include "Projectile.h"

class Archer : public Unit {
    public:
        Archer(int id, float pos);

        void attack(Entity* target) override;
        Projectile fireProjectile();
        void update(float dt) override;
};

#endif