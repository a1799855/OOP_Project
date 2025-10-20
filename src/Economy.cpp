#include <iostream>
#include "Economy.h"

using namespace std;

Economy::Economy() : gold(100), incomeRate(5.0f), acc(0.0f) {};

void Economy::spend(int cost){
    // Assumes canAfford function has already been used
    if (cost > gold){
        cout << "ECONOMY: Can't afford" << endl;
    }
    gold = gold - cost;
}

void Economy::update(float dt){
    // Will require refinement to fit together with dt update
    gold = gold + incomeRate;
}

void Economy::setIncomeRate(float inc){incomeRate = inc;}
int Economy::getGold(){return gold;}
float Economy::getIncomeRate(){return incomeRate;}