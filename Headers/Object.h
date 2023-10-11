#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
class Object{
    protected:
        //Can people walk through the object
        bool passthrough;

        //Unique object ID
        int id;
        
        int get_id();
        virtual sf::RectangleShape get_bounds() = 0;
        virtual float get_x() = 0;
        virtual float get_y() = 0;
        bool isPassthrough();
        
};

#endif