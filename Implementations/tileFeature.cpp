#include "../Headers/tileFeature.h"
#include <SFML/Graphics.hpp>

tileFeature::tileFeature(int id, float x, float y){
    this->id=id;
    passthrough = false;
    this->x = x;
    this->y = y;
    rectangle.setOrigin(sf::Vector2f(-4, -4));
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