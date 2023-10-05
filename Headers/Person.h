#ifndef PERSON_H
#define PERSON_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "Object.h"
#include "Common.h"
#include "Bullet.h"
#include "Game.h"
#include "Gun.h"

class Person : public Object {
    protected:
        int health;
        std::array<Gun, 2> gun_inventory;
        float xDelta;
        float yDelta;
        float Rot;
        sf::Sprite sprite;
        sf::Texture texture;
        Game* game;
        sf::Clock clock;
        
    public:
        Person(Game* thisGame);
        void attack();
        int get_health();
        sf::Sprite move();
        void setMovement(movement::Direction direction);
        
};

#endif

//TODO create player class which outputs ammo and health