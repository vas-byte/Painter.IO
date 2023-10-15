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
#include "EasyBot.h"
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
        tileFeature** map_objects;
        Collectable** collectables;
        std::map<int,Gun*> collectable_guns;
        std::map<int,Ammo*> collectable_ammo;
        std::map<int,Health*> collectable_health;
        void load_features();
        void load_collectables();
        const int num_features = 91;
        int num_collectables;


        //Player related properties
        Player* human;
        bool humanInit;
       
        //Bot related properties
        BotBehaviour** bots;
        int numBots;
        
        
    
    public:
        Game();
        ~Game();

        //Frame properties (resolution)
        int get_width();
        int get_height();
        void reset();   

        //in game object properties
        int generate_id();

        //Renders bullet in game
        void shootBullet();

        //Map properties
        TileMap get_map();
        void render_objects(sf::RenderWindow &app);
        
        //Player properties
        void renderPlayer(sf::RenderWindow &app);
        
        //Human Player properties
        void collectObject();
        void movePlayer(movement::Direction direction);
        void swap_gun();

        //Bot functionality
        void render_bots(sf::RenderWindow &app);
        void move_bots();

        int getHumanPlayerHealth() const;

};

#endif