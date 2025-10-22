#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <sstream>
#include <random>
#include "MenuController.h"
#include "Renderer.h"
#include "Debug.h"

using namespace std;

inline char firstLower(const string& s) {
    return s.empty() ? '\0' : static_cast<char>(tolower(static_cast<unsigned char>(s[0])));
}

static constexpr FactionType factionList[4] {
    FactionType::Faction1, // Westerland
    FactionType::Faction2, // Easton
    FactionType::Faction3, // Southos
    FactionType::Faction4 // Northia
};

FactionType MenuController::factionPick_(const std::string& in) {
    if (in.empty()) return FactionType::Faction1; // Defaults to Westerland
    int k = std::clamp(std::atoi(in.c_str()), 1, 4);
    return factionList[k - 1];
}

void MenuController::handle(Game& g, const string& input) {
    switch (g.getState()) {
        case GameState::StartMenu: onStartMenu_(g, input); break;
        case GameState::FactionSelect: onFactionSelect_(g, input); break;
        case GameState::MainGameScreen: onMainGameScreen_(g, input); break;
        case GameState::UpgradeMenu: onUpgradeMenu_(g, input); break;
        case GameState::GameOver: onGameOver_(g, input); break;
    }
}

void MenuController::onStartMenu_(Game& g, const string& in) {
    char cmd = firstLower(in);
    if (cmd == 'g' || cmd == 'G') g.setState(GameState::FactionSelect);
    else if (cmd == 'q' || cmd == 'Q') exit(0);
}

void MenuController::onFactionSelect_(Game& g, const string& in) {
    FactionType playerPick = factionPick_(in);
    g.selectPlayerFaction(playerPick);
    g.setState(GameState::MainGameScreen);
}

void MenuController::onMainGameScreen_(Game& g, const string& in){
    if (in.empty()) { g.update(); return; }
    char cmd = firstLower(in);
    if (cmd == '1') {
        const_cast<Base&>(g.getEnemyBase()).takeDamage(25);
        Debug::info("Enemy damaged for 25");
        g.update();
    }
    else if (cmd == '2') {
        const_cast<Base&>(g.getPlayerBase()).takeDamage(25);
        Debug::info("Player damaged for 25");
        g.update();
    }
    else if (cmd == 'p' || cmd == 'P') {
        g.playerSpawn(UnitType::Peasant);
        Debug::info("Spawned peasant");
        g.update();
    }
    else if (cmd == 'a' || cmd == 'A') {
        g.playerSpawn(UnitType::Archer);
        Debug::info("Spawned archer");
        g.update();
    }
    else if (cmd == 'k' || cmd == 'K') {
        g.playerSpawn(UnitType::Knight);
        Debug::info("Spawned knight");
        g.update();
        Debug::info(to_string(g.usePlayerEconomy().getGold()));
    }
    else if (cmd == 'n') {}
    else if (cmd == 'm') {
        g.setState(GameState::UpgradeMenu); return;
    }
    else if (cmd == 'q' || cmd == 'Q') {
        Debug::info("Player quit the program");
        exit(0);
    }
    g.AIController();
    // g.update();
    if (g.isGameOver()) g.setState(GameState::GameOver);
}

void MenuController::onUpgradeMenu_(Game& g, const string& in){
    auto& pe = g.usePlayerEconomy();
    auto& pf = g.getPlayerFaction();
    auto& pm = Faction(g.playerFaction).getModifiers();

    if (in.empty()) { return; }
    char cmd = firstLower(in);
    if (cmd == 'p' || cmd == 'P') {
        if (!pm.peasantUpgraded && pe.getGold() >= 40) {
            pe.spend(40);
            pf.applyTechUpgrade("peasant");
            Debug::info("Upgraded peasant");
        }
        else {
            Debug::warn("Can't upgrade peasant. Not enough gold or already upgraded");
        }
    }
    else if (cmd == 'a' || cmd == 'A') {
        if (!pm.archerUpgraded && pe.getGold() >= 60) {
            pe.spend(60);
            pf.applyTechUpgrade("archer");
            Debug::info("Upgraded archer");
        }
        else {
            Debug::warn("Can't upgrade archer. Not enough gold or already upgraded");
        }
    }
    else if (cmd == 'k' || cmd == 'K') {
        if (!pm.knightUpgraded && pe.getGold() >= 120) {
            pe.spend(120);
            pf.applyTechUpgrade("knight");
            Debug::info("Upgraded knight");
        }
        else {
            Debug::warn("Can't upgrade knight. Not enough gold or already upgraded");
        }
    }
    else if (cmd == 'e' || cmd == 'E') {
        if (pe.getGold() >= 100) {
            pe.spend(100);
            pf.applyTechUpgrade("economy");
            Debug::info("Upgraded economy");
        }
        else {
            Debug::warn("Can't upgrade economy. Not enough gold");
        }
    } else if (cmd == 'q' || cmd == 'Q'){
        exit(0);
    }
   else if (cmd == 'm' || cmd == 'M') {
        g.setState(GameState::MainGameScreen);
    }
}

void MenuController::onGameOver_(Game& g, const string& in){
    char cmd= firstLower(in);
    if (cmd == 's' || cmd == 'S'){
        g = Game();
        g.setState(GameState::StartMenu);
    } else if (cmd == 'q' || cmd == 'Q'){
        exit(0);
    }
}
