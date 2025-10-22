#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entity.h"
class Projectile : public Entity {
private:
    int damage; // Damage should come from archer shooting projectile
    int targetId;
    float speed; // +ve for left to right, -ve for right to left
    float travelDistance; // How far the projectile has travelled
    float maxTravelDistance; // How far the projectile CAN travel. Temporary: will be set by 'int range' in archer unit in future.
public:
    explicit Projectile(int id, float pos, float speed, int damage, int targetId, float maxTravelDistance);
    
    void update(float dt) override;

    int getDamage() const;
    int getTarget() const;
    float getSpeed() const;
    float getTravelDistance() const;
    float getMaxTravelDistance() const;
};

#endif