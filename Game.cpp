#include "Game.h"

Game::Game() : stormEye(200.0f, 400.0f) {
    players.push_back(Player(sf::Vector2f(100.0f, 100.0f), 100.0f));
}

void Game::update() {
    for (Player& player : players) {
        if (!stormEye.isInside(player.getPosition())) {
            player.takeDamage(5.0f);
        }
    }
    stormEye.shrink(0.5f);
}
