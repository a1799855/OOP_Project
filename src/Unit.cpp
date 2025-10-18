#include <iostream>
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

void Unit::attack(Entity* target){
    if (target->getPos() < getRange()){
        // Basic procedure: enemy target is damaged by amount == atk value
        target->takeDamage( getAttack() );
    }
    // Include cooldown
}

void Unit::update(float dt){
    if (isAlive() == false){
        return;
    }

    // IF FIGHTING: ...

    // IF NOT FIGHTING:
    float pos = getPos();       // Get current position of unit
    
    if (pos != 0.0f || pos != 1000.0f){
        // If unit is not currently at a base, update to next location
        pos = pos + ( 0.1f * getSpeed() );
        setPos(pos);
    } else if (pos == 0.0f || pos == 1000.0f) {
        // **Damage base & do NOT update position
    } else {
        // **Temporary basic debug
        cout << "Class UNIT: Unit gone beyond boundary" << endl;
    }
}


int Unit::getAttack() const {return atk;}
int Unit::getRange() const {return range;}
float Unit::getAttackCooldown() const {return atk_cd;}
float Unit::getAttackTimer() const {return atkTimer;}
int Unit::getSpeed() const {return speed;}
int Unit::getCost() const {return cost;}
