#ifndef ENTITY_H
#define ENTITY_H

// Parent of all entities: units, projectiles & bases
// Stores unique ID for each entity, and universal values (HP, pos etc)

class Entity {
  protected:
    int id;            // Unique entity ID
    int hp;            // Health of entity
    float pos;         // Position of entity on the field
    bool alive;        // Tracks alive/dead state of entity
    char playerSymb;   // Symbol of entity for the player
    char enemySymb;    // Symbol of the entity for the enemy

  public:
    Entity(int id, int hp, float pos); 
    virtual ~Entity() = default;

    virtual void update(float dt);       // Defined in children
    virtual void takeDamage(int dmg);    // Decreases HP by attack value

    int getHp() const;                   // Gets HP value
    int getID() const;                   // Gets entity ID
    float getPos() const;                // Gets position of entity
    char getPlayerSymb() const;          // Gets symbol of entity for the player
    char getEnemySymb() const;           // Gets symbol of entity for the enemy
    void setPos(float p);                // Sets the position of the entity
    void setSymb(char a, char b);        // Sets the symbols
    bool isAlive() const;                // Checks whether entity is alive

    virtual void logging_();                      // Logs current state of entity
};

#endif
