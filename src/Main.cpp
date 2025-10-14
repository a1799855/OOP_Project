#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include "Game.h"
#include "Debug.h"

using namespace std;

namespace renderer {
    // ANSI should clear the screen. Might not work. system("clear") can be used instead. Would need <cstdlib>
    // void clearScreen() {
    //     cout << "\x1b[2J\x1b[H" << flush;
    // }
    void clearScreen() {
        system("clear");
    }

    // Creates the health bar using pipes "|"
    static string bar(int value, int maxVal, int width) {
        width = max(width, 1);
        if (maxVal <= 0) {
            return string(width, ' ');
        }
        // Limit range
        value = clamp(value, 0, maxVal);
        
        // Originally had "int filled = (int)((double)value / (double)maxVal * width);", had a bug. This should fix it.
        double ratio = static_cast<double>(value)/static_cast<double>(maxVal);
        int filled = static_cast<int>(ratio * width);

        // Failovers
        if (filled < 0) filled = 0;
        if (filled > width) filled = width;

        return string(filled, '|') + string(width - filled, ' ');
    }

    string render(const Game& g) {
        const auto& cfg = g.getConfig();
        const auto& pb = g.getPlayerBase();
        const auto& eb = g.getEnemyBase();
        const auto& econ = g.getEconomy();

        // Constructs the lane that units move across
        string lane(cfg.laneCols, '.');

        ostringstream out;
        // Gold amount and base health display
        out << "Gold: " << econ.gold << " | Player Base[" << pb.getHp() << "] | " << " Enemy Base[" << eb.getHp() << "]\n";
        out << "Player [" << bar(pb.getHp(), 200, 20) << "]   " << "Enemy [" << bar(eb.getHp(), 200, 20) << "]\n";

        // Prints the lane
        out << "🏰" << lane << "🏰" << "\n";

        // Comtrols, prompting for expected player inputs. More dynamic input with cooldowns later on
        out << "Controls:" << "\n" << "'p' to damage enemy, 'e' to damage player, 'n' to advance tick, and 'q' to quit.\n";

        // Game over banner. To be replaced by gameState
        if (g.isGameOver()) {
            out << "\n=== " << g.winnerText() << " ===\n";
        }

        // Debug handling; "return s;" should be what the player sees
        string s = out.str();
        Debug::print(s);
        return s;
    }
}

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
            const_cast<Base&>(game.getEnemyBase()).takeDamage(25);
            Debug::info("Enemy damaged for 25");
            game.update();
        }
        if (cmd == "e" || cmd == "E") {
            const_cast<Base&>(game.getPlayerBase()).takeDamage(25);
            Debug::info("Player damaged for 25");
            game.update();
        }
        // Advance simulation one tick. I would rather this be tied to something like "float dt"
        if (cmd == "n" || cmd == "N") {
            game.update();
            // 
            // this_thread::sleep_for(std::chrono)
        }
    }
    Debug::info("Closing logger");
    Debug::shutdown();
    return 0;
}
