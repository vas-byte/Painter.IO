#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>

class GameOverScreen {
public:
    GameOverScreen();
    void show(int rank, sf::RenderWindow &window);
};

#endif