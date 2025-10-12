#include <sstream>
#include <algorithm>
#include <iostream>

#include "renderer.h"
#include "debug.h"

using namespace std;

// I wanted to make an actual game. Great just a simple output was a little boring
// This probably shouldn't be used as the final product. Could use some refinement
// I have created several things I wasn't supposed to. Whoops. Use them for comparison I guess? 

namespace renderer {
    // ANSI should clear the screen. Might not work. system("clear") can be used instead. Would need <cstdlib>
    void clearScreen() {
        cout << "\x1b[2J\x1b[H" << flush;
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
        out << "Gold: " << econ.gold << " | Player Base[" << pb.hp << "] | " << " Enemy Base[" << eb.hp << "]\n";
        out << "Player [" << bar(pb.hp, 200, 20) << "]   " << "Enemy [" << bar(eb.hp, 200, 20) << "]\n";

        // Prints the lane
        out << lane << "\n";

        // Comtrols, prompting for expected player inputs. More dynamic input with cooldowns later on
        out << "Controls:" << "\n" << "'p' to damage enemy" << "\n" << "'e' to damage player" << "\n" << "'n' to advance tick" << "\n" << "'q' to quit.\n";

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
