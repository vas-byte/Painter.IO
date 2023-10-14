#ifndef PERSON_H
#define PERSON_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Object.h"
#include "Common.h"
#include "Bullet.h"
#include "Gun.h"
#include "tileFeature.h"
#include "Gun.h"
#include "Ammo.h"
#include "Health.h"

//Forward declare Player and BotBehaviour to include in render signature 
class BotBehaviour;
class Person : public Object{
    protected:
        //Player Health
        int health;
        virtual void updateHealth(int health);

        //Player Gun
        std::array<Gun, 2> gun_inventory;
        int selectedGun;
        sf::Clock clock;
        bool hasSecondary;
        std::vector<Bullet*> bullets;

        //Setting Future Player movement
        bool isCollided;

        //Previous player position
        sf::Vector2f lastPos;
        float prev_dir;

        //Player sprite
        sf::Sprite sprite;
        sf::Texture texture;
            
    public:
        Person(int id, float x, float y);
        ~Person();

        //Attack methods
        void attack();
        bool canAttack();
        void swapGun();

        //Modify/Read player's health status 
        int get_health();
        bool isDead();
        virtual void takeDamage(int damage);

        //Move player
        void move(movement::Direction direction, tileFeature** map_objects, int width, int height);

        //Render player (defined in Player and BotBehaviour classes)
        virtual void render(sf::RenderWindow& app, int width, int height, tileFeature** map_objects, Person* human, BotBehaviour** bots) = 0;

        //Get Player Position
        float get_x();
        float get_y();
        float get_rotation();

        //Player collision status 
        bool checkFutureCollision(movement::Direction direction, tileFeature** map_objects);
        bool detectPlayerCollision(Object* obj);
        bool isInsideMap(movement::Direction direction, int width, int height);

        //Collect collectable objects
        void collectObject(Collectable** collectables, std::map<int, Ammo*> ammo, std::map<int, Health*> health, std::map<int, Gun*> guns);

};

#endif

