#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include "Entity.h"
//#include "Faction.h"

using namespace std;

class Unit : public Entity {
    private:
        int atk;                // Attack power
        int range;              // Distance from which unit can attack enemy
        float atk_cd;           // Attack cooldown?
        float atkTimer;         // Time between when unit can attack?
        int speed;              // Speed of unit across battlefield
        int cost;               // Expense of the unit
        // Faction* faction;    // Will require addition of 'faction'
    public:
        Unit(int id, int hp, float pos, int atk, int range, float atk_cd, float atkTimer, int speed, int cost);
        virtual ~Unit() {};

        int getAttack() const;            // Get 'atk' value
        int getRange() const;             // Get 'range' value
        float getAttackCooldown() const;  // Get 'atk_cd' value
        float getAttackTimer() const;     // Get 'atkTimer' value
        int getSpeed() const;             // Get 'speed' value
        int getCost() const;              // Get 'cost' value

        void setHp(int newHP);            // *** Why here & not in entity?
        void setAttack(int newAtk);
        void setCost(int newCost);
        void setAttackTimer(float newTime);
    
        bool canAfford(int cost);
        virtual void attack(Entity* target);
        virtual void update(float dt) override;

        virtual float getSize() const { return 0.5f; }
};

#endif

