#ifndef ARCHER_H
#define ARCHER_H

#include "Unit.h"
#include "Projectile.h"

class Archer : public Unit {
    public:
        Archer(int id, float pos, int speed);

        void update(float dt) override;
        Projectile fireProjectile(Entity* target);
        void attack(Entity* target) override;
};

#endif