#include "../Headers/Collectable.h"
#include <SFML/Graphics.hpp>

Collectable::Collectable(bool isCollected){
    id="an ID";
    this->isCollected = isCollected;
    position = sf::Vector2f(0,0);
}

Collectable::Collectable(){
    id="an ID";
    isCollected = false;
    position = sf::Vector2f(0,0);
}