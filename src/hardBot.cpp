#include "hardBot.h"
#include <cstdlib>  
#include <cmath>    

HardBot::HardBot() : Person() {
}

void HardBot::update() {
    move();
    attack();
}

sf::Sprite HardBot::move() {
    int random = rand() % 100;
    if (random < 25) { 
        setMovement(static_cast<movement::Direction>(rand() % 4));  
    }
}

void HardBot::attack() {
    int random = rand() % 100;
    if (random < 30) {  
        float deviation = (rand() % 5 - 2.5) * (M_PI / 180);  
        shootBullet();
        bulletDirection = sf::Vector2f(cos(Rot + deviation), sin(Rot + deviation));
    }
}
