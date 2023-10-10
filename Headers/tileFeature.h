#ifndef TILEFEATURE_H
#define TILEFEATURE_H

#include "Object.h"
#include <SFML/Graphics/RectangleShape.hpp>
class tileFeature : public Object{
    private:
        float x;
        float y;
        sf::RectangleShape rectangle;
        

    public:
        tileFeature(int id, float x, float y);

        //get rectangle bound by tiles
        sf::RectangleShape get_bounds();

        //get x, y coords of wall tile 
        float get_x();
        float get_y();


};

#endif