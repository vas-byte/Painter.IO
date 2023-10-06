#ifndef GAME_H
#define GAME_H

#include "Person.h"
#include "tileMap.h"

class Game{
    private:
        int width;
        int height;
        TileMap map;

    public:
        Game();
        int get_width();
        int get_height();
        TileMap get_map();

};

#endif











