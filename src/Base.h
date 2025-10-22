#ifndef BASE_H
#define BASE_H

#include "Entity.h"

class Base : public Entity {
    public:
        //Base(int id, float pos, Faction faction);
        Base(int id, float pos);

        void update(float dt) override;
};

#endif
