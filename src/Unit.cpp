#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include "Entity.h"
#include "Unit.h"
#include "Debug.h"

using namespace std;

Unit::Unit(int id, int hp, float pos, int atk, int range, float atk_cd, float atkTimer, int speed, int cost) : 
    Entity(id, hp, pos), 
    atk(atk), 
    range(range), 
    atk_cd(atk_cd), 
    atkTimer(atkTimer), 
    speed(speed), 
    cost(cost) {}

// MANUAL: Individual attack function
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

// Updates state of unit
void Unit::update(float dt){
    if (isAlive() == false){
        return;
    }

    // Reduce attack cooldown timer
    atkTimer -= dt;
    if (atkTimer < 0.f) atkTimer = 0.f;
}

// Checks whether unit is friendly or not
bool Unit::isFriendlyTo(const Entity& other) const {
            auto otherUnit = dynamic_cast<const Unit*>(&other);
            if (!otherUnit) return false;
            return (getSpeed() > 0) == (otherUnit->getSpeed() > 0);
}


int Unit::getAttack() const {return atk;}                       // Get attack value
int Unit::getRange() const {return range;}                      // Get range value
float Unit::getAttackCooldown() const {return atk_cd;}          // Get time delay on attacks
float Unit::getAttackTimer() const {return atkTimer;}           // Get time until next attack
int Unit::getSpeed() const {return speed;}                      // Get speed of unit
int Unit::getCost() const {return cost;}                        // Get cost of unit

void Unit::setAttack(int newAtk) {atk = newAtk;}                // Set new attack value
void Unit::setCost(int newCost) {cost = newCost;}               // Set new cost value
void Unit::setAttackTimer(float newTime){atkTimer = newTime;}   // Reset attack timer
void Unit::setHp(int newHP) {hp = newHP;}                       // Set new HP value


// Create log to output entire state of object
void Unit::logging(){
    // If file exists, open and delete content (trunc)
    // If file doesn't exist, create it 
    ofstream file("log_Unit.txt", ios::out | ios::trunc);

    // Exit function & output to debugger if log file couldn't open
    if (!file){
        Debug::info("Could not open log file in Unit");
        return;
    }

    file << "ID: " << getID() << endl;
    file << "HP: " << getHp() << endl;
    file << "Position: " << getPos() << endl;
    file << "Alive? " << isAlive() << endl;
    file << "Attack: " << atk << endl;
    file << "Range: " << range << endl;
    file << "Attack Cooldown: " << atk_cd << endl;
    file << "Attack Timer: " << atkTimer << endl;
    file << "Speed: " << speed << endl;
    file << "Cost: " << cost << endl;

    file.close();
    Debug::info("Successfully wrote to Unit log file");
}