#ifndef TILEFEATURE_H
#define TILEFEATURE_H

#include "Object.h"
#include <SFML/Graphics.hpp>
class tileFeature : public Object{
    private:
        float x;
        float y;
        sf::Sprite rectangle;
        

    public:
        tileFeature(int id, float x, float y);

        //get rectangle bound by tiles
        sf::FloatRect get_bounds();

        //get x, y coords of wall tile 
        float get_x();
        float get_y();


};

#endif