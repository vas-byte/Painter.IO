#include "../Headers/Game.h"
#include <iostream>
#include <vector>
#include "../Headers/Bullet.h"
#include <fstream>
#include <nlohmann/json.hpp>

Game::Game() {
  width = 1440;
  height = 800;
  map = TileMap();

  obj_id = 0;

  //init JSON object
  nlohmann::json j;
  std::ifstream ifs("State/map.json");

  //open JSON file
  if (!ifs.is_open())
    {
        //return false;;
    }

  //Write file to JSON object
  ifs >> j;

  //Close file IO
  ifs.close();

  // define the level with an array of tile indices
  int level[4500];

  //index in array for map (tile indicies)
  int i = 0;

  //Loads map from JSON file with list of tile indices
  for (int elem : j["map"]){
    level[i] = elem;
    i++;
  }
      
  map.load("Assets/Tileset.png", sf::Vector2u(16, 16), level, 90, 50);
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