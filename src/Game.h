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

enum class UnitType { Peasant, Knight, Archer };
enum class GameState { StartMenu, FactionSelect, MainGameScreen, UpgradeMenu, GameOver };

struct Config {
    int laneCols = 120; // How many "."s appear
    float laneLen = 120.0f; // 120.0 is more sensible than previous 1000.0, even the idea of replacing with an int has floated around thought that would be less scalable
    float dt = 0.25f; // Time per in-game tick. Would need to be replaced eventually. Maybe cap to 60 FPS '1.0f / 60.0f' / 0.0167s
};

class Game {
public:
    Game();

    // Advances game by one tick
    void update();

    // Resets the game
    // void reset();

    mt19937 rng{random_device{}()};

    void spawnPeasant(bool isPlayer);

    // GameState
    GameState getState() const { return state; }
    void setState(GameState m) { state = m; }
    bool isGameOver() const { return state == GameState::GameOver ; }
    // Default factions. Basically a safety net
    FactionType playerFaction = FactionType::Faction1;
    FactionType enemyFaction = FactionType::Faction2;
    
    void selectPlayerFaction(FactionType f);
    void setFactions(FactionType playerPick, FactionType enemyPick);

    // Getters
    // E.g. to see gold count, need game.getEconomy().getGold()
    const vector<Entity*>& getPlayerEntities() const { return playerEntities; }
    const vector<Entity*>& getEnemyEntities() const { return enemyEntities; }
    const Base& getPlayerBase() const { return playerBase; }
    const Base& getEnemyBase() const { return enemyBase; }
    const Economy& getPlayerEconomy() const { return playerEcon; } // Allows to see economy
    const Economy& getEnemyEconomy() const { return enemyEcon; }
    Economy& usePlayerEconomy() { return playerEcon; }
    Economy& useEnemyEconomy() { return enemyEcon; }
    int getUniqueID();
    void setUniqueID(int i);
    void playerSpawn(UnitType uType);
    void enemySpawn(UnitType uType);
    void AIController();
    const Config& getConfig() const { return cfg; }
    string winnerText() const;

// Split purely for organisational purposes
private:
    // Internal functions
    GameState state = GameState::MainGameScreen;
    int uniqueID = 2;
    float colToWorld_(int col) const;
    int worldToCol_(float x) const;
    vector<Entity*> playerEntities;  // **********
    vector<Entity*> enemyEntities;   // **********
    void updateProjectiles_(float dt);
    vector<Projectile> projectiles;

    // Game properties
    Config cfg{};
    Economy playerEcon;
    Economy enemyEcon;
    Base playerBase;
    Base enemyBase;
};

#endif
