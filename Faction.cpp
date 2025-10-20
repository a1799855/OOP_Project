#include "Faction.h"
#include <stdexcept>

Faction::Faction(FactionType type) : factionType(type) {
    modifiers.name = getFactionName();
    initializeFactionBonuses();
}

Faction::~Faction() {
    // Cleanup if needed
}

void Faction::initializeFactionBonuses() {
    switch (factionType) {
        case Faction1:
            modifiers.hpMult = 1.2f;
            break;
        
        case Faction2:
            modifiers.costMult = 0.8f;
            break;
        
        case Faction3:
            modifiers.atkMult = 1.12f;
            break;
        
        case Faction4:
            modifiers.hpMult = 1.1f;
            modifiers.atkMult = 1.05f;
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
        modifiers.hpMult *= 1.1f;
    }
    else if (upgradeType == "knight") {
        modifiers.knightUpgraded = true;
        modifiers.atkMult *= 1.2f;
    }
    else if (upgradeType == "archer") {
        modifiers.archerUpgraded = true;
        modifiers.atkMult *= 1.15f;
    }
    else if (upgradeType == "economy") {
        modifiers.econBuildings++;
        modifiers.costMult *= 0.95f;
    }
}

std::string Faction::getFactionName() const {
    switch (factionType) {
        case Faction1: return "Faction1";
        case Faction2: return "Faction2";
        case Faction3: return "Faction3";
        case Faction4: return "Faction4";
        default: return "Unknown";
    }
}