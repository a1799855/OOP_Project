#include <algorithm>
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

// **********************
void Game::Spawn(UnitType uType){
    if (uType == UnitType::Knight){
        playerEntities.push_back(new Knight(10,0.0f));   // Temporary ID
    }
    if (uType == UnitType::Peasant){
        playerEntities.push_back(new Peasant(11,0.0f));    // Temporary ID
    }
    if (uType == UnitType::Archer){
        playerEntities.push_back(new Archer(12,0.0f));    // Temporary ID
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
