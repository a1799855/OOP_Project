#include "FactionModifiers.h"
#include "Unit.h"


FactionModifiers::FactionModifiers() 
    : name(""),
      hpMult(1.0f),
      atkMult(1.0f),
      costMult(1.0f),
      peasantUpgraded(false),
      knightUpgraded(false),
      archerUpgraded(false),
      econBuildings(0) {
}

void FactionModifiers::applyUpgrade(Unit* unit, int amount) {
    if (unit == nullptr) {
        return;
    }

    if (hpMult != 1.0f) {
        int currentHp = unit->getHp();
        int newHP = static_cast<int>(currentHp * hpMult);
        unit->setHp(newHP);
    }
    
    if (atkMult != 1.0f) {
        int currentAtk = unit->getAttack();
        int newAtk = static_cast<int>(currentAtk * atkMult);
        unit->setAttack(newAtk);
    }
    
    if (costMult != 1.0f) {
        int currentCost = unit->getCost();
        int newCost = static_cast<int>(currentCost * costMult);
        unit->setCost(newCost);
    }
}