#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include "Game.h"

using namespace std;

namespace renderer {
    void clearScreen();
    
    // Trying to centre text
    // int getTerminalWidth();
    // string centreLine(const string& text, int totalWidth);
    // string centreBlock(const string& block, int totalWidth);

    string bar(int value, int maxVal, int width);

    string render(const Game& g);

    string renderStartMenu(const Game& g);
    string renderFactionSelect(const Game& g);
    string renderMainGameScreen(const Game& g);
    // string renderUpgradeMenu(const Game& g);
    string renderGameOver(const Game& g);
}

#endif