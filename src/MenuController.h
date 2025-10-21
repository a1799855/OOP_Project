#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <string>
#include <random>
#include "Game.h"

using namespace std;

class MenuController {
    public:
        MenuController() = default;

        void handle(Game& game, const string& input);

        GameState tick(Game& game, const string& input);
    private:
        void onStartMenu_(Game& game, const string& in);
        void onFactionSelect_(Game& game, const string& in);
        void onMainGameScreen_(Game& game, const string& in);
        void onUpgradeMenu_(Game& game, const string& in);
        void onGameOver_(Game& game, const string& in);

        FactionType factionPick_(const string& in); // Input for Faction, 1-4 
};

#endif