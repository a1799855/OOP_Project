#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include "Entity.h"

// Parent for every type of unit: 'Archer', 'Knight', 'Peasant'
// Holds attack, range, speed and cost values

using namespace std;

class Unit : public Entity {
    private:
        int atk;                // Attack power
        int range;              // Distance from which unit can attack enemy
        float atk_cd;           // Attack cooldown
        float atkTimer;         // Time between when unit can attack?
        int speed;              // Speed of unit across battlefield
        int cost;               // Expense of the unit
    public:
        Unit(int id, int hp, float pos, int atk, int range, float atk_cd, float atkTimer, int speed, int cost);
        virtual ~Unit() {};

        int getAttack() const;            // Get 'atk' value
        int getRange() const;             // Get 'range' value
        float getAttackCooldown() const;  // Get 'atk_cd' value
        float getAttackTimer() const;     // Get 'atkTimer' value
        int getSpeed() const;             // Get 'speed' value
        int getCost() const;              // Get 'cost' value

        void setHp(int newHP);              // Sets updated HP value
        void setAttack(int newAtk);         // Sets updated attack value
        void setCost(int newCost);          // Sets updated cost value
        void setAttackTimer(float newTime); // Resets attack timer

        bool canAfford(int cost);
        virtual void attack(Entity* target);    // MANUAL attack function
        virtual void update(float dt) override; // Checks if alive and reduces attack timer

        virtual float getSize() const { return 0.5f; }
        virtual bool canPassAllies() const { return false; }

        //Helper
        bool isFriendlyTo(const Entity& other) const {
            auto otherUnit = dynamic_cast<const Unit*>(&other);
            if (!otherUnit) return false;
            return (getSpeed() > 0) == (otherUnit->getSpeed() > 0);
        }

        void logging();                 // Print entire state of object to file
};

#endif

