#include "mediumBot.h"
#include <cstdlib>  
#include <cmath>   

MediumBot::MediumBot() : Person() {
}

void MediumBot::update() {
    move();
    attack();
}

sf::Sprite MediumBot::move() {
    int random = rand() % 100;
    if (random < 15) {  // 15% chance to change direction, slightly more often than ezybot
        setMovement(static_cast<movement::Direction>(rand() % 4));  
    }
}

void MediumBot::attack() {
    int random = rand() % 100;
    if (random < 20) {  // 20% chance to shoot in each update, more often than Eattbot
        float deviation = (rand() % 15 - 7.5) * (M_PI / 180);  
        shootBullet();
        bulletDirection = sf::Vector2f(cos(Rot + deviation), sin(Rot + deviation));
    }
}
