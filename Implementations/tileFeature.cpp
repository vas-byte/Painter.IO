#include "../Headers/tileFeature.h"
#include <SFML/Graphics.hpp>

tileFeature::tileFeature(int id, float x, float y){
    //Assigns tile an ID
    this->id=id;

    //tile is not passthrough (ie objects must collide with it)
    passthrough = false;

    //Assigns it's x,y coordinates in the map
    this->x = x;
    this->y = y;

    //Sets the center of the sprite
    rectangle.setOrigin(sf::Vector2f(-4, -4));

    //Sets the position of sprite (used by get_bounds())
    rectangle.setPosition(x, y);
}

//Get the rectangle bound by the tile feature
sf::FloatRect tileFeature::get_bounds(){
    return rectangle.getGlobalBounds();
}

//Get x-coordinate of map tile feature
float tileFeature::get_x(){
    return x;
}

//Get y-coordinate of map tile feature
float tileFeature::get_y(){
    return y;
}