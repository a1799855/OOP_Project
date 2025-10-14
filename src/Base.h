#ifndef BASE_H
#define BASE_H

#include "Entity.h"
// #include "Faction.h"

class Base : public Entity {
 public:
  Base(int id, float pos); //Faction faction (for faction design included later)

      void
      update(float dt) override;
};

#endif
