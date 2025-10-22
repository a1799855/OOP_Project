#include "Knight.h"

// Knight has: 
// HP == 30
// Attack == 6
// Speed == 2
// Cost == 20
// (Set atk_cd & atkTimer == 0 for now)
Knight::Knight(int id, float pos, int speed) : 
    Unit(id, 70, pos, 12, 1, 0, 0, speed, 60) {setSymb('>','<');}