#ifndef GAME_H
#define GAME_H

#include "tileMap.h"
#include "Bullet.h"
#include <vector>

class Game{
    private:
        int width;
        int height;
        TileMap map;
        std::vector<Bullet*> bullets;
        int obj_id;
    
    public:
        Game();
        ~Game();
        int get_width();
        int get_height();
        int generate_id();
        TileMap get_map();
        void set_bullet(Bullet* bullet);
        void show_bullet(sf::RenderWindow &app);
     
};

#endif