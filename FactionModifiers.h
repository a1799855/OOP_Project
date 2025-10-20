#ifndef FACTIONMODIFIERS_H
#define FACTIONMODIFIERS_H

#include <string>


#include "Unit.h"

class FactionModifiers {
public:
    std::string name;
    float hpMult;
    float atkMult;
    float costMult;
    bool peasantUpgraded;
    bool knightUpgraded;
    bool archerUpgraded;
    int econBuildings;

    FactionModifiers();


    void applyUpgrade(Unit* unit, int amount);
};

#endif