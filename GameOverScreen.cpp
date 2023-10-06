#include "GameOverScreen.h"

GameOverScreen::GameOverScreen() {}

void GameOverScreen::show(int rank, sf::RenderWindow &window) {
    window.clear();

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);

    if (rank == 1) {
        text.setString("Victory Royale");
    } else {
        text.setString("You finished " + std::to_string(rank) + "th");
    }

    window.draw(text);
    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
}
