#ifndef ENTITY_H
#define ENTITY_H

class Entity {
 protected:
    int id;
    int hp;
    float pos;    // MUST be protected for Projectile::update() to run
    bool alive;

 public:
    Entity(int id, int hp, float pos); 
    virtual ~Entity() = default;

    virtual void update(float dt);     
    virtual void takeDamage(int dmg);
    virtual void movement(float pos);  

    int getHp() const;
    int getID() const;
    float getPos() const;
    void setPos(float p);
    bool isAlive() const;
};

#endif
