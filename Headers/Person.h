#ifndef PERSON_H
#define PERSON_H
    
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Common.h"

class Person : public Object {  // Use 'public' inheritance
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
        
        virtual void attack();       // Make these methods virtual so they can be overridden
        virtual void update() = 0;   // Pure virtual function. This means all derived classes MUST provide an implementation.
        virtual int get_health();    // If you think the way of retrieving health might differ among bots, make this virtual
        virtual sf::Sprite move();   // Movement behavior will be different for bots, so this is virtual
        virtual sf::Sprite shootBullet();  // Shooting behavior differs among bots
        virtual bool showBullet();

        void setMovement(movement::Direction direction);  // This might remain common for all, but can be made virtual if needed
};

#endif
