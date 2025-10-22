#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <random>
#include "Base.h"
#include "Projectile.h"
#include "Unit.h"
#include "Faction.h"
#include "Economy.h"
#include "Faction.h"
using namespace std;

// Store unit and game state variations for ease of use
enum class UnitType { Peasant, Knight, Archer };
enum class GameState { StartMenu, FactionSelect, MainGameScreen, UpgradeMenu, GameOver };

// Store essential details for rendering
struct Config {
    int laneCols = 120;         // How many "."s appear
    float laneLen = 120.0f;     // 120.0 is more sensible than previous 1000.0
    float dt = 0.25f;           // Time per in-game tick. Maybe cap to 60 FPS '1.0f / 60.0f' / 0.0167s
};


// Controls entire game, updating every entity, tracking movements, managing gamestate

class Game {
    public:
        Game();
        ~Game();

        // Advances game by one tick
        void update();

        // Resets the game
        // void reset();

        mt19937 rng{random_device{}()};

        // COMBAT & MOTION
        // Manages player & combat movements and attacks
        Entity* closestEnemy(Entity* attacker, bool isPlayerUnit);  // Finds closest enemy entity
        void playerCombatStep();                                    // Checks & attacks enemy
        void enemyCombatStep();                                     // Checks & attacks player
        void movementStep();                                        // Moves entities
        void spawnPeasant(bool isPlayer);                           

        int getPlayerUnitCost(UnitType t) const;                    // Get cost for each player unit
        // int getEnemyUnitCost(UnitType t) const;                  // Get cost fo each enemy unit


        // GAMESTATE
        GameState getState() const { return state; }                // Gets state of game
        void setState(GameState m) { state = m; }                   // Controls state of game
        bool isGameOver() const { return state == GameState::GameOver ; }
        // Default factions. Basically a safety net
        // FactionType playerFaction = FactionType::Faction1;
        // FactionType enemyFaction = FactionType::Faction2;

        // FACTION
        Faction playerFaction;                                              // Establishes faction for player
        Faction enemyFaction;                                               // Establishes faction for enemy
        Faction& getPlayerFaction() { return playerFaction; }               // Access & change player faction
        Faction& getEnemyFaction() { return enemyFaction; }                 // Access & change enemy faction
        const Faction& getPlayerFaction() const { return playerFaction; }   // Access player faction
        const Faction& getEnemyFaction() const { return enemyFaction; }     // Access enemy faction
        
        void selectPlayerFaction(FactionType f);                            // Implements user input of faction choice
        void setFactions(FactionType playerPick, FactionType enemyPick);    // Sets player & enemy factions

        // GETTERS & SETTERS
        const vector<Entity*>& getPlayerEntities() const { return playerEntities; } // Access player entities
        const vector<Entity*>& getEnemyEntities() const { return enemyEntities; }   // Access enemy entities
        const Base& getPlayerBase() const { return playerBase; }                    // Access player base
        const Base& getEnemyBase() const { return enemyBase; }                      // Access enemy base
        const Economy& getPlayerEconomy() const { return playerEcon; }              // Access player economy
        const Economy& getEnemyEconomy() const { return enemyEcon; }                // Access enemy economy
        Economy& usePlayerEconomy() { return playerEcon; }                          // Access & change player economy
        Economy& useEnemyEconomy() { return enemyEcon; }                            // Access & change user economy
        int getUniqueID();                                                          // Get unique ID for new entities
        void setUniqueID(int i);                                                    // Update ID to keep unique

        // SPAWN UNITS
        void playerSpawn(UnitType uType);                   // Spawn player unit of choice
        void enemySpawn(UnitType uType);                    // Spawn enemy unit of choice
        void AIController();                                // Controls spawn of enemy units

        // OTHER
        const Config& getConfig() const { return cfg; }     // Render configuration details
        string winnerText() const;
        void allUnitlogging();

    // Split purely for organisational purposes
    private:
        GameState state = GameState::MainGameScreen;    

        // INTERNAL VECTORS
        vector<Entity*> playerEntities;         // Creates vector for player entities
        vector<Entity*> enemyEntities;          // Creates vector for enemy entities
        vector<Projectile> projectiles;         // Creates vector for projectiles

        // INTERNAL FUNCTIONS
        float colToWorld_(int col) const;
        int worldToCol_(float x) const;
        float stopBefore_(float blockerPos, float selfSize, float blockerSize, bool positiveSpeed) const;
        void resolveVsEntity_(Unit& u, Entity& target, float /*size*/, float dt);
        int uniqueID = 2;       // Holds value of unique ID assigned to each entity
        
        
        void updateProjectiles_(float dt);      // Increments motion of projectiles
        

        // GAME PROPERTIES
        Config cfg{};           // Defines render configuration details
        Economy playerEcon;     // Creates economy for player
        Economy enemyEcon;      // Creates economy for enemy
        Base playerBase;        // Creates base for player
        Base enemyBase;         // Creates base for enemy
};

#endif
