#include <iostream>
#include "Economy.h"

using namespace std;

// Default constructor, factions start with 100 gold and accumulate at 5 gold per timestep
Economy::Economy() : gold(100), incomeRate(5.0f), acc(0.0f) {};

// Provided unit cost is within budget, subtracts cost of unit
void Economy::spend(int cost){
    if (cost <= gold){
        gold = gold - cost;
    }
}

// Apply timestep to increase the gold value by the rate of income
void Economy::update(float dt){ gold = gold + incomeRate; }

void Economy::setIncomeRate(float inc){incomeRate = inc;}   // Set rate of income
int Economy::getGold() const {return gold;}                 // Get current amount of gold
float Economy::getIncomeRate() const {return incomeRate;}   // Get current rate of income