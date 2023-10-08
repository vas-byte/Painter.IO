#include <SFML/Graphics.hpp>
#include <iostream>
#include "Headers/Player.h"
#include "Headers/Bullet.h"
#include "Headers/Common.h"
#include "Headers/Game.h"


int main() {
  //Create game instance
  Game game;

  //Create instance of player (human)
  Player player(&game);

  // create the window
  sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    //Listen for keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      player.setMovement(movement::left);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      player.setMovement(movement::right);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      player.setMovement(movement::up);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      player.setMovement(movement::down);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
     player.attack();
    }

    //Clear previous frame
    window.clear();

    //Render map
    window.draw(game.get_map());

    //Render player movement and HUD
    window.draw(player.move());
    player.showAmmo(window);
    player.showHealth(window);

    //Render bullets & bot movement
    game.show_bullet(window);
    
    //Show new frame
    window.display();
  }

  return 0;
}