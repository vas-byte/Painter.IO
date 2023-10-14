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
        
    public:
        //Retrieves unique ID of object
        int get_id();

        //retrieves position of object
        virtual float get_x() = 0;
        virtual float get_y() = 0;

        //retireves whether an object is passthrough
        bool isPassthrough();
        
};

#endif