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
class Person {
    protected:
        //Player Health
        int health;

        //Player Gun
        std::array<Gun, 2> gun_inventory;
        int selectedGun;
        sf::Clock clock;
        bool hasSecondary;

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

        //Attack methods
        Bullet* attack();
        bool canAttack();
        void swapGun();

        //Get player's status 
        int get_health();

        //Move player
        void move(movement::Direction direction);
        void render(sf::RenderWindow& app);

        //Get Player Position
        float get_x();
        float get_y();
        float get_rotation();
        sf::FloatRect get_bounds();

        //Player collision status
        bool get_collision();
        void set_collision(bool collision_status);
        float get_previous_dir();
        void set_previous_dir(float dir);

        //Player collectables
        bool accept_collectables(Gun* gun);
        bool accept_collectables(Health* health);
        bool accept_collectables(Ammo* ammo);

};

#endif

//TODO create player class which outputs ammo and health