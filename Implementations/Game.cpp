#include "../Headers/Game.h"
#include <iostream>
#include <vector>
#include "../Headers/Bullet.h"
#include "../Headers/Object.h"
#include <algorithm>
#include <future>
#include "../Headers/Common.h"
#include "../Headers/Person.h"
#include "../Headers/Player.h"

void Game::load_features(){
  int feature_index = 0;
  //TODO: fix magic values
  for(int col = 0; col < width/16; col++){
    for(int row = 0; row < height/16; row++){
      tileFeature* feature = map.get_mapFeatures(width/16,row,col,generate_id());

      if(feature != NULL){
        map_objects[feature_index] = feature;
        feature_index++;
      }
    }
  }
}

//Default constructor for game
Game::Game() {
  width = 1440;
  height = 800;
  map = TileMap();

  obj_id = 0;
          
  //Load game map
  map.load("Assets/Tileset.png", sf::Vector2u(16, 16), 90, 50);
  
  //Load map objects into game
  map_objects = new tileFeature*[91];
  load_features();

  //Load "player" into game
  human = new Player(width, height, generate_id());

  prevDir = 1;

}

//Default destructor for game
Game::~Game(){

  //clear any dynamically allocated memory for bullets
  for (int i = 0; i < bullets.size(); i++) {
    delete bullets.at(i);
  }

  for(int i = 0; i < 105; i++){
    delete map_objects[i];
  }

  delete map_objects;
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

void Game::set_bullet() {

  if(human->canAttack()){
     bullets.push_back(human->attack());  
  }
 
}

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

//Show Player HUD and movement
void Game::renderPlayer(sf::RenderWindow &app){
  human->showAmmo(app, width, height);
  human->showHealth(app, width, height);
  app.draw(human->move());
}

//Checks if player will collide with object
bool Game::checkCollision(movement::Direction direction){
  
  sf::FloatRect player_pos = human->get_bounds();

  int rot = 0;

    switch(direction){
        case movement::up:
            rot=angle::up;
            break;
        case movement::down:
            rot=angle::down;
            break;
        case movement::left:
            rot=angle::left; 
            break;
        case movement::right:
            rot=angle::right;
            break;
    }

  for(int i = 0; i < 91; i++){

    if(isCollided){

      std::cout << "current: " << rot << std::endl;
      std::cout << "prev:    " << prev_dir << std::endl;

      for(int i = 0; i < 91; i++){
        if(human->get_bounds().contains(map_objects[i]->get_bounds().getPosition())){
          isCollided = true;
          break;
        } else {
          isCollided = false;
        }
      }

      if(prev_dir != rot){
        return false;
      } else {
        return true;
      }

    } else if(human->get_bounds().contains(map_objects[i]->get_bounds().getPosition())){
     
     
      collided_tile = map_objects[i];
      prev_dir = human->get_rotation();
      std::cout << "current: " << rot << std::endl;
      std::cout << "prev:    " << prev_dir << std::endl;
      isCollided = true;
      return true;

    }

   
   
    // if(human->get_rotation() == 0.f || human->get_rotation() == 360.f){
    //    std::cout << "C1" << std::endl;
    //   if(abs(human->get_x() - map_objects[i]->get_bounds().getPosition().x + 24) < 5 &&  abs(human->get_y() - map_objects[i]->get_bounds().getPosition().y) < 10)
    //     human->move(sf::Vector2f(-0.2,0));

    // } else if (human->get_rotation() == 90.f){
    //    std::cout << "C2" << std::endl;
    //   if(abs(human->get_x() - map_objects[i]->get_bounds().getPosition().x) < 10 &&  abs(human->get_y() - map_objects[i]->get_bounds().getPosition().y + 24) < 5)
    //    human->move(sf::Vector2f(0,-0.2));

    // } else if (human->get_rotation() == 180.f){
    //   std::cout << "C3" << std::endl;
    //   std::cout << abs(human->get_y() - map_objects[i]->get_bounds().getPosition().y) <<std::endl;
    //   if(abs(human->get_x() - map_objects[i]->get_bounds().getPosition().x - 24) < 15 &&  abs(human->get_y() - map_objects[i]->get_bounds().getPosition().y) < 11)
    //     human->move(sf::Vector2f(0.2,0));

    // } else if (human->get_rotation() == 270.f){
    //    std::cout << "C4" << std::endl;
    //   if(abs(human->get_x() - map_objects[i]->get_bounds().getPosition().x) < 11 &&  abs(human->get_y() - map_objects[i]->get_bounds().getPosition().y - 24) < 15)   
    //     human->move(sf::Vector2f(0,0.2));

    // }


  }
    isCollided = false;
    return false;
}

//Sets Player Movement from Keyboard
void Game::movePlayer(movement::Direction direction){
  if(!checkCollision(direction))
    human->setMovement(direction);


}