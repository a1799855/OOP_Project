#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <random>
#include "Base.h"
#include "Projectile.h"
#include "Economy.h"
#include "Faction.h"
using namespace std;

//enum class Faction { Player, Enemy }; // Other factions to be added later. Ideally there would be 4 factions, player would choose one and the enemy will be one of the other three
enum class UnitType { Peasant }; // Basic unit created for testing and prototype
enum class GameState { MainGameScreen, GameOver }; // StartMenu, FactionSelect, and BuildMenu(/UpgradeMenu) to be added later

struct Config {
    int laneCols = 120; // How many "."s appear
    float laneLen = 1000.f; // I had this idea of making it 10000 for precision or something, and now I had no idea why I thought that.
    float dt = 0.25f; // Time per in-game tick. Would need to be replaced eventually. Maybe cap to 60 FPS '1.0f / 60.0f' / 0.0167s
};

class Game {
public:
    Game();

    // Advances game by one tick
    void update();

    // Resets the game
    // void reset();

    // GameState
    GameState getState() const { return state; }
    void setState(GameState m) { state = m; }
    bool isGameOver() const { return state == GameState::GameOver ; }

    // Getters
    // const vector<Unit>& getUnits() const { return units; }
    // E.g. to see gold count, need game.getEconomy().getGold()
    const Base& getPlayerBase() const { return playerBase; }
    const Base& getEnemyBase() const { return enemyBase; }
    const Economy& getPlayerEconomy() const { return playerEcon; } // Allows to see economy
    const Economy& getEnemyEconomy() const { return enemyEcon; }
    //const Faction& getPlayerFaction() const { return playerFaction; }
    //const Faction& getEnemyFaction() const { return enemyFaction; }
    const Config& getConfig() const { return cfg; }
    string winnerText() const;

// Split purely for organisational purposes
private:
    // Internal functions
    GameState state = GameState::MainGameScreen;
    // void aiStep_();
    // void movementStep_();
    // void combatStep_();
    // void cleanupDead_();
    float colToWorld_(int col) const;
    int worldToCol_(float x) const;
    //void incomeStep_();  \\ Replaced by economy class
    void updateProjectiles_(float dt);
    vector<Projectile> projectiles;

    // Game properties
    Config cfg{};
    //Faction playerFaction;
    //Faction enemyFaction;
    Economy playerEcon;
    Economy enemyEcon;
    Base playerBase;
    Base enemyBase;
    // vector<Unit> units;
    // bool gameOver{false};
    // float aiSpawnCooldown{0.f}; // Tracking for when the enemy creates units so it doesn't just fart out units
};

#endif
