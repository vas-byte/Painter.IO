#include "../Headers/Game.h"

#include <algorithm>
#include <future>
#include <iostream>
#include <vector>

#include "../Headers/Bullet.h"
#include "../Headers/Common.h"
#include "../Headers/Object.h"
#include "../Headers/Person.h"
#include "../Headers/Player.h"

void Game::load_features() {
  //Array index
  int feature_index = 0;

  //Loop through number of tiles 
  for (int col = 0; col < width / 16; col++) {
    for (int row = 0; row < height / 16; row++) {

      //Get tile (only if it's a wall tile)
      tileFeature* feature = map.get_mapFeatures(width / 16, row, col, generate_id());

      //Check tile is a wall tile and load into object array
      if (feature != NULL) {
        map_objects[feature_index] = feature;
        feature_index++;
      }

    }
  }
}

// Default constructor for game
Game::Game() {
  width = 1440;
  height = 800;
  map = TileMap();

  obj_id = 0;

  // Load game map
  map.load("Assets/Tileset.png", sf::Vector2u(16, 16), 90, 50);

  // Load map objects into game
  map_objects = new tileFeature*[91];
  load_features();

  // Load "player" into game
  human = new Player(width, height, generate_id());


}

// Default destructor for game
Game::~Game() {
  // clear any dynamically allocated memory for bullets
  for (int i = 0; i < bullets.size(); i++) {
    delete bullets.at(i);
  }

  for (int i = 0; i < 91; i++) {
    delete map_objects[i];
  }

  delete map_objects;
}

// Returns display size
int Game::get_width() { return width; }
int Game::get_height() { return height; }

// Returns map object for rendering
TileMap Game::get_map() { return map; }

// generate unique object ID
int Game::generate_id() {
  obj_id++;
  return obj_id;
}

void Game::set_bullet() {
  if (human->canAttack()) {
    bullets.push_back(human->attack());
  }
}

// Renders bullets - invisible bullets (from frame) reemoved from rendering
// queue
void Game::show_bullet(sf::RenderWindow& app) {
  // Iterate over list of shot bullets
  for (int i = 0; i < bullets.size(); i++) {
    // Check if bullets exist within map (otherwise remove from rendering queue)
    if (!bullets.at(i)->isInsideMap(width, height)) {
      delete bullets.at(i);
      bullets.erase(bullets.begin() + i);
      continue;
    }

    // Render moving bullet
    app.draw(bullets.at(i)->shootBullet());
  }
}

// Show Player HUD and movement
void Game::renderPlayer(sf::RenderWindow& app) {
  human->showAmmo(app, width, height);
  human->showHealth(app, width, height);
  app.draw(human->move());
}

// Checks if player is close to any tiles
bool Game::detectPlayerCollision(Object* obj) {
  if (human->get_rotation() == 0.f || human->get_rotation() == 360.f) {
    if (abs(human->get_x() - obj->get_bounds().getPosition().x + 24) < 5 &&
        abs(human->get_y() - obj->get_bounds().getPosition().y) < 14){
          // std::cout << "C1" << std::endl;
          return true;
        }
      

  } else if (human->get_rotation() == 90.f) {
    if (abs(human->get_x() - obj->get_bounds().getPosition().x) < 14 &&
        abs(human->get_y() - obj->get_bounds().getPosition().y + 24) < 5){
          // std::cout << "C2" << std::endl;
           return true;
        }
     

  } else if (human->get_rotation() == 180.f) {
    if (abs(human->get_x() - obj->get_bounds().getPosition().x - 24) < 15 &&
        abs(human->get_y() - obj->get_bounds().getPosition().y) < 17){
          // std::cout << "C3" << std::endl;
          return true;
        }
      

  } else if (human->get_rotation() == 270.f) {
    if (abs(human->get_x() - obj->get_bounds().getPosition().x) < 17 &&
        abs(human->get_y() - obj->get_bounds().getPosition().y - 24) < 15){
          // std::cout << "C4" << std::endl;
          return true;
        }
      
  }
}

// Checks if player will collide with object
bool Game::checkCollision(movement::Direction direction) {
  int next_rot = direction_to_angle(direction);

  for (int i = 0; i < 91; i++) {

    //Check if player has already collided
    if (human->get_collision()) {
      for (int i = 0; i < 91; i++) {

        //Check player is out of range of collided barrier
        if (detectPlayerCollision(map_objects[i])) {
          human->set_collision(true);
          break;
        } else {
          human->set_collision(false);
        }
      }

      // std::cout << next_rot << std::endl;
      // std::cout << human->get_previous_dir() << std::endl;
      //Check player is moving away from object
      if (human->get_previous_dir() != next_rot) {
        return false;
      } else {
        return true;
      }

    //Otherwise check if player will collide with a non "passthrough" object
    } else if (detectPlayerCollision(map_objects[i])) {
      human->set_previous_dir(human->get_rotation());
      human->set_collision(true);
      return true;
    }

  }

  human->set_collision(false);
  return false;
}

//Check if player inside map
bool Game::isInsideMap(movement::Direction direction){
 
 //Checks if player is outside map bounds
  if(human->get_x() < 20){
    //Checks if map is heading within bounds (aka not left and further outside)
    if(direction != movement::left){ 
      return true; 
    } else {
      return false; 
    }

  } else if(human->get_x() > width-20){
    //Checks if map is heading within bounds (aka not left and further outside)
    if(direction != movement::right){ 
      return true;
    } else {
      return false;
    }
    
  } else if(human->get_y() < 20){
    //Checks if map is heading within bounds (aka not left and further outside)
    if(direction != movement::up){ 
      return true;
    } else {
      return false;
    }
  
  } else if(human->get_y() > height - 20){
    //Checks if map is heading within bounds (aka not left and further outside)
    if(direction != movement::down) {
      return true;
    } else {
      return false;
    }

  //If player not outside x,y coords of map it must be inside the map
  } else {
    return true;
  }
  
}

// Sets Player Movement from Keyboard
void Game::movePlayer(movement::Direction direction) {
  if (isInsideMap(direction) && !checkCollision(direction)) human->setMovement(direction);
}