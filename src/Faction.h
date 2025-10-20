#ifndef FACTION_H
#define FACTION_H

#include "FactionModifiers.h"
#include <string>

enum FactionType {
    Faction1,
    Faction2,
    Faction3,
    Faction4,
};

class Faction {
private:
    FactionType factionType;
    FactionModifiers modifiers;

    
    void initializeFactionBonuses();

public:
    explicit Faction(FactionType type);

    ~Faction();

    FactionType getFactionType() const;
    FactionModifiers& getModifiers();
    const FactionModifiers& getModifiers() const;

    
    void applyTechUpgrade(const std::string& upgradeType);

    
    std::string getFactionName() const;
};

#endif