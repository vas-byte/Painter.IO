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
        //Map and frame characteristics
        int width;
        int height;
        TileMap map;
        
        //in-game object properties
        int obj_id;
        std::vector<Bullet*> bullets;
        tileFeature** map_objects;

        //Player related properties
        Player* human;
        bool detectPlayerCollision(Object* obj);
        bool isInsideMap(movement::Direction direction);
        
    
    public:
        Game();
        ~Game();

        //Frame properties (resolution)
        int get_width();
        int get_height();

        //in game object properties
        int generate_id();
        void load_features();
        void set_bullet();
        void show_bullet(sf::RenderWindow &app);

        //Map properties
        TileMap get_map();
        
        //Player properties
        void renderPlayer(sf::RenderWindow &app);
        void movePlayer(movement::Direction direction);
        bool checkCollision(movement::Direction direction);
       
};

#endif