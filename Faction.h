#ifndef FACTION_H
#define FACTION_H

#include "FactionModifiers.h"
#include <string>

enum FactionType {
    Faction1, // Westerland
    Faction2, // Easton
    Faction3, // Southos
    Faction4 // Northia
};

class Faction {
private:
    FactionType factionType;
    FactionModifiers modifiers;

    void initializeFactionBonuses();

public:
    explicit Faction(FactionType type);

    // Added for upgrades
    Faction();

    ~Faction();

    FactionType getFactionType() const;
    FactionModifiers& getModifiers();
    const FactionModifiers& getModifiers() const;

    // Apply technology upgrades
    void applyTechUpgrade(const std::string& upgradeType);

    // Apply modifiers to specific unit types
    void applyKnightModifiers(Unit* unit);
    void applyPeasantModifiers(Unit* unit);
    void applyArcherModifiers(Unit* unit);
    std::string getFactionName() const;
};

#endif