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

        movement::Direction currentDirection;
        sf::Vector2f bulletDirection;
            
    public:
        Person(int id, float x, float y);

        //Attack methods
        virtual Bullet* attack();
        bool canAttack();
        void swapGun();
        // virtual void attack();

        //Get player's status 
        int get_health();

        virtual void setMovement(movement::Direction direction);
        Bullet* shootBullet();

        //Move player
        virtual void move(movement::Direction direction);
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
        void takeDamage(int amount);
        bool isDead();

        //Player collectables
        bool accept_collectables(Gun* gun);
        bool accept_collectables(Health* health);
        bool accept_collectables(Ammo* ammo);

        virtual void update();
        virtual sf::Sprite getSprite();

        // virtual void move(movement::Direction direction);
        // virtual Bullet* shootBullet();

};

#endif

//TODO create player class which outputs ammo and health
