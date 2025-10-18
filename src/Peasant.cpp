#include "Peasant.h"

// Peasent has: HP == 30, Attack == 6, Speed == 1, Cost == 20
// Set atk_cd & atkTimer == 0 for now
Peasant::Peasant(int id, float pos) : 
    Unit(id, 30, pos, 6, 1, 0, 0, 1, 20) {}

void Peasant::attack(Entity* target) {
    Unit::attack(target);
    // Anything specific to peasant regarding behaviour
}

void Peasant::update(float dt) {
    Unit::update(dt);
    // Anything specific to peasant regarding updating
}