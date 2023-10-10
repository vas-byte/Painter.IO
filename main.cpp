#include <SFML/Graphics.hpp>
#include <iostream>
#include "Headers/Player.h"
#include "Headers/Bullet.h"
#include "Headers/Common.h"
#include "Headers/Game.h"


int main() {
  //Create game instance
  Game game;

  // create the window
  sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");

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
     game.set_bullet();
    }

    //Listen for keyboard input to pickup objects
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
     game.collectObject();
    }

  
    //Clear previous frame
    window.clear();

    //Render map
    window.draw(game.get_map());

    //render collectable objects
    game.render_objects(window);

    //Render bullets
    game.show_bullet(window);

    //Render player movement and HUD
    game.renderPlayer(window);
    
    //Show new frame
    window.display();
  }

  return 0;
}