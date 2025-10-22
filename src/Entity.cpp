#include <fstream>
#include <string>
#include "Debug.h"
#include "Entity.h"

// Assigns default ' ' symbol for all entities
Entity::Entity(int id, int hp, float pos)
    : id(id), hp(hp), pos(pos), alive(true), playerSymb(' '), enemySymb(' ') {}

// Defined in children
void Entity::update(float dt) {}

// Decreases HP by a value equal to the attack value of the enemy entity
void Entity::takeDamage(int dmg) {
  hp -= dmg;
  if (hp <= 0) {
    hp = 0;
    alive = false;
  }
}

int Entity::getHp() const { return hp; }
int Entity::getID() const { return id; }
float Entity::getPos() const { return pos; }
char Entity::getPlayerSymb() const { return playerSymb; }
char Entity::getEnemySymb() const { return enemySymb; }
void Entity::setPos(float p){pos = p;}
void Entity::setSymb(char a, char b){playerSymb = a; enemySymb = b;}
bool Entity::isAlive() const { return alive; }

// Create log to output entire state of object
void Entity::logging_(){
    // If file exists, open and delete content (trunc)
    // If file doesn't exist, create it 
    ofstream file("log_Entity.txt", ios::out | ios::trunc);

    // Exit function & output to debugger if log file couldn't open
    if (!file){
        Debug::info("Could not open log file in Entity");
        return;
    }

    file << "ID: " << getID() << endl;
    file << "HP: " << getHp() << endl;
    file << "Position: " << getPos() << endl;
    file << "Alive? " << isAlive() << endl;

    file.close();
    Debug::info("Successfully wrote to Entity log file");
}