#include <SFML/Graphics.hpp>
#include <iostream>
#include "Headers/Player.h"
#include "Headers/Bullet.h"
#include "Headers/Common.h"
#include "Headers/Game.h"


int main() {
  Game game;
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

    window.clear();
    window.draw(game.get_map());
    window.draw(player.move());
    game.show_bullet(window);
    player.showAmmo(window);
    player.showHealth(window);
    window.display();
  }

  return 0;
}