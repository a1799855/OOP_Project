#ifndef RENDERER_H
#define RENDERER_H

#include "game.h"
#include <string>

using namespace std;

namespace renderer {
    void clearScreen();
    string render(const Game& g);
}

#endif