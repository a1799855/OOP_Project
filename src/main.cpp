#include <iostream>
#include <string>
#include "game.h"
#include "debug.h"
#include "renderer.h"

using namespace std;

int main() {
    Debug::init("debug.log", true);
    
    Game game;
    Debug::info("Game started");

    while (true) {
        renderer::clearScreen();
        renderer::render(game);

        if (game.isGameOver()) {
            Debug::info("Game over reached");
            cout << "Press Enter to exit.\n";
            string dummy;
            getline(cin, dummy);
            break;
        }

        // Turn-based input. Supposed to read a line each in-game update/"tick"
        cout << "> ";
        string cmd;
        if (!getline(cin, cmd)) break;

        if (cmd == "q" || cmd == "Q") {
            Debug::info("Player quit the program");
            break;
        }
        if (cmd == "p" || cmd == "P") {
            game.damageBase(Faction::Enemy, 25);
            Debug::info("Enemy damaged for 25");
            game.update();
        }
        if (cmd == "e" || cmd == "E") {
            game.damageBase(Faction::Player, 25);
            Debug::info("Player damaged for 25");
            game.update();
        }
        // Advance simulation one tick. I would rather this be tied to something like "float dt"
        if (cmd == "n" || cmd == "N") game.update();
    }
    Debug::info("Closing logger");
    Debug::shutdown();
    return 0;
}
