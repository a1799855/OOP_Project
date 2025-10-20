#include "Knight.h"

// Peasent has: HP == 30, Attack == 6, Speed == 1, Cost == 20
// Set atk_cd & atkTimer == 0 for now
Knight::Knight(int id, float pos) : 
    Unit(id, 70, pos, 12, 1, 0, 0, 2, 60) {}

void Knight::attack(Entity* target) {
    Unit::attack(target);
    // Anything specific to knight regarding behaviour
}

void Knight::update(float dt) {
    Unit::update(dt);
    // Anything specific to knight regarding updating
}