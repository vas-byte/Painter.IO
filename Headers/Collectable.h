#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <SFML/Graphics.hpp>
#include "Object.h"

class Collectable : public Object{
    protected:
        sf::Vector2f position;
        bool isCollected;
    public:
        Collectable(bool isCollected);
        Collectable();
};

#endif