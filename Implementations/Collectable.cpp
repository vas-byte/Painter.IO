#include "../Headers/Collectable.h"
#include <SFML/Graphics.hpp>

Collectable::Collectable(int id, bool isCollected){
    this->id=id;
    this->isCollected = isCollected;
    passthrough = true;
    x = 0;
    y = 0;
    rectangle.setSize(sf::Vector2f(16, 16));
    rectangle.setPosition(x,y);
}

float Collectable::get_x(){
    return x;
}

float Collectable::get_y(){
    return y;
}

sf::RectangleShape Collectable::get_bounds(){
    return rectangle;
}