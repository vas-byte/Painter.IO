#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <SFML/Graphics.hpp>
#include "Object.h"

class Collectable : public Object{
    protected:
        float x;
        float y;
        bool isCollected;
        sf::RectangleShape rectangle;
        
    public:
        Collectable(int id, bool isCollected);
        float get_x();
        float get_y();
        sf::RectangleShape get_bounds();
};

#endif