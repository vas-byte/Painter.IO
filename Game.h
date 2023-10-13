#ifndef GAME_H
#define GAME_H

#include <vector>
#include "StormEye.h"
#include "Player.h"

class Game {
public:
    Game();
    void update();

private:
    StormEye stormEye;
    std::vector<Player> players;
};

#endif
