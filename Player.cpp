#include "Player.h"

Player::Player(sf::Vector2f& initial_position, float initial_health)
    : position(initial_position), health(initial_health) {}

void Player::takeDamage(float damage) {
    health -= damage;
}

sf::Vector2f Player::getPosition() {
    return position;
}
