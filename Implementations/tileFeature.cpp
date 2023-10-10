#include "../Headers/tileFeature.h"
#include <SFML/Graphics/RectangleShape.hpp>

tileFeature::tileFeature(int id, float x, float y){
    this->id=id;
    passthrough = false;
    this->x = x;
    this->y = y;
    rectangle.setSize(sf::Vector2f(16, 16));
    rectangle.setOrigin(sf::Vector2f(8, 8));
    rectangle.setPosition(x, y);
}

sf::RectangleShape tileFeature::get_bounds(){
    return rectangle;
}

float tileFeature::get_x(){
    return x;
}

float tileFeature::get_y(){
    return y;
}