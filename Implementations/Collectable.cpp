#include "../Headers/Collectable.h"
#include <SFML/Graphics.hpp>

Collectable::Collectable(int id, bool isCollected){
    this->id=id;
    this->isCollected = isCollected;
    passthrough = true;
    position = sf::Vector2f(0,0);
}

