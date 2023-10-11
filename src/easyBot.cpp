#include "../Headers/easyBot.h"
#include <cstdlib>  
#include <cmath>   

EasyBot::EasyBot() : Person(0, 0.0f, 0.0f) {  // Using dummy values
}


void EasyBot::update() {
    move();
    attack();
}

void EasyBot::move(movement::Direction direction) {
    // Simple movement behavior
    int random = rand() % 100; 
    if (random < 5) {
        setMovement(static_cast<movement::Direction>(rand() % 4));  
    }
}

Bullet* EasyBot::attack() {
    int random = rand() % 100;
    if (random < 10) {  
        float deviation = (rand() % 20 - 10) * (M_PI / 180);  
        shootBullet();
        bulletDirection = sf::Vector2f(cos(get_rotation() + deviation), sin(get_rotation() + deviation));
    }
};



