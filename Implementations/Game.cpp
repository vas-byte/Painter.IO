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
#include "../Headers/HardBot.h"
#include "../Headers/EasyBot.h"

// Default constructor for game
Game::Game() {
  humanInit = false;
  numBots = 0;

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

  // Load "human player" into game
  sf::Vector2f player_pos = generate_position();
  human = new Player(width, height, player_pos.x, player_pos.y, generate_id());
  humanInit = true;
 
  //Load boats into game
  bots = new BotBehaviour*[2];
  sf::Vector2f bot_pos = generate_position();
  bots[0] = new HardBot(generate_id(), bot_pos.x, bot_pos.y, width, height);
  numBots = 1;
  sf::Vector2f bot_pos2 = generate_position();
  bots[1] = new HardBot(generate_id(), bot_pos2.x, bot_pos2.y, width, height);
  numBots = 2;

}

// Default destructor for game
Game::~Game() {
  // clear any dynamically allocated memory

  for (int i = 0; i < 91; i++) {
    delete map_objects[i];
  }

  for(int i = 0; i < 12; i++){
    delete collectables[i];
  }

  delete map_objects;
  delete collectables;
}

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
}

//Generates random position for objects/players in a spot with an empty tile
sf::Vector2f Game::generate_position(){
  srand(time(0));

  while(true){
    
    bool noTile = true;
    bool noCollectable = true;
    bool noBots = true;

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

    if(humanInit && human->get_x() == x && human->get_y() == y)
      continue;

    for(int i = 0; i < 2; i++){
      if(numBots == i || numBots == 0)
        continue;

      if(x == bots[i]->get_x() && y == bots[i]->get_y()){
        noBots = false;
        break;
      }
        
    }

    if(!noBots)
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

// Renders bullets - invisible bullets (from frame) reemoved from rendering
// queue
void Game::shootBullet() {
  human->attack();
}

// Show Player HUD and movement
void Game::renderPlayer(sf::RenderWindow& app) {
  human->showAmmo(app, width, height);
  human->showHealth(app, width, height);
  human->showGun(app, width, height);
  human->render(app, width, height, map_objects, human, bots);
}

// Checks if player is close to any tiles
// Sets Player Movement from Keyboard
void Game::movePlayer(movement::Direction direction) {
  human->move(direction, map_objects, width, height);
}

//Show collectable objects
void Game::render_objects(sf::RenderWindow &app){
  for(int i = 0; i < 12; i++){
    if(!collectables[i]->get_collected_status())
      collectables[i]->render(app);
  }
}

//Called by human player (to collect nearby objects)
void Game::collectObject(){
  human->collectObject(collectables,collectable_ammo,collectable_health,collectable_guns);
}

//Called by human player (to swap guns)
void Game::swap_gun(){
  human->swapGun();
}

void Game::render_bots(sf::RenderWindow &app){
  for(int i = 0; i < 2; i++){
    bots[i]->render(app, width, height, map_objects, human, bots);
  }
}

void Game::move_bots(){
  for(int i = 0; i < 2; i++){
    bots[i]->move_bot(map_objects,width,height,human,bots);
    bots[i]->collectObject(collectables,collectable_ammo,collectable_health,collectable_guns);
  }
}