#include "../Headers/Collectable.h"
#include <SFML/Graphics.hpp>

//Called when Gun is intialized in Person constructor (default pistol)
Collectable::Collectable(int id, bool isCollected){
    this->id=id;
    this->isCollected = isCollected;
    passthrough = true;
    x = 0;
    y = 0;
    rectangle.setSize(sf::Vector2f(16, 16));
    rectangle.setPosition(x,y);
}

//Called when objects are created in Game class to be picked up
 Collectable::Collectable(int id, bool isCollected, float x, float y, std::string texture){
    this->id=id;
    this->isCollected = isCollected;
    passthrough = true;
    this->x = x;
    this->y = y;
    recttexture.loadFromFile(texture);
    rectangle.setTexture(&recttexture);
    rectangle.setSize(sf::Vector2f(16, 16));
    rectangle.setPosition(x,y);
 }

//Gets position data for object
float Collectable::get_x(){
    return x;
}

float Collectable::get_y(){
    return y;
}

sf::RectangleShape Collectable::get_bounds(){
    return rectangle;
}

void Collectable::render(sf::RenderWindow& app){
    app.draw(rectangle);
}

 bool Collectable::get_collected_status(){
    return isCollected;
 }