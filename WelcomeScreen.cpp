#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shooter.io");

    sf::Text text;
    text.setFont(font);
    text.setString("Welcome to the game. Press any key to start");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                // Code to start the game
            }
        }

        window.clear();

        window.draw(text);

        window.display();
    }

    return 0;
}