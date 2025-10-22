#include <algorithm>
#include <array>
#include <cmath>
#include "Game.h"
#include "Debug.h"
#include "Unit.h"
#include "Knight.h"
#include "Peasant.h"
#include "Archer.h"

using namespace std;

// Gets the size for collision detection. Not for bases or projectiles.
static inline float sizeOf(const Entity& e) {
    if (auto u = dynamic_cast<const Unit*>(&e)) return u->getSize();
    return 0.0f;
}

float Game::stopBefore_(float blockerPos, float selfSize, float blockerSize, bool positiveSpeed) const {
    return positiveSpeed ? (blockerPos - (selfSize + blockerSize)) : (blockerPos + (selfSize + blockerSize));
}

// Manually selecting factions for both. Added for debugging/stretch goals
void Game::setFactions(FactionType playerPick, FactionType enemyPick) {
    playerFaction = Faction(playerPick);
    enemyFaction = Faction(enemyPick);
}

void Game::selectPlayerFaction(FactionType playerPick) {
    playerFaction = Faction(playerPick);

    array<FactionType, 4> allFactions{
        FactionType::Faction1, FactionType::Faction2,
        FactionType::Faction3, FactionType::Faction4
    };

    FactionType pool[3];
    int enemyPool = 0;
    for (auto randomEnemy : allFactions) if (randomEnemy != playerPick) pool[enemyPool++] = randomEnemy;
    uniform_int_distribution<int> dist(0, 2);
    enemyFaction = Faction(pool[dist(rng)]);
}

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

Game::~Game() {
    for (Entity* pEntity : playerEntities){
        delete pEntity;
    }
    playerEntities.clear();
    for (Entity* eEntity : enemyEntities){
        delete eEntity;
    }
    enemyEntities.clear();
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

Entity* Game::closestEnemy(Entity* attacker, bool isPlayerUnit) {
    if (attacker == nullptr || !attacker->isAlive()) {
        return nullptr;
    }
    
    float attackerPos = attacker->getPos();
    Entity* closest = nullptr;
    float minDistance = 999999.0f;
    
    if (isPlayerUnit) {
        // Player unit - search enemy entities and enemy base
        // Check enemy base first (always at end of lane)
        float distToBase = fabs(enemyBase.getPos() - attackerPos);
        if (enemyBase.isAlive() && distToBase < minDistance) {
            minDistance = distToBase;
            closest = &enemyBase;
        }
        
        // Check enemy units
        for (Entity* enemy : enemyEntities) {
            if (enemy->isAlive()) {
                float dist = fabs(enemy->getPos() - attackerPos);
                if (dist < minDistance) {
                    minDistance = dist;
                    closest = enemy;
                }
            }
        }
    } else {
        float distToBase = fabs(playerBase.getPos() - attackerPos);
        if (playerBase.isAlive() && distToBase < minDistance) {
            minDistance = distToBase;
            closest = &playerBase;
        }
        
        // Check player units
        for (Entity* player : playerEntities) {
            if (player->isAlive()) {
                float dist = fabs(player->getPos() - attackerPos);
                if (dist < minDistance) {
                    minDistance = dist;
                    closest = player;
                }
            }
        }
    }
    
    return closest;
}

void Game::playerCombatStep() {
    for (Entity* ent : playerEntities) {
        if (!ent->isAlive()) continue;
        
        Unit* unit = dynamic_cast<Unit*>(ent);
        if (unit != nullptr) {
            Entity* target = closestEnemy(unit, true);
            if (target != nullptr) {
                unit->attack(target);
            }
        }
    }
}

void Game::enemyCombatStep() {
    for (Entity* ent : enemyEntities) {
        if (!ent->isAlive()) continue;
        
        Unit* unit = dynamic_cast<Unit*>(ent);
        if (unit != nullptr) {
            Entity* target = closestEnemy(unit, false);
            if (target != nullptr) {
                unit->attack(target);
            }
        }
    }
}

// Basically fighting and getting stuck in a queue
void Game::resolveVsEntity_(Unit& u, Entity& target, float /*size*/, float dt) {
    if (!u.isAlive() || !target.isAlive()) return;

    const bool posDir = (u.getSpeed() > 0);
    const float p = u.getPos();
    const float tp = target.getPos();

    // Ignore entities behind
    if ((posDir && tp <= p) || (!posDir && tp >= p)) {
        u.setPos(p + static_cast<float>(u.getSpeed()) * dt);
        return;
    }

    const float desired = p + static_cast<float>(u.getSpeed()) * dt;

    const float selfSize = u.getSize();
    const float blockerSize = sizeOf(target);
    const float stopPos = stopBefore_(tp, selfSize, blockerSize, posDir);

    // Clamps but never goes backwards
    if (posDir) u.setPos(std::min(desired, stopPos));
    else u.setPos(std::max(desired, stopPos));
}

void Game::movementStep() {
    std::vector<Unit*> units;
    units.reserve(playerEntities.size() + enemyEntities.size());

    for (Entity* e : playerEntities) {
        if (!e || !e->isAlive()) continue;
        if (auto* u = dynamic_cast<Unit*>(e)) units.push_back(u);
    }
    for (Entity* e : enemyEntities) {
        if (!e || !e->isAlive()) continue;
        if (auto* u = dynamic_cast<Unit*>(e)) units.push_back(u);
    }

    auto moveOne = [&](Unit& u) {
        if (!u.isAlive()) return;
        if (u.getSpeed() == 0) return;

        const bool posDir = (u.getSpeed() > 0);
        const float p = u.getPos();
        const float desired = p + static_cast<float>(u.getSpeed()) * cfg.dt;

        Unit* best = nullptr;
        float bestDist = 1e9f;

        for (Unit* other : units) {
            if (other == &u) continue;
            if (!other->isAlive()) continue;

            const float tp = other->getPos();
            const float ahead = posDir ? (tp - p) : (p - tp);
            if (ahead < 0.f) continue;

            const float reach = std::fabs(desired - p) + u.getSize() + other->getSize();
            if (ahead <= reach && ahead < bestDist) {
                bestDist = ahead;
                best = other;
            }
        }

        if (!best) {
            u.setPos(desired); // Nothing infront
        } else {
            resolveVsEntity_(u, *best, 0.f, cfg.dt);
        }

        // Clamps to stop them leaving
        if (u.getPos() < 0.f) u.setPos(0.f);
        if (u.getPos() > cfg.laneLen) u.setPos(cfg.laneLen);
    };

    for (Unit* u : units) moveOne(*u);
}


void Game::update() {
    //incomeStep_();
    playerEcon.update(cfg.dt);    // ** Replace when dt is properly implemented
    enemyEcon.update(cfg.dt);
    updateProjectiles_(cfg.dt);
    if (!playerBase.isAlive() || !enemyBase.isAlive()) {
        state = GameState::GameOver;
    }

    movementStep();

    // Individually update each player entity
    for (int i = 0; i < static_cast<int>(playerEntities.size()); i++){
        Entity* ent = playerEntities[i];
        ent->update(cfg.dt);
    }
    // Individually update each enemy entity
    for (int i = 0; i < static_cast<int>(enemyEntities.size()); i++){
        Entity* ent = enemyEntities[i];
        ent->update(cfg.dt);
    }

    // Player advantage
    playerCombatStep(); // player will automatically attack each turn
    enemyCombatStep(); // enemy will automatically attack each turn

    playerEntities.erase(
        remove_if(playerEntities.begin(), playerEntities.end(),
            [](Entity* e) { 
                if (!e->isAlive()) {
                    delete e; 
                    return true; 
                } 
                return false; 
            }),
        playerEntities.end());

    enemyEntities.erase(
        remove_if(enemyEntities.begin(), enemyEntities.end(),
        [](Entity* e) { 
            if (!e->isAlive()) {
                delete e; 
                return true; 
            } 
            return false; 
        }),
        enemyEntities.end());
}


// Checks if economy can afford, and if so spawns in unit
void Game::playerSpawn(UnitType uType){
    if (uType == UnitType::Knight){
        int K_price = Knight(0,0.0f,2).getCost();
         if (playerEcon.getGold() >= K_price){
            playerEntities.push_back(new Knight(uniqueID,0.0f,2));
            playerEcon.spend(K_price);
            uniqueID = uniqueID + 1;
        }
    }
    if (uType == UnitType::Peasant){
        int P_price = Peasant(0,0.0f,1).getCost();
        if (playerEcon.getGold() >= P_price){
            playerEntities.push_back(new Peasant(uniqueID,0.0f,1)); 
            playerEcon.spend(P_price);
            uniqueID = uniqueID + 1;
        }
    }
    if (uType == UnitType::Archer){
        int A_price = Archer(0,0.0f,1).getCost();
        if (playerEcon.getGold() >= A_price){
            playerEntities.push_back(new Archer(uniqueID,0.0f,1));
            playerEcon.spend(A_price);
            uniqueID = uniqueID + 1;
        }
    }
}

void Game::enemySpawn(UnitType uType){
    if (uType == UnitType::Knight){
        int K_price = Knight(0,0.0f,-2).getCost();
        if (enemyEcon.getGold() >= K_price){
            enemyEntities.push_back(new Knight(uniqueID,cfg.laneLen-1,-2));
            enemyEcon.spend(K_price);
            uniqueID = uniqueID + 1;
        }
    }
    if (uType == UnitType::Peasant){
        int P_price = Peasant(0,0.0f,-1).getCost();
        if (enemyEcon.getGold() >= P_price){
            enemyEntities.push_back(new Peasant(uniqueID,cfg.laneLen-1,-1));
            enemyEcon.spend(P_price);
            uniqueID = uniqueID + 1;
        }
    }
    if (uType == UnitType::Archer){
        int A_price = Archer(0,0.0f,-1).getCost();
        if (enemyEcon.getGold() >= A_price){
            enemyEntities.push_back(new Archer(uniqueID,cfg.laneLen-1,-1));
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
    if (!playerBase.isAlive() && !enemyBase.isAlive()) return "Draw!";
    if (!enemyBase.isAlive()) return "YOU WIN!";
    if (!playerBase.isAlive()) return "YOU LOSE!";
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