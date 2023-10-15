#include <SFML/Graphics.hpp>

class WelcomeScreen {
private:
    sf::Text title;
    sf::Text instructions;
    sf::Font font;
public:
    WelcomeScreen(int width, int height);
    void render(sf::RenderWindow& window);
    bool handleInput(const sf::Event& event); 
};
