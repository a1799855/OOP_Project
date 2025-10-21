#include <algorithm>
#include <cstdlib>
#include "Game.h"
#include "Debug.h"
#include "Unit.h"
#include "Knight.h"
#include "Peasant.h"
#include "Archer.h"

using namespace std;

Game::Game() : 
    playerBase(0, 0.0f), enemyBase(1, cfg.laneLen),
    //playerFaction(FactionType::Faction1),
    //enemyFaction(FactionType::Faction4),
    //playerBase(0, 0.0f, Faction(Faction1)),         // ID == 0
    //enemyBase(1, cfg.laneLen, Faction(Faction2)),   // ID == 1
    playerEcon(),
    enemyEcon()
{
    // Initial game state & data
    state = GameState::MainGameScreen;
    cfg = Config{};
}

// Purely for testing
void Game::updateProjectiles_(float dt) {
    for (auto& p : projectiles )
        if (p.isAlive()) p.update(dt);
    projectiles.erase(
        remove_if(projectiles.begin(), projectiles.end(),
            [](const Projectile& p) { return !p.isAlive(); }),
        projectiles.end());
}

void Game::update() {
    //incomeStep_();
    playerEcon.update(cfg.dt);    // ** Replace when dt is properly implemented
    enemyEcon.update(cfg.dt);
    updateProjectiles_(cfg.dt);
    for (int i = 0; i < static_cast<int>(playerEntities.size()); i++){
        Entity* ent = playerEntities[i];
        ent->update(cfg.dt);
    }
    if (!playerBase.isAlive() || !enemyBase.isAlive()) {
        state = GameState::GameOver;
    }
}

// Checks if economy can afford, and if so spawns in unit
void Game::playerSpawn(UnitType uType){
    if (uType == UnitType::Knight){
        int K_price = Knight(0,0.0f).getCost();
        if (playerEcon.getGold() >= K_price){
            playerEntities.push_back(new Knight(uniqueID,0.0f));   // Temporary ID
            playerEcon.spend(K_price);
            uniqueID = uniqueID + 1;
        }
    }
    if (uType == UnitType::Peasant){
        int P_price = Peasant(0,0.0f).getCost();
        if (playerEcon.getGold() >= P_price){
            playerEntities.push_back(new Peasant(uniqueID,0.0f));    // Temporary ID
            playerEcon.spend(P_price);
            uniqueID = uniqueID + 1;
        }
    }
    if (uType == UnitType::Archer){
        int A_price = Archer(0,0.0f).getCost();
        if (playerEcon.getGold() >= A_price){
            playerEntities.push_back(new Archer(uniqueID,0.0f));    // Temporary ID
            playerEcon.spend(A_price);
            uniqueID = uniqueID + 1;
        }
    }
}

void Game::enemySpawn(UnitType uType){
    if (uType == UnitType::Knight){
        int K_price = Knight(0,0.0f).getCost();
        if (enemyEcon.getGold() >= K_price){
            enemyEntities.push_back(new Knight(uniqueID,cfg.laneLen));   // Temporary ID
            enemyEcon.spend(K_price);
            uniqueID = uniqueID + 1;
        }
    }
    if (uType == UnitType::Peasant){
        int P_price = Peasant(0,0.0f).getCost();
        if (enemyEcon.getGold() >= P_price){
            enemyEntities.push_back(new Peasant(uniqueID,cfg.laneLen));    // Temporary ID
            enemyEcon.spend(P_price);
            uniqueID = uniqueID + 1;
        }
    }
    if (uType == UnitType::Archer){
        int A_price = Archer(0,0.0f).getCost();
        if (enemyEcon.getGold() >= A_price){
            enemyEntities.push_back(new Archer(uniqueID,cfg.laneLen));    // Temporary ID
            enemyEcon.spend(A_price);
            uniqueID = uniqueID + 1;
        }
    }
}

void Game::AIController(){
    int randomNum = rand() % 8;
    if (randomNum == 0){
        enemySpawn(UnitType::Peasant);
    } else if (randomNum == 1 || randomNum == 2){
        enemySpawn(UnitType::Knight);
    } else if (randomNum == 3 || randomNum == 4 || randomNum == 5){
        enemySpawn(UnitType::Archer);
    } 
}

string Game::winnerText() const {
    // Idea for later
    // const bool playerAlive = playerBase.isAlive();
    // const bool enemyAlive = enemyBase.isAlive();

    if (!playerBase.isAlive() && !enemyBase.isAlive()) return "Draw!";
    if (!enemyBase.isAlive()) return "You won!";
    if (!playerBase.isAlive()) return "You lost!";
    return "";
}

float Game::colToWorld_(int col) const {
    return (float(col) / float(max(1, cfg.laneCols - 1))) * cfg.laneLen;
}
int Game::worldToCol_(float x) const {
    if (x <= 0.f) return 0;
    if (x >= cfg.laneLen) return cfg.laneCols - 1;
    float t = x / cfg.laneLen;
    return clamp(int(t * (cfg.laneCols - 1)), 0, cfg.laneCols - 1);
}

int Game::getUniqueID(){ return uniqueID; }
void Game::setUniqueID(int i){ uniqueID = i; }
