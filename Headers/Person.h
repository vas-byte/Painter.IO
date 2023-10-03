#ifndef PERSON_H
#define PERSON_H
    
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Common.h"

class Person : Object {
    protected:
        int health;
        bool shoot;
        float xDelta;
        float yDelta;
        float Rot;
     
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Texture bTexture;
        sf::Sprite bullet;
        sf::Vector2f bulletDirection;
    
    public:
        Person();
        void attack();
        int get_health();
        sf::Sprite move();
        void setMovement(movement::Direction direction);
        sf::Sprite shootBullet();
        bool showBullet();
};

#endif