#include "easyBot.h"
#include <cstdlib>  
#include <cmath>   

EasyBot::EasyBot() : Person() {
}

void EasyBot::update() {
    move();
    attack();
}

sf::Sprite EasyBot::move() {
    // Simple movement behavior
    int random = rand() % 100; 
    if (random < 5) {
        setMovement(static_cast<movement::Direction>(rand() % 4));  
    }
}

void EasyBot::attack() {
    int random = rand() % 100;
    if (random < 10) {  
        float deviation = (rand() % 20 - 10) * (M_PI / 180);  
        shootBullet();
        bulletDirection = sf::Vector2f(cos(Rot + deviation), sin(Rot + deviation));
    }
}
