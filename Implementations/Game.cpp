#include "../Headers/Game.h"
#include <algorithm>
#include <iostream>
#include <vector>
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

  //Tracks whether or not human object created (for coordinate generation)
  humanInit = false;

  //Tracks number of bots and collectables
  numBots = 0;
  num_collectables = 0;

  //Tracks assigned ID (ensures it is unique)
  obj_id = 0;

  //Resolution
  width = 1440;
  height = 800;

  map = TileMap();

  // Load game map
  map.load("Assets/Tileset.png", sf::Vector2u(16, 16), 90, 50);

  // Load map objects into game
  map_objects = new tileFeature*[91];
  load_features();


  //load collectable items
  collectables = new Collectable*[16];
  load_collectables();

  // Load "human player" into game
  sf::Vector2f player_pos = generate_position();
  human = new Player(width, height, player_pos.x, player_pos.y, generate_id());
  humanInit = true;
 
  //Load boats into game
  bots = new BotBehaviour*[8];
  load_bots();
}

// Default destructor for game
Game::~Game() {

  //clear memory occupied by map tile features inside array
  for (int i = 0; i < num_features; i++) {
    delete map_objects[i];
  }

  //clear memory occupied by collectables (ammo, health, guns) inside array
  for(int i = 0; i < num_collectables; i++){
    delete collectables[i];
  }

  //clear memory occupied by bots inside array
  for(int i = 0; i < numBots; i++){
    delete bots[i];
  }

  //Clear the arrays themselves for the objects above
  delete map_objects;
  delete collectables;
  delete bots;
  delete human;
}

//Load map features (wall tiles) into array
void Game::load_features() {
  int features_index = 0;

  //Loop through number of tiles 
  for (int col = 0; col < width / 16; col++) {
    for (int row = 0; row < height / 16; row++) {

      //Get tile (only if it's a wall tile)
      tileFeature* feature = map.get_mapFeatures(width / 16, row, col, generate_id());

      //Check tile is a wall tile and load into object array
      if (feature != NULL) {
        map_objects[features_index] = feature;
        features_index++;
      }

    }
  }
}

//Load bots into game
void Game::load_bots(){
  
  //Init 6 hard bots
  for(int i = 0; i < 6; i++){
    sf::Vector2f bot_pos = generate_position();
    bots[i] = new HardBot(generate_id(), bot_pos.x, bot_pos.y, width, height);
    numBots++;
  }

  //Init 2 easy bots
  for(int i = 0; i < 2; i++){
    sf::Vector2f bot_pos = generate_position();
    bots[6 + i] = new EasyBot(generate_id(), bot_pos.x, bot_pos.y, width, height);
    numBots++;
  }

}

//Load collectable objects into game
void Game::load_collectables(){

  //Generate random health collectables
  for(int i = 0; i < 4; i++){
    sf::Vector2f pos = generate_position();
    int id = generate_id();
    Health* health = new Health(id, false, pos.x, pos.y);
    collectables[i] = health;
    collectable_health[id] = health;
    num_collectables++;
  }

  //Generate random ammo collectables
  for(int i = 0; i < 8; i++){
    sf::Vector2f pos = generate_position();
    int id = generate_id();
    Ammo* ammo = new Ammo(id, false, pos.x, pos.y);
    collectables[4 + i] = ammo;
    collectable_ammo[id] = ammo;
    num_collectables++;
  }

  //Generate random gun collectables
  for(int i = 0; i < 4; i++){
    sf::Vector2f pos = generate_position();
    int id = generate_id();
    Gun* gun = new Gun(id, false, rapid, pos.x, pos.y);
    collectables[12 + i] = gun;
    collectable_guns[id] = gun;
    num_collectables++;
  }
}

//Generates random position for objects/players in a spot with an empty tile
sf::Vector2f Game::generate_position(){
  srand(time(0));

  while(true){
    
    bool noTile = true;
    bool noCollectable = true;
    bool noBots = true;

    //Generates random position
    int x = 50 + rand() % 1200;
    int y = 50 + rand() % 650;
    
    //Series of checks to ensure random position not already used


    //checks if map tile (wall) has this coordinate
    for(int i = 0; i < num_features; i++){
      if(x == map_objects[i]->get_x() || y == map_objects[i]->get_y()){
        noTile = false;
        break;
      }
    }
    if(!noTile)
      continue;
    
     //checks if a collectable object has this coordinate
    for(int i = 0; i < num_collectables; i++){  
      if(collectables[i]->get_x() == x || collectables[i]->get_y() == y){
        noCollectable = false;
        break;
      }

    }
    if(!noCollectable)
      continue;


    //Checks if a player has this coordinate
    if(humanInit && human->get_x() == x && human->get_y() == y)
      continue;


    //Checks if a bot has this coordinate
    for(int i = 0; i < numBots; i++){
      if(x == bots[i]->get_x() && y == bots[i]->get_y()){
        noBots = false;
        break;
      }
        
    }
    if(!noBots)
      continue;
    
    //If not the coordinate is returned
    return sf::Vector2f(x,y);
  }


};

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
  human->render(app, width, height, map_objects, num_features, human, bots, numBots);
}

// Checks if player is close to any tiles
// Sets Player Movement from Keyboard
void Game::movePlayer(movement::Direction direction) {
  human->move(direction, map_objects, num_features, width, height);
}

//Show collectable objects
void Game::render_objects(sf::RenderWindow &app){
  for(int i = 0; i < num_collectables; i++){
    if(!collectables[i]->get_collected_status())
      collectables[i]->render(app);
  }
}

//Called by human player (to collect nearby objects)
void Game::collectObject(){
  human->collectObject(collectables,num_collectables,collectable_ammo,collectable_health,collectable_guns);
}

//Called by human player (to swap guns)
void Game::swap_gun(){
  human->swapGun();
}


//Shows bots on screen
void Game::render_bots(sf::RenderWindow &app){
  for(int i = 0; i < numBots; i++){
    bots[i]->render(app, width, height, map_objects, num_features, human, bots, numBots);
  }
}

int Game::getHumanPlayerHealth() const {
  return human->getHealth();
}

//Moves the bots after each frame
void Game::move_bots(){
  for(int i = 0; i < numBots; i++){
    bots[i]->move_bot(map_objects,num_features,width,height,human,bots,numBots);
    bots[i]->collectObject(collectables,num_collectables,collectable_ammo,collectable_health,collectable_guns);
  }
}

//Resets game
void Game::reset() {

  //Reset game collectables
  for(int i = 0; i < num_collectables; i++){
    delete collectables[i];
  }

  //Reset bots
  for(int i = 0; i < numBots; i++){
    delete bots[i];
  }

  //Reset number of bots and collectables
  numBots = 0;
  num_collectables = 0;

  //Reset human Object
  delete human;
  humanInit = false;

  //Create new human object
  sf::Vector2f player_pos = generate_position();
  human = new Player(width, height, player_pos.x, player_pos.y, generate_id());
  humanInit = true;

  //Load collectables into collectables array
  load_collectables();

  //Load new bot objects into bots array
  load_bots();
}

//checks if all bots are dead
bool Game::all_bots_dead(){
  for(int i = 0; i < numBots; i++)
    if(bots[i]->get_health() > 0){
      return false;
    }

    return true;
}
