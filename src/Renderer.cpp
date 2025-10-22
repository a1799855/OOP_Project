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
        << "Start game:                [g]\n"
        << "Quit:                      [q]\n";

        // Debug handling; "return s;" should be what the player sees
        const string s = out.str();
        Debug::print(s);
        return s;
    }

    string renderFactionSelect(const Game& g) {
        ostringstream out;
        out << "\n|||||   SELECT FACTION   |||||\n\n"
            << "Westerland                 [1]\n"
            << "Easton                     [2]\n"
            << "Southos                    [3]\n"
            << "Northia                    [4]\n";
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

        const int pCost = g.getPlayerUnitCost(UnitType::Peasant);
        const int aCost = g.getPlayerUnitCost(UnitType::Archer);
        const int kCost = g.getPlayerUnitCost(UnitType::Knight);

        // Constructs the lane that units move across
        string lane(cfg.laneCols, '.');
        string laneBlank(cfg.laneCols, ' ');
        
        // Game kept crashing as units went out of bounds. Time for maths
        auto toCol = [&](float x) {
            if (x <= 0.f) return 0;
            if (x >= cfg.laneLen) return cfg.laneCols - 1;
            float t = x / cfg.laneLen; // [0,1)
            return static_cast<int>(t * (cfg.laneCols - 1));
        };

        // Iterate over entities, finding position
        for (int i = 0; i < static_cast<int>(g.getPlayerEntities().size()); i++){
            Entity* ent = g.getPlayerEntities()[i];
            // int column_pos =  static_cast<int>(( ent->getPos() / cfg.laneLen ) * cfg.laneCols);
            int column_pos = toCol(ent->getPos());
            lane[column_pos] = ent->getPlayerSymb();
        }
        for (int i = 0; i < static_cast<int>(g.getEnemyEntities().size()); i++){
            Entity* ent = g.getEnemyEntities()[i];
            // int column_pos =  static_cast<int>(( ent->getPos() / cfg.laneLen ) * cfg.laneCols);
            int column_pos = toCol(ent->getPos());
            lane[column_pos] = ent->getEnemySymb();
        }

        for (const auto& p : g.getProjectiles()) {
            // convert world x to a lane column (reuse toCol lambda already in this func)
            int arrow = toCol(p.getPos());
            char arrowSymb = (p.getSpeed() > 0.0f) ? '-' : '-'; // Yes, they are the same

            // Avoid overwriting a unit; only draw if the cell is empty-ish
            if (lane[arrow] == '.') lane[arrow] = arrowSymb;
        }

        ostringstream out;
        // Gold amount and base health display
        out << "\n" << pf << " [" << bar(pb.getHp(), 200, 20) << "]" << "🏰" << lane << "🏰" << "[" << bar(eb.getHp(), 200, 20) << "] " << ef << "\n";
        out << "Health remaining:   " << pb.getHp() << laneBlank << "Health remaining:   " << eb.getHp() << "\n";
        out << "Gold count:         " << pe.getGold() << laneBlank << "Gold Count:         " << ee.getGold() << "\n\n";

        // Comtrols, prompting for expected player inputs. More dynamic input with cooldowns later on
        out << "Peasant (" << pCost << ") Gold          [p]\n"
            << "Archer  (" << aCost << ") Gold          [a]\n"
            << "Knight  (" << kCost << ") Gold          [k]\n"
            << "Upgrade menu               [m]\n"
            << "Quit                       [q]\n";

        // Debug handling; "return s;" should be what the player sees
        const string s = out.str();
        Debug::print(s);
        return s;
    }

    string renderUpgradeMenu(const Game& g) {
        const auto& pe = g.getPlayerEconomy();
        auto& pf = g.getPlayerFaction();
        const auto& pm = pf.getModifiers();

        ostringstream out;
        // Gold amount and base health display
        out << "\n|||||   PAUSED   |||||\n\n";
        out << "Gold count:         " << pe.getGold() << "\n\n";

        // Comtrols, prompting for expected player inputs. More dynamic input with cooldowns later on
        out << "Upgrade Peasant (40) Gold  [p]" << (pm.peasantUpgraded ? " [UPGRADED]" : "") << "\n"
            << "Upgrade Archer  (60) Gold  [a]" << (pm.archerUpgraded ? " [UPGRADED]" : "") << "\n"
            << "Upgrade Knight  (120) Gold [k]" << (pm.knightUpgraded ? " [UPGRADED]" : "") << "\n"
            << "Upgrade Economy            [e] " << (pm.econBuildings)<< "\n"
            << "Close Menu                 [m]\n";

        // Debug handling; "return s;" should be what the player sees
        const string s = out.str();
        Debug::print(s);
        return s;
    }

    string renderGameOver(const Game& g) {
        ostringstream out;
        out << "\n|||||   " << g.winnerText() << "   |||||\n\n"
        << "Back to start:             [s]\n"
        << "Quit:                      [q]\n";

        // Debug handling; "return s;" should be what the player sees
        const string s = out.str();
        Debug::print(s);
        return s;
    }
}
