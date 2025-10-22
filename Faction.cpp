#include "Faction.h"
#include "Unit.h"
#include <stdexcept>

Faction::Faction(FactionType type) : factionType(type) {
    modifiers.name = getFactionName();
    initializeFactionBonuses();
}

Faction::Faction() : factionType(Faction1) { //Default constructor, with Faction1 as default.
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
    
    // Base stats from Knight.cpp: HP=70, ATK=12, Cost=60
    float knightHpMult = 1.0f;
    float knightAtkMult = 1.0f;
    float knightCostMult = modifiers.costMult;  // Always use current cost mult
    
    switch (factionType) {
        case Faction1:
            // Knights faction - Knights get HUGE bonuses
            knightHpMult = 1.5f;   // 70 -> 105 HP
            knightAtkMult = 1.4f;  // 12 -> 16-17 ATK
            break;
        
        case Faction2:
            // Economy faction - Normal knights but cheaper
            knightHpMult = 1.0f;
            knightAtkMult = 1.0f;
            break;
        
        case Faction3:
            // Ranged faction - Knights are weaker
            knightHpMult = 0.9f;   // 70 -> 63 HP
            knightAtkMult = 0.9f;  // 12 -> 10-11 ATK
            break;
        
        case Faction4:
            // Balanced faction - Use base modifiers
            knightHpMult = 1.0f;
            knightAtkMult = 1.0f;
            break;
    }
    
    // Apply tech upgrade bonuses if researched
    if (modifiers.knightUpgraded) {
        // Apply the base modifier upgrades that were added in applyTechUpgrade
        knightHpMult *= modifiers.hpMult;   // Includes +15% from tech
        knightAtkMult *= modifiers.atkMult; // Includes +10% from tech
    } else {
        // No tech, just faction bonuses
    }
    
    // Apply modifiers
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
    
    // Base stats from Peasant.cpp: HP=30, ATK=6, Cost=20
    float peasantHpMult = 1.0f;
    float peasantAtkMult = 1.0f;
    float peasantCostMult = modifiers.costMult;  // Always use current cost mult
    
    switch (factionType) {
        case Faction1:
            // Knights faction - Peasants are weaker
            peasantHpMult = 0.9f;   // 30 -> 27 HP
            peasantAtkMult = 0.9f;  // 6 -> 5 ATK
            break;
        
        case Faction2:
            // Economy faction - Peasants are strong (workers)
            peasantHpMult = 1.3f;   // 30 -> 39 HP
            peasantAtkMult = 1.2f;  // 6 -> 7 ATK
            break;
        
        case Faction3:
            // Ranged faction - Normal peasants
            peasantHpMult = 1.0f;
            peasantAtkMult = 1.0f;
            break;
        
        case Faction4:
            // Balanced faction - Use base modifiers
            peasantHpMult = 1.0f;
            peasantAtkMult = 1.0f;
            break;
    }
    
    // Apply tech upgrade bonuses if researched
    if (modifiers.peasantUpgraded) {
        // Apply the base modifier upgrades that were added in applyTechUpgrade
        peasantHpMult *= modifiers.hpMult;   // Includes +15% from tech
        // Cost already reduced in modifiers.costMult
    }
    
    // Apply modifiers
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
            archerHpMult = 1.4f;   // 20 -> 28 HP
            archerAtkMult = 1.6f;  // 9 -> 14-15 ATK
            break;
        
        case Faction4:
            archerHpMult = 1.0f;
            archerAtkMult = 1.0f;
            break;
    }
    
    // Apply tech upgrade bonuses if researched
    if (modifiers.archerUpgraded) {
        // Apply the base modifier upgrades that were added in applyTechUpgrade
        archerAtkMult *= modifiers.atkMult;  // Includes +20% from tech
    }
    
    // Apply modifiers
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
