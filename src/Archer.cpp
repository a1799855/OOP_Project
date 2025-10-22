#include <cmath>
#include <iostream>
#include "Archer.h"
#include "Debug.h"

// Archer has: HP == 20, Attack == 9, Speed == 1, Cost == 30
// Set atk_cd & atkTimer == 0 for now
Archer::Archer(int id, float pos, int speed) : 
    Unit(id, 20, pos, 9, 6, 0, 0, speed, 30) {setSymb('}','{');}

// Generate projectile with correct speed and direction
Projectile Archer::fireProjectile(Entity* target){
    // Finds speed and direction of projectile (**change magnitude)
    float speed;
    if ( getPos() < target->getPos() ){
        speed = 4.0f;
    } else if ( getPos() > target->getPos() ){
        speed = -4.0f;
    }

    int iden = 1000;    // Assign fixed ID

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
