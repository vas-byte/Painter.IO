#include "../Headers/Game.h"
#include <algorithm>
#include <future>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "../Headers/Bullet.h"
#include "../Headers/Common.h"
#include "../Headers/Object.h"
#include "../Headers/Person.h"
#include "../Headers/Player.h"
#include "../Headers/Health.h"
#include "../Headers/Ammo.h"
#include "../Headers/easyBot.h"

//Load map features (wall tiles) into array
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
  //     // need to add
  //     if(!gameFont.loadFromFile("path/to/font.ttf")) {
  //       std::cerr << "Failed to load font." << std::endl;
  //     }

  //     // Load game over sound (need to add)
  //     if(!gameOverSoundBuffer.loadFromFile("path/to/sound.wav")) {
  //       std::cerr << "Failed to load game over sound." << std::endl;
  //     }
  //     gameOverSound.setBuffer(gameOverSoundBuffer);
  //   }
  // }
}

//Generates random position for objects/players in a spot with an empty tile
sf::Vector2f Game::generate_position(){
  srand(time(0));

  while(true){
    bool noTile = true;
    bool noCollectable = true;

    int x = 50 + rand() % 1200;
    int y = 50 + rand() % 650;

    for(int i = 0; i < 91; i++){
      if(x == map_objects[i]->get_x() || y == map_objects[i]->get_y()){
        noTile = false;
        break;
      }
    }

    if(!noTile)
      continue;
    
    for(int i = 0; i < 12; i++){
      if(collectables[i] == nullptr)
        continue;
      
      if(collectables[i]->get_x() == x || collectables[i]->get_y() == y){
        noCollectable = false;
        break;
      }

    }

    if(!noCollectable)
      continue;
    
    return sf::Vector2f(x,y);
  }


};

//Load collectable objects into game
void Game::load_collectables(){

  //Generate random health collectables
  for(int i = 0; i < 4; i++){
    sf::Vector2f pos = generate_position();
    int id = generate_id();
    Health* health = new Health(id, false, pos.x, pos.y);
    collectables[i] = health;
    collectable_health[id] = health;
  }

  //Generate random ammo collectables
  for(int i = 0; i < 4; i++){
    sf::Vector2f pos = generate_position();
    int id = generate_id();
    Ammo* ammo = new Ammo(id, false, pos.x, pos.y);
    collectables[4 + i] = ammo;
    collectable_ammo[id] = ammo;
  }

  //Generate random gun collectables
  for(int i = 0; i < 4; i++){
    sf::Vector2f pos = generate_position();
    int id = generate_id();
    Gun* gun = new Gun(id, false, rapid, pos.x, pos.y);
    collectables[8 + i] = gun;
    collectable_guns[id] = gun;
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


  //load collectable items
  collectables = new Collectable*[12];
  load_collectables();

  for (int i = 0; i < bots.size(); i++) {
      bots.push_back(new EasyBot());
  }

  // Load "human player" into game
  sf::Vector2f player_pos = generate_position();
  human = new Player(width, height, player_pos.x, player_pos.y, generate_id());
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

  for(int i = 0; i < 12; i++){
    delete collectables[i];
  }

  for (EasyBot* bot : bots) {
    delete bot;
  }

  delete map_objects;
  delete collectables;
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

bool Game::bulletCollision(Bullet* bullet){
  for(int i = 0; i < 91; i++){
    if(map_objects[i]->get_bounds().getGlobalBounds().intersects(bullet->get_bounds())){
      return true;
    }
  }

  return false;
}

//Adds bullet to global render queue
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

    //Check if exploded (if so remove from render queue)
    if (bullets.at(i)->get_exploded()) {
      delete bullets.at(i);
      bullets.erase(bullets.begin() + i);
      continue;
    }

    // Check if bullets exist within map (otherwise remove from rendering queue)
    if (!bullets.at(i)->isInsideMap(width, height)) {
      delete bullets.at(i);
      bullets.erase(bullets.begin() + i);
      continue;
    }

    //Check if collided
   if(bulletCollision(bullets.at(i))){
      bullets.at(i)->set_exploded();
   }

    // Render moving bullet (if not exploded)
    app.draw(bullets.at(i)->shootBullet());
  }
}

// Show Player HUD and movement
void Game::renderPlayer(sf::RenderWindow& app) {
  human->showAmmo(app, width, height);
  human->showHealth(app, width, height);
  human->showGun(app, width, height);
  human->render(app);
}

// Checks if player is close to any tiles
bool Game::detectPlayerCollision(Person* entity, Object* obj) {

  // Note: a distance threshold is applied different depending on the direction
  // the sprite faces since it is rectangular

  //Checks distance between wall object and player (when moving right)
  if (entity->get_rotation() == 0.f || entity->get_rotation() == 360.f) {
    if (abs(entity->get_x() - obj->get_bounds().getPosition().x + 24) < 5 && abs(entity->get_y() - obj->get_bounds().getPosition().y) < 14){
          return true;
        }
      
  //Checks distance between wall object and player (when moving down)
  } else if (entity->get_rotation() == 90.f) {
    if (abs(entity->get_x() - obj->get_bounds().getPosition().x) < 14 && abs(entity->get_y() - obj->get_bounds().getPosition().y + 24) < 5){
           return true;
        }
     
  //Checks distance between wall object and player (when moving left)
  } else if (entity->get_rotation() == 180.f) {
    if (abs(entity->get_x() - obj->get_bounds().getPosition().x - 24) < 15 && abs(entity->get_y() - obj->get_bounds().getPosition().y) < 17){
          return true;
        }
      
  //Checks distance between wall object and player (when moving up)
  } else if (entity->get_rotation() == 270.f) {
    if (abs(entity->get_x() - obj->get_bounds().getPosition().x) < 17 && abs(entity->get_y() - obj->get_bounds().getPosition().y - 24) < 15){
          return true;
        }
      
  }

  return false; 
}

// Checks if player will collide with object
bool Game::checkCollision(movement::Direction direction) {
  int next_rot = direction_to_angle(direction);

  for (int i = 0; i < 91; i++) {

    //Check if player has already collided
    if (human->get_collision()) {
      
      for (int i = 0; i < 91; i++) {

        //Check player is out of range of collided barrier
        if (detectPlayerCollision(human, map_objects[i])) {
          human->set_collision(true);
          break;
        } else {
          human->set_collision(false);
        }
      }

      //Check player is moving away from object
      if (human->get_previous_dir() != next_rot) {
        return false;
      } else {
        return true;
      }

    //Otherwise check if player will collide with a non "passthrough" object
    } else if (detectPlayerCollision(human, map_objects[i])) {
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
    //Checks if player is heading within bounds (aka not left and further outside)
    if(direction != movement::left){ 
      return true; 
    } else {
      return false; 
    }

  } else if(human->get_x() > width-20){
    //Checks if player is heading within bounds (aka not left and further outside)
    if(direction != movement::right){ 
      return true;
    } else {
      return false;
    }
    
  } else if(human->get_y() < 20){
    //Checks if player is heading within bounds (aka not left and further outside)
    if(direction != movement::up){ 
      return true;
    } else {
      return false;
    }
  
  } else if(human->get_y() > height - 20){
    //Checks if player is heading within bounds (aka not left and further outside)
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
  if(isInsideMap(direction) && !checkCollision(direction)) human->move(direction);
}

//Show collectable objects
void Game::render_objects(sf::RenderWindow &app){
  for(int i = 0; i < 12; i++){
    if(!collectables[i]->get_collected_status())
      collectables[i]->render(app);
  }
}

void Game::spawnBot() {
    EasyBot* newBot = new EasyBot;
    bots.push_back(newBot);
}


//Collect any nearby objects
void Game::collectObject(Person* player){

  int id = 0;

  for(int i = 0; i < 12; i++){

    //Checks if object already collected
    if(collectables[i]->get_collected_status())
      continue;

    //Checks if object is close to player
    if(abs(player->get_x() - collectables[i]->get_x()) < 30 && abs(player->get_y() - collectables[i]->get_y()) < 30){
      id = collectables[i]->get_id();
    }

  }

//Get the base object from a dictionary
Health* health = collectable_health[id];
Ammo* ammo = collectable_ammo[id];
Gun* gun = collectable_guns[id];


//Pass base object to Person class
if(health != nullptr){
  if(player->accept_collectables(health)){
    health->collect();
    return;
  }  
}

if(ammo != nullptr){
  if(player->accept_collectables(ammo)){
    ammo->collect();
    return;
  }
}

if(gun != nullptr){
 if(player->accept_collectables(gun)){
    gun->collect();
    return;
 }  
}

if (bulletHitsPlayer) {
    player->takeDamage(bulletDamage);
    if (player->isDead()) {
        gameOver();
    }
}

}

void Game::updateBots() {
    for (EasyBot* bot : bots) {
        bot->update();
    }
}

void Game::renderBots(sf::RenderWindow &window) {
    for (EasyBot* bot : bots) {
        window.draw(bot->getSprite());
    }
}

//Called by human player (to collect nearby objects)
void Game::collectObject(){
  collectObject(human);
}

//Called by human player (to swap guns)
void Game::swap_gun(){
  human->swapGun();
}

void Game::gameOver() {
    // Display a game-over message
    sf::Text gameOverText;
    gameOverText.setString("GAME OVER");
    gameOverText.setFont(gameFont); 
    gameOverText.setPosition(width / 2, height / 2); 
    gameOverText.setCharacterSize(24); 
    gameOverText.setFillColor(sf::Color::Red); 

    // Play the game-over sound (assuming you have one)
    gameOverSound.play();

    // Refresh the window to show the game over screen
    window.display();

    sf::sleep(sf::seconds(3)); 
    restartGame();
}

void Game::restartGame() {
    // Reset player attributes
    sf::Vector2f player_pos = generate_position();
    human->setPosition(player_pos); // Assuming you have a setPosition function
    human->setHealth(100); // Reset health. Assuming you have a setHealth function
    // ... reset other attributes like inventory, score, etc.

    // Reload the level/map and all collectables and states
    map = TileMap(); // Reload the map
    map.load("Assets/Tileset.png", sf::Vector2u(16, 16), 90, 50);
    load_features();  // Reload features
    load_collectables(); // Reload collectables

    // Clear the window and display the restarted game state
    window.clear();
    window.display();

}
