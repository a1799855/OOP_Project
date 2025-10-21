#include "Faction.h"
#include "Unit.h"
#include <stdexcept>

Faction::Faction(FactionType type) : factionType(type) {
    modifiers.name = getFactionName();
    initializeFactionBonuses();
}

Faction::~Faction() {
}

void Faction::initializeFactionBonuses() {
    modifiers.hpMult = 1.0f;
    modifiers.atkMult = 1.0f;
    modifiers.costMult = 1.0f;
    
    switch (factionType) {
        case Faction1:
            modifiers.knightUpgraded = true;
            modifiers.econBuildings = 0;
            break;
        
        case Faction2:
            modifiers.costMult = 0.8f;
            modifiers.econBuildings = 2;
            break;
        
        case Faction3:
            modifiers.archerUpgraded = true;
            modifiers.econBuildings = 0;
            break;
        
        case Faction4:
            modifiers.hpMult = 1.1f;
            modifiers.atkMult = 1.05f;
            modifiers.econBuildings = 1;
            break;
    }
}

FactionType Faction::getFactionType() const {
    return factionType;
}

FactionModifiers& Faction::getModifiers() {
    return modifiers;
}

const FactionModifiers& Faction::getModifiers() const {
    return modifiers;
}

void Faction::applyTechUpgrade(const std::string& upgradeType) {
    if (upgradeType == "peasant") {
        modifiers.peasantUpgraded = true;
    }
    else if (upgradeType == "knight") {
        modifiers.knightUpgraded = true;
    }
    else if (upgradeType == "archer") {
        modifiers.archerUpgraded = true;
    }
    else if (upgradeType == "economy") {
        modifiers.econBuildings++;
        modifiers.costMult *= 0.95f;
    }
}

void Faction::applyKnightModifiers(Unit* unit) {
    if (unit == nullptr) {
        return;
    }
    
    
    float knightHpMult = 1.0f;
    float knightAtkMult = 1.0f;
    float knightCostMult = modifiers.costMult;
    
    switch (factionType) {
        case Faction1:
            knightHpMult = 1.5f;
            knightAtkMult = 1.4f;  
            break;
        
        case Faction2:
            knightHpMult = 1.0f;
            knightAtkMult = 1.0f;
            break;
        
        case Faction3:
            knightHpMult = 0.9f;   
            knightAtkMult = 0.9f;
            break;
        
        case Faction4:
            knightHpMult = modifiers.hpMult;
            knightAtkMult = modifiers.atkMult;
            break;
    }
    
    if (modifiers.knightUpgraded) {
        knightHpMult *= 1.15f;  
        knightAtkMult *= 1.2f;  
    }
    
    
    int newHp = static_cast<int>(unit->getHp() * knightHpMult);
    int newAtk = static_cast<int>(unit->getAttack() * knightAtkMult);
    int newCost = static_cast<int>(unit->getCost() * knightCostMult);
    
    unit->setHp(newHp);
    unit->setAttack(newAtk);
    unit->setCost(newCost);
}

void Faction::applyPeasantModifiers(Unit* unit) {
    if (unit == nullptr) {
        return;
    }
    float peasantHpMult = 1.0f;
    float peasantAtkMult = 1.0f;
    float peasantCostMult = modifiers.costMult;
    
    switch (factionType) {
        case Faction1:
            peasantHpMult = 0.9f;
            peasantAtkMult = 0.9f; 
            break;
        
        case Faction2:
            peasantHpMult = 1.3f; 
            peasantAtkMult = 1.2f; 
            break;
        
        case Faction3:
            peasantHpMult = 1.0f;
            peasantAtkMult = 1.0f;
            break;
        
        case Faction4:
            peasantHpMult = modifiers.hpMult;
            peasantAtkMult = modifiers.atkMult;
            break;
    }
    

    if (modifiers.peasantUpgraded) {
        peasantHpMult *= 1.15f;
        peasantCostMult *= 0.9f;
    }

    int newHp = static_cast<int>(unit->getHp() * peasantHpMult);
    int newAtk = static_cast<int>(unit->getAttack() * peasantAtkMult);
    int newCost = static_cast<int>(unit->getCost() * peasantCostMult);
    
    unit->setHp(newHp);
    unit->setAttack(newAtk);
    unit->setCost(newCost);
}

void Faction::applyArcherModifiers(Unit* unit) {
    if (unit == nullptr) {
        return;
    }

    float archerHpMult = 1.0f;
    float archerAtkMult = 1.0f;
    float archerCostMult = modifiers.costMult;
    
    switch (factionType) {
        case Faction1:
            archerHpMult = 0.9f;  
            archerAtkMult = 0.9f; 
            break;
        
        case Faction2:
            archerHpMult = 1.0f;
            archerAtkMult = 1.0f;
            break;
        
        case Faction3:
            archerHpMult = 1.4f;  
            archerAtkMult = 1.6f; 
            break;
        
        case Faction4:
            archerHpMult = modifiers.hpMult;
            archerAtkMult = modifiers.atkMult;
            break;
    }

    if (modifiers.archerUpgraded) {
        archerAtkMult *= 1.25f;
    }

    int newHp = static_cast<int>(unit->getHp() * archerHpMult);
    int newAtk = static_cast<int>(unit->getAttack() * archerAtkMult);
    int newCost = static_cast<int>(unit->getCost() * archerCostMult);
    
    unit->setHp(newHp);
    unit->setAttack(newAtk);
    unit->setCost(newCost);
}

std::string Faction::getFactionName() const {
    switch (factionType) {
        case Faction1: return "Westerland♞ "; // "Knights Faction"
        case Faction2: return "Easton💰 "; // "Economy Faction"
        case Faction3: return "Southos🏹 "; // "Ranged Faction"
        case Faction4: return "Northia⚖️ "; // "Balanced Faction"
        default: return "Unknown";
    }
}
