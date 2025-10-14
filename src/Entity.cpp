#include "Entity.h"

Entity::Entity(int id, int hp, float pos)
    : id(id), hp(hp), pos(pos), alive(true) {}

void Entity::update(float dt) {
  // default: do nothing
}

void Entity::takeDamage(int dmg) {
  hp -= dmg;
  if (hp <= 0) {
    hp = 0;
    alive = false;
  }
}

    int Entity::getHp() const { return hp; }
    float Entity::getPos() const { return pos; }
    bool Entity::isAlive() const { return alive; }
