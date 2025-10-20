#include "Base.h"

#include <iostream>

Base::Base(int id, float pos, Faction faction)
    : Entity(id, 200, pos) {}

void Base::update(float dt) {
}
