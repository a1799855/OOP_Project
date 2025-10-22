#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Debug.h"
#include "MenuController.h"
#include "Renderer.h"

using namespace std;

int main() {
    srand(time(nullptr));

    Debug::init("debug.log", true);

    Game game;
    game.setState(GameState::StartMenu);
    Debug::info("Game started");

    MenuController menu;
    string line;

    while (true) {
        renderer::clearScreen();
        switch (game.getState()){
            case GameState::StartMenu: renderer::renderStartMenu(game); break;
            case GameState::FactionSelect: renderer::renderFactionSelect(game); break;
            case GameState::MainGameScreen: renderer::renderMainGameScreen(game); break;
            case GameState::UpgradeMenu: renderer::renderUpgradeMenu(game); break;
            case GameState::GameOver: renderer::renderGameOver(game); break;
        }
        if (!std::getline(std::cin, line)) break;
        menu.handle(game, line);
    }
    Debug::info("Closing logger");
    Debug::shutdown();
    return 0;
}
