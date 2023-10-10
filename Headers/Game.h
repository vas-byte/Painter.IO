#ifndef GAME_H
#define GAME_H

#include "tileMap.h"
#include "Bullet.h"
#include <vector>
#include "Object.h"
#include "Person.h"
#include "Player.h"
#include "Common.h"
#include "Health.h"
#include "Ammo.h"
class Game{
    private:
        //Map and frame characteristics
        int width;
        int height;
        TileMap map;

        //Fetches random "empty" position in game map
        sf::Vector2f generate_position();
        
        //in-game object properties
        int obj_id;
        std::vector<Bullet*> bullets;
        tileFeature** map_objects;
        Collectable** collectables;
        std::map<int,Gun*> collectable_guns;
        std::map<int,Ammo*> collectable_ammo;
        std::map<int,Health*> collectable_health;
        void load_features();
        void load_collectables();

        //Player related properties
        Player* human;
        bool detectPlayerCollision(Person* entity, Object* obj);
        bool isInsideMap(movement::Direction direction);
        
    
    public:
        Game();
        ~Game();

        //Frame properties (resolution)
        int get_width();
        int get_height();

        //in game object properties
        int generate_id();
        void set_bullet();
        void show_bullet(sf::RenderWindow &app);
        bool bulletCollision(Bullet* bullet);

        //Map properties
        TileMap get_map();
        void render_objects(sf::RenderWindow &app);
        
        //Player properties
        void renderPlayer(sf::RenderWindow &app);
        bool checkCollision(movement::Direction direction);
        void collectObject(Person* player);
        

        //Human Player properties
        void collectObject();
        void movePlayer(movement::Direction direction);
        void swap_gun();
       
};

#endif