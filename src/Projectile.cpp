#include <cmath>
#include "Projectile.h"
#include "Debug.h"

using namespace std;

// Faction should be tracked with archer spawnProjectile() function.
Projectile::Projectile(int id, float pos, float speed, int damage, int targetId,  float maxTravelDistance) :
    Entity(id, 1, pos),
    damage(damage),
    targetId(targetId),
    speed(speed),
    travelDistance(0.f),
    maxTravelDistance(maxTravelDistance) {}

void Projectile::update(float dt) {
    // +ve for left to right, -ve for right to left
    if (dt > 0.1f) dt = 0.1f; // Local clamp. For when delta time is properly set up
    const float dx = speed * dt;
    pos += dx;
    travelDistance += abs(dx); // Magnitude. Used for tracking projectile lifespan

    // Kills the projectile if it exceeds projectile range
    if ( travelDistance >= maxTravelDistance ) {
        alive = false;
    }
    // Kills projectile if it leaves the map. Map currently not defined. Will be in Game.h
    // if ( pos < 0.f || pos > 1000.f ) {
    //     alive = false;
    // }
}

int Projectile::getDamage() const { return damage; }
int Projectile::getTarget() const { return targetId; }
float Projectile::getSpeed() const { return speed; }
float Projectile::getTravelDistance() const { return travelDistance; }
float Projectile::getMaxTravelDistance() const { return maxTravelDistance; }