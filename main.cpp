#include <SFML/Graphics.hpp>
#include <iostream>
#include "Headers/Player.h"
#include "Headers/Bullet.h"
#include "Headers/Common.h"
#include "Headers/Game.h"

int main() {
    Game game;

    sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");

    // Welcome screen 
    sf::Font titleFont;  
    titleFont.loadFromFile("Assets/Fonts/CompassPro.ttf"); 

    // Title Text
    sf::Text titleText("Welcome to Painter.IO", titleFont, 50); 
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(game.get_width() / 2 - titleText.getLocalBounds().width / 2, game.get_height() / 4 - 100);

    sf::Sprite gifSprite;
    sf::Clock gifClock;
    const float frameDuration = 0.04f;  
    int currentFrame = 1;
    int numberOfFrames = 100;  // Total frames for the GIF
    std::vector<sf::Texture> gifFrames;

    for (int i = 1; i <= 100; i++) {
        sf::Texture texture;
        if(!texture.loadFromFile("Assets/download (" + std::to_string(i) + ").png")) {
        std::cerr << "Failed to load frame " << i << std::endl;
        } else {
            gifFrames.push_back(texture);
        }
    }

    // Enter Button
    sf::RectangleShape enterButton(sf::Vector2f(150, 60)); 
    enterButton.setPosition(game.get_width() / 2 - enterButton.getSize().x / 2, 2 * game.get_height() / 3 + 100);
    enterButton.setFillColor(sf::Color(129, 106, 58));
    
    // Button Text
    sf::Text buttonText("Enter", titleFont, 30); 
    buttonText.setPosition(enterButton.getPosition().x + (enterButton.getSize().x - buttonText.getLocalBounds().width) / 2, 
                          enterButton.getPosition().y + (enterButton.getSize().y - buttonText.getLocalBounds().height) / 2);
    buttonText.setFillColor(sf::Color::White);
    float enterTextCenterX = enterButton.getPosition().x + (enterButton.getLocalBounds().width / 2) - (buttonText.getLocalBounds().width / 2);
    float adjustedTextHeight = buttonText.getCharacterSize();
    float enterTextCenterY = enterButton.getPosition().y + (enterButton.getSize().y - adjustedTextHeight) / 2;
    buttonText.setPosition(enterTextCenterX, enterTextCenterY);

    // Welcome screen loop
    bool showWelcomeScreen = true;
    while (showWelcomeScreen) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Checking fot the for window close
            if (event.type == sf::Event::Closed) {
                window.close();
                return 0;
            }

            // Check for mouse movement over the enterButton
            if (event.type == sf::Event::MouseMoved) {
                if (enterButton.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                    enterButton.setFillColor(sf::Color::Red); // Hover effect
                } else {
                    enterButton.setFillColor(sf::Color(127, 103, 56));
                }
            }

            // Check for mouse button press on the enterButton
            if (event.type == sf::Event::MouseButtonPressed && 
                event.mouseButton.button == sf::Mouse::Left &&
                enterButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                showWelcomeScreen = false;
            }
        }

        // Update     frames
        if (gifClock.getElapsedTime().asSeconds() >= frameDuration) {
            currentFrame = (currentFrame + 1) % numberOfFrames;
            gifSprite.setTexture(gifFrames[currentFrame]);
            gifClock.restart();
        }
        
        // Position the ]=    sprite
        gifSprite.setPosition(game.get_width() / 2 - gifSprite.getLocalBounds().width / 2, game.get_height() / 2 - 225);

        // Render the welcome screen
        window.clear(sf::Color(127, 103, 56));
        window.draw(titleText);
        window.draw(gifSprite);
        window.draw(enterButton);
        window.draw(buttonText);
        window.display();
    }

  sf::Text gameOverText("Game Over", titleFont, 50);
  gameOverText.setFillColor(sf::Color::Red);
  gameOverText.setPosition(game.get_width() / 2 - gameOverText.getLocalBounds().width / 2, game.get_height() / 4 - 100);
  sf::RectangleShape restartButton(sf::Vector2f(150, 60)); 
  restartButton.setPosition(game.get_width() / 2 - restartButton.getSize().x / 2, 2 * game.get_height() / 3 + 100);
  restartButton.setFillColor(sf::Color(129, 106, 58));

  sf::Text restartButtonText("Restart", titleFont, 30);
  float restartTextCenterX = restartButton.getPosition().x + (restartButton.getLocalBounds().width / 2) - (restartButtonText.getLocalBounds().width / 2);
  float restartTextCenterY = restartButton.getPosition().y + (restartButton.getSize().y - restartButtonText.getCharacterSize()) / 2;
  restartButtonText.setPosition(restartTextCenterX, restartTextCenterY);
  restartButtonText.setFillColor(sf::Color::White);

  bool isGameOver = false;  

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      
       //Listen for keyboard input to swap guns
      if(event.type != sf::Event::KeyPressed) break; 
      if(event.key.code == sf::Keyboard::Tab){
        game.swap_gun();
      }
      
    }

    //Listen for keyboard input (for moving player)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      game.movePlayer(movement::left);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      game.movePlayer(movement::right);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      game.movePlayer(movement::up);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      game.movePlayer(movement::down);
    }
    
    //Listen for keyboard input to shoot
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
     game.shootBullet();
    }

    //Listen for keyboard input to pickup objects
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
     game.collectObject();
    }

    if (game.getHumanPlayerHealth() <= 0) {
        isGameOver = true;
    }

    bool needRender = true;
 
    if (isGameOver) {
        window.clear(sf::Color(127, 103, 56));  // Clear with background color
        window.draw(gameOverText);
        window.draw(restartButton);
        window.draw(restartButtonText);
        window.display();
        needRender = false;  
        
        sf::Event event;
        while (window.pollEvent(event)) {
            // Check for window close or escape key
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            } 

            // Check for mouse button press on the restartButton
            if (event.type == sf::Event::MouseButtonPressed && 
                event.mouseButton.button == sf::Mouse::Left &&
                restartButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                game.reset();   
                isGameOver = false;
                needRender = true;   
                break;  // restart
            }
        }
    } else {

      //Move the bots
      game.move_bots();
    
      //Clear previous frame
      window.clear();

      //Render map
      window.draw(game.get_map());

      //render collectable objects
      game.render_objects(window);

      //Render player movement and HUD
      game.renderPlayer(window);

      //Render bots
      game.render_bots(window);
      
      //Show new frame
      window.display();
    } 
  }  
  //something in Game destructor causes trace trap
  
  return 0;
}