#include "../Headers/Game.h"

#include <iostream>
#include <vector>

#include "../Headers/Bullet.h"

Game::Game() {
  width = 1440;
  height = 800;
  map = TileMap();

  // define the level with an array of tile indices
  int level[4500];
  std::fill_n(level, 4500, 6);
  map.load("Assets/Tileset.png", sf::Vector2u(16, 16), level, 90, 50);
}

int Game::get_width() { return width; }

int Game::get_height() { return height; }

TileMap Game::get_map() { return map; }

void Game::set_bullet(Bullet* bullet) { bullets.push_back(bullet); }

void Game::show_bullet(sf::RenderWindow& app) {
  for (int i = 0; i < bullets.size(); i++) {

    if (!bullets.at(i)->isInsideMap(width, height)) {
      delete bullets.at(i);
      bullets.erase(bullets.begin() + i);
      continue;
    }
    
    app.draw(bullets.at(i)->shootBullet());
  }
}