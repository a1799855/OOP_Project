#include <algorithm>
#include "game.h"
#include "debug.h"

using namespace std;

Game::Game() {
    // Initial game state & data
    state = GameState::MainGameScreen;
    cfg = Config{};
    econ = Economy{};
    playerBase = Base{};
    enemyBase  = Base{};
    // units.clear();
    // aiSpawnCooldown = 0.f;
}

// Purely for testing
void Game::damageBase(Faction side, int dmg) {
    if (state == GameState::GameOver) return;
    if (side == Faction::Player) {
        playerBase.hp -= dmg;
        if (playerBase.hp < 0) playerBase.hp = 0;
    }
    if (side == Faction::Enemy) {
        enemyBase.hp -= dmg;
        if (enemyBase.hp < 0) enemyBase.hp = 0;
    }
}

void Game::incomeStep_() {
    econ.acc += econ.income_per_sec * cfg.dt;
    while (econ.acc >= 1.f) { econ.gold += 1; econ.acc -= 1.f; }
}

void Game::update() {
    if (playerBase.hp <= 0) {
        state = GameState::GameOver;
        playerBase.hp = 0;
    }
    if (enemyBase.hp <= 0) {
        state = GameState::GameOver;
        enemyBase.hp = 0;
    }
}

string Game::winnerText() const {
    // if (!gameOver) return ""; // Originally game over was going to be tracked by a bool in my mind. Then I thought about more menus and game states. This is a bit of vestigal code
    if (playerBase.hp <= 0 && enemyBase.hp <= 0) return "Draw!";
    if (enemyBase.hp <= 0) return "You won!";
    if (playerBase.hp <= 0 ) return "You lost!";
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
