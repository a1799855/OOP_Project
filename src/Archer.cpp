#include <cmath>
#include <iostream>
#include "Archer.h"

// Archer has: HP == 20, Attack == 9, Speed == 1, Cost == 30
// Set atk_cd & atkTimer == 0 for now
Archer::Archer(int id, float pos) : 
    Unit(id, 20, pos, 9, 6, 0, 0, 1, 30) {}

void Archer::update(float dt) {
    Unit::update(dt);
    // Anything specific to archer regarding updating
}

Projectile Archer::fireProjectile(Entity* target){
    // Finds speed and direction of projectile (**change magnitude)
    float speed;
    if ( getPos() < target->getPos() ){
        speed = 4.0f;
    } else if ( getPos() > target->getPos() ){
        speed = -4.0f;
    } else {
        cout << "ARCHER: Identical Position Error" << endl;
    }

    int iden = 1000;

    // Use 'attack' value as 'damage'
    return Projectile( iden, getPos(), speed, getAttack(), target->getID(),  getRange() );
}

void Archer::attack(Entity* target) {
    if (getAttackTimer() <= 0.0f){    
        if (fabs(target->getPos() - getPos()) <= getRange()){
            Projectile p = fireProjectile(target);
            // Now add to 'projectile manager' (in Game class?)
            // Make to not shoot if archer is in same position as enemy unit
            setAttackTimer( getAttackCooldown() );  // Reset attack cooldown timer
        }
    }
}
