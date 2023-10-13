#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System/Vector2.hpp>

class Player {
public:
    Player(sf::Vector2f& initial_position, float initial_health);
    void takeDamage(float damage);
    sf::Vector2f getPosition();

private:
    sf::Vector2f position;
    float health;
};

#endif