#ifndef ARCHER_H
#define ARCHER_H

#include "Unit.h"
#include "Projectile.h"

// Create Archer unit

class Archer : public Unit {
    public:
        Archer(int id, float pos, int speed);

        Projectile fireProjectile(Entity* target);  // Generate arrow 'projectile'
        void attack(Entity* target) override;       // Fire arrow when in range
};

#endif