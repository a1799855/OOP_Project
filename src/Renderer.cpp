#include <sstream>
#include <algorithm>
#include <iostream>

#include "Renderer.h"
#include "Debug.h"

using namespace std;

namespace renderer {
    void clearScreen() {
        system("clear");
    }
    // This should be better, but I can't get it to work.
    // void clearScreen() {
    //     cout << "\x1b[2J\x1b[H";
    // }

    string renderStartMenu(const Game& g) {
        ostringstream out;
        out << "\n|||||   START   |||||\n\n"
        << "Start game:        [g]\n"
        << "Quit:              [q]\n";

        // Debug handling; "return s;" should be what the player sees
        const string s = out.str();
        Debug::print(s);
        return s;
    }

    string renderFactionSelect(const Game& g) {
        ostringstream out;
        out << "\n|||||   SELECT FACTION   |||||\n\n"
            << "Westerland         [1]\n"
            << "Easton             [2]\n"
            << "Southos            [3]\n"
            << "Northia            [4]\n";
        const string s = out.str();
        Debug::print(s);
        return s;
    }

    // Creates the health bar using pipes "|"
    string bar(int value, int maxVal, int width) {
        width = max(width, 1);
        if (maxVal <= 0) {
            return string(width, ' ');
        }
        // Limit range
        value = clamp(value, 0, maxVal);
        
        // Originally had "int filled = (int)((double)value / (double)maxVal * width);", had a bug. This should fix it.
        const double ratio = static_cast<double>(value)/static_cast<double>(maxVal);
        int filled = static_cast<int>(ratio * width);

        // Failovers
        if (filled < 0) filled = 0;
        if (filled > width) filled = width;

        return string(filled, '|') + string(width - filled, ' ');
    }

    string renderMainGameScreen(const Game& g) {
        const auto& cfg = g.getConfig();
        const auto& pb = g.getPlayerBase();
        const auto& eb = g.getEnemyBase();
        const auto& pe = g.getPlayerEconomy();
        // Might remove enemy econ being shown.
        const auto& ee = g.getEnemyEconomy();
        const string pf = Faction(g.playerFaction).getFactionName();
        const auto& ef = Faction(g.enemyFaction).getFactionName();

        // Constructs the lane that units move across
        string lane(cfg.laneCols, '.');
        string laneBlank(cfg.laneCols, ' ');
        
        // Search 'playerEntity' for all positions, extract positions and render
        for (int i = 0; i < static_cast<int>(g.getPlayerEntities().size()); i++){
            Entity* ent = g.getPlayerEntities()[i];
            int column_pos =  static_cast<int>(( ent->getPos() / cfg.laneLen ) * cfg.laneCols);
            lane[column_pos] = ent->getPlayerSymb();
        }

        // Search 'enemyEntity' for all positions, extract positions and render
        for (int i = 0; i < static_cast<int>(g.getEnemyEntities().size()); i++){
            Entity* ent = g.getEnemyEntities()[i];
            int column_pos =  static_cast<int>(( ent->getPos() / cfg.laneLen ) * cfg.laneCols);
            lane[column_pos] = ent->getEnemySymb();
        }

        ostringstream out;
        // Gold amount and base health display
        out << "\n" << pf << " [" << bar(pb.getHp(), 200, 20) << "]" << "🏰" << lane << "🏰" << "[" << bar(eb.getHp(), 200, 20) << "] " << ef << "\n";
        out << "Health remaining:   " << pb.getHp() << laneBlank << "Health remaining:   " << eb.getHp() << "\n";
        out << "Gold count:         " << pe.getGold() << laneBlank << "Gold Count:         " << ee.getGold() << "\n\n";

        // Comtrols, prompting for expected player inputs. More dynamic input with cooldowns later on
        out << "Peasant (20) Gold  [p]\n"
            << "Archer  (30) Gold  [a]\n"
            << "Knight  (60) Gold  [k]\n"
            << "Upgrade menu       [m]\n"
            << "Quit               [q]\n";

        // Game over banner. To be replaced by gameState
        if (g.isGameOver()) {
            out << "\n=== " << g.winnerText() << " ===\n";
        }

        // Debug handling; "return s;" should be what the player sees
        const string s = out.str();
        Debug::print(s);
        return s;
    }

    string renderUpgradeMenu(const Game& g) {
        const auto& cfg = g.getConfig();
        const auto& pb = g.getPlayerBase();
        const auto& eb = g.getEnemyBase();
        const auto& pe = g.getPlayerEconomy();
        const auto& ee = g.getEnemyEconomy();
        const string pf = Faction(g.playerFaction).getFactionName();
        const auto& ef = Faction(g.enemyFaction).getFactionName();

        // Constructs the lane that units move across
        string lane(cfg.laneCols, '.');
        string laneBlank(cfg.laneCols, ' ');

        // Iterate over entities, finding position
        for (int i = 0; i < static_cast<int>(g.getPlayerEntities().size()); i++){
            Entity* ent = g.getPlayerEntities()[i];
            int column_pos =  static_cast<int>(( ent->getPos() / cfg.laneLen ) * cfg.laneCols);
            lane[column_pos] = ent->getPlayerSymb();
        }
        for (int i = 0; i < static_cast<int>(g.getEnemyEntities().size()); i++){
            Entity* ent = g.getEnemyEntities()[i];
            int column_pos =  static_cast<int>(( ent->getPos() / cfg.laneLen ) * cfg.laneCols);
            lane[column_pos] = ent->getEnemySymb();
        }

        ostringstream out;
        // Gold amount and base health display
        out << "\n" << pf << " [" << bar(pb.getHp(), 200, 20) << "]" << "🏰" << lane << "🏰" << "[" << bar(eb.getHp(), 200, 20) << "] " << ef << "\n";
        out << "Health remaining:   " << pb.getHp() << laneBlank << "Health remaining:   " << eb.getHp() << "\n";
        out << "Gold count:         " << pe.getGold() << laneBlank << "Gold Count:         " << ee.getGold() << "\n\n";

        // Comtrols, prompting for expected player inputs. More dynamic input with cooldowns later on
        out << "Peasant (20) Gold  [p]\n"
            << "Archer  (30) Gold  [a]\n"
            << "Knight  (60) Gold  [k]\n"
            // << "Upgrade menu       [m]\n"
            << "Quit               [q]\n";

        // Game over banner. To be replaced by gameState
        if (g.isGameOver()) {
            out << "\n=== " << g.winnerText() << " ===\n";
        }

        // Debug handling; "return s;" should be what the player sees
        const string s = out.str();
        Debug::print(s);
        return s;
    }

    string renderGameOver(const Game& g) {
        ostringstream out;
        out << "\n|||||   " << g.winnerText() << "   |||||\n\n"
        << "Back to start:     [s]\n"
        << "Quit:              [q]\n";

        // Debug handling; "return s;" should be what the player sees
        const string s = out.str();
        Debug::print(s);
        return s;
    }
}
