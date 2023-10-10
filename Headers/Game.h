#ifndef GAME_H
#define GAME_H

#include "tileMap.h"
#include "Bullet.h"
#include <vector>
#include "Object.h"
#include "Person.h"
#include "Player.h"
#include "Common.h"
class Game{
    private:
        int width;
        int height;
        TileMap map;
        std::vector<Bullet*> bullets;
        int obj_id;
        tileFeature** map_objects;
        Player* human;
        float prevDir;
        tileFeature* collided_tile;
        bool isCollided;
        int prev_dir;
        
    
    public:
        Game();
        ~Game();

        int get_width();
        int get_height();
        int generate_id();

        TileMap get_map();
        void load_features();

        void set_bullet();
        void show_bullet(sf::RenderWindow &app);
        void renderPlayer(sf::RenderWindow &app);
        void movePlayer(movement::Direction direction);

        bool checkCollision(movement::Direction direction);
        bool detectCollision(Object* obj);  
};

#endif