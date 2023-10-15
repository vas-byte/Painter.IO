#include "../Headers/Welcome.h"

WelcomeScreen::WelcomeScreen(int width, int height) {
    // Setup title text
    title.setFont(font);
    title.setString("Welcome to Painter.IO!");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setPosition(width / 2 - title.getGlobalBounds().width / 2, height / 3);

    instructions.setFont(font);
    instructions.setString("Press Enter to Start");
    instructions.setCharacterSize(20);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(width / 2 - instructions.getGlobalBounds().width / 2, 2 * height / 3);
}

void WelcomeScreen::render(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(instructions);
}

bool WelcomeScreen::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        return true;
    }
    return false;
}
