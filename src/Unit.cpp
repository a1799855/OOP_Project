#include <iostream>
#include <cmath>
#include "Entity.h"
#include "Unit.h"
// #include "Economy.h"
// #include "Faction.h"

using namespace std;

Unit::Unit(int id, int hp, float pos, int atk, int range, float atk_cd, float atkTimer, int speed, int cost) : 
    Entity(id, hp, pos), 
    atk(atk), 
    range(range), 
    atk_cd(atk_cd), 
    atkTimer(atkTimer), 
    speed(speed), 
    cost(cost) {}

bool Unit::canAfford(int cost){
    // Once economy & factions are defined
    
    return true;
}

// **Will need to build a target tracking system before using the following
void Unit::attack(Entity* target){
    // If cooldown is over, attack
    if (atkTimer <= 0.0f){    
        if (fabs(target->getPos() - getPos()) <= getRange()){
            // Basic procedure: enemy target is damaged by amount == atk value
            target->takeDamage( getAttack() );
            atkTimer = atk_cd;  // Reset attack cooldown timer
        }
    }
}

void Unit::update(float dt){
    if (isAlive() == false){
        return;
    }

    // IF FIGHTING: ...

    // IF NOT FIGHTING:
    float pos = getPos();       // Get current position of unit
    
    if (pos >= 0.0f && pos <= 1000.0f){
        // If unit is not currently at a base, update to next location
        pos = pos + ( 1.0f * getSpeed() );
        setPos(pos);
    } else if (pos <= 0.0f || pos >= 1000.0f) {
        // **Damage base & do NOT update position
    } else {
        // **Temporary basic debug
        cout << "Class UNIT: Unit gone beyond boundary" << endl;
    }

    // Reduce attack cooldown timer
    atkTimer = atkTimer - 0.1f;     // Make dependent on dt
}


int Unit::getAttack() const {return atk;}
int Unit::getRange() const {return range;}
float Unit::getAttackCooldown() const {return atk_cd;}
float Unit::getAttackTimer() const {return atkTimer;}
int Unit::getSpeed() const {return speed;}
int Unit::getCost() const {return cost;}
void Unit::setAttack(int newAtk) {atk = newAtk;}
void Unit::setCost(int newCost) {cost = newCost;}
void Unit::setAttackTimer(float newTime){atkTimer = newTime;}
void Unit::setHp(int newHP) {hp = newHP;}
