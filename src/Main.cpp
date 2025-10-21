#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include "Game.h"
#include "Debug.h"

using namespace std;

namespace renderer {
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

    // Idea for realigning output
    // static string centreText(const string& text, int width) {
    //     if ((int)text.size() >= width) return text;
    //     int leftPadding = (width - text.size()) / 2;
    //     return string(leftPadding, ' ') + text;
    // }

    string render(const Game& g) {
        const auto& cfg = g.getConfig();
        const auto& pb = g.getPlayerBase();
        const auto& eb = g.getEnemyBase();
        const auto& playerEcon = g.getPlayerEconomy();
        const auto& enemyEcon = g.getEnemyEconomy();

        // Constructs the lane that units move across
        string lane(cfg.laneCols, '.');
        string laneBlank(cfg.laneCols, ' ');

        // ***********
        // Iterate over entities, finding position
        for (int i = 0; i < static_cast<int>(g.getPlayerEntities().size()); i++){
            Entity* ent = g.getPlayerEntities()[i];
            int column_pos =  static_cast<int>(( ent->getPos() / cfg.laneLen ) * cfg.laneCols);
            lane[column_pos] = ent->getPlayerSymb();
        }

        ostringstream out;
        // Gold amount and base health display
        out << "Player [" << bar(pb.getHp(), 200, 20) << "]" << "🏰" << lane << "🏰" << "[" << bar(eb.getHp(), 200, 20) << "] Enemy\n";
        out << "Health remaining:   " << pb.getHp() << laneBlank << "Health remaining:   " << eb.getHp() << "\n";
        out << "Gold count:         " << playerEcon.getGold() << "\n\n";

        // Comtrols, prompting for expected player inputs. More dynamic input with cooldowns later on
        out << "Controls:" << "\n" << "'d' to damage enemy" << "\n" << "'e' to damage player" << "\n" << "'p' to spawn peasant" << "\n" << "'k' to spawn knight" << "\n" << "'a' to spawn archer" << "\n" << "'n' to advance tick" << "\n" << "'q' to quit.\n";

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
        if (cmd == "d" || cmd == "D") {
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
        if (cmd == "k" || cmd == "K") {
            game.Spawn(UnitType::Knight);
            Debug::info("Spawned knight");
            // game.update();
        }
        if (cmd == "p" || cmd == "P") {
            game.Spawn(UnitType::Peasant);
            Debug::info("Spawned peasant");
            // game.update();
        }
        if (cmd == "a" || cmd == "A") {
            game.Spawn(UnitType::Archer);
            Debug::info("Spawned archer");
            // game.update();
        }
    }
    Debug::info("Closing logger");
    Debug::shutdown();
    return 0;
}
