#ifndef PERSON_H
#define PERSON_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Object.h"
#include "Common.h"
#include "Bullet.h"
#include "Gun.h"
#include "tileFeature.h"
class Person {
    protected:
        int health;
        std::array<Gun, 2> gun_inventory;
        float xDelta;
        float yDelta;
        float Rot;
        sf::Vector2f lastPos;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Clock clock;
        int selectedGun;
        bool isCollided;
        float prev_dir;
        
        
    public:
        Person(int id);
        Bullet* attack();
        bool canAttack();
        int get_health();
        sf::Sprite move();
        void setMovement(movement::Direction direction);
        void move(sf::Vector2f);

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

};

#endif

//TODO create player class which outputs ammo and health