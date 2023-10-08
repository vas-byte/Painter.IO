#include "../Headers/Game.h"
#include <iostream>
#include <vector>
#include "../Headers/Bullet.h"

//Default constructor for game
Game::Game() {
  width = 1440;
  height = 800;
  map = TileMap();

  obj_id = 0;
      
  //Load game map
  map.load("Assets/Tileset.png", sf::Vector2u(16, 16), 90, 50);
}

//Default destructor for game
Game::~Game(){

  //clear any dynamically allocated memory for bullets
  for (int i = 0; i < bullets.size(); i++) {
    delete bullets.at(i);
  }


}

//Returns display size
int Game::get_width() { return width; }
int Game::get_height() { return height; }

//Returns map object for rendering
TileMap Game::get_map() { return map; }

//generate unique object ID
int Game::generate_id(){
  obj_id++;
  return obj_id;
}

void Game::set_bullet(Bullet* bullet) { bullets.push_back(bullet); }

//Renders bullets - invisible bullets (from frame) reemoved from rendering queue
void Game::show_bullet(sf::RenderWindow& app) {

  //Iterate over list of shot bullets
  for (int i = 0; i < bullets.size(); i++) {

    //Check if bullets exist within map (otherwise remove from rendering queue)
    if (!bullets.at(i)->isInsideMap(width, height)) {
      delete bullets.at(i);
      bullets.erase(bullets.begin() + i);
      continue;
    }

    //Render moving bullet
    app.draw(bullets.at(i)->shootBullet());
    
  }
}