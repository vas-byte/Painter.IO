#include "../Headers/BotBehaviour.h"
#include "../Headers/Player.h"

//Virtual constructor for bots - sets them all to blue
BotBehaviour::BotBehaviour(int id, float x, float y) : Person(id,x,y){
    sprite.setColor(sf::Color::Blue);
}

//Virtual destructor for Bots (frees allocated memory for bullets)
BotBehaviour::~BotBehaviour(){
  for(int i = 0; i < bullets.size(); i++){
    delete bullets.at(i);
    bullets.erase(bullets.begin() + i);
  }
}

//randomly generates direction for bot to move (roam)
void BotBehaviour::reset_direction(){
    switch (rand() % 4) {
      case movement::up:
        direction = movement::up;
        break;
      case movement::down:
        direction = movement::down;
        break;
      case movement::left:
        direction = movement::left;
        break;
      case movement::right:
        direction = movement::right;
        break;
    }
}

//Sets initial direction of bot movement based on which direction has the longest distance
//To edge of map
void BotBehaviour::set_initial_direction(float x, float y, int width, int height){

  //Calculate distance to edges of map (top, bottom, left, right)
  int length_left = x;
  int length_right = width - x;
  int length_up = y;
  int length_down = height - y;

  //Calculates horizontal distance to edge, and compares distance to the left & right of the map
  int hoz_space = length_left > length_right ? length_left : length_right;
  bool left_longer = length_left > length_right ? true : false;

  //Calculates vertical distance, and compares distance to the top & bottom of the map
  int vert_space = length_up > length_down ? length_up : length_down;
  bool up_longer = length_up > length_down ? true : false;

  //Sets the bot in the direction of the longest distance to edge of map 
  if (hoz_space > vert_space) {
    if (left_longer)
      direction = movement::left;
    else
      direction = movement::right;
  } else {
    if (up_longer)
      direction = movement::up;
    else
      direction = movement::down;
  }
}

//Renders bot movements & bullets shot
void BotBehaviour::render(sf::RenderWindow& app, int width, int height, tileFeature** map_objects, int num_objs, Person* human, BotBehaviour** bots, int numBots){
  
  //Determines if bullet is in rendering queue
  bool showBullet = true;

  //Skips rendering if bot dead
  if(this->health <= 0)
    return;

  //Renders bot
  app.draw(sprite);

  lastPos = sprite.getPosition();

  //Checks if shot bullets collide with any objects
  for (int i = 0; i < bullets.size(); i++) {

     //Check if collided with player
    if(bullets.at(i)->checkCollision(human)){

      //If so don't render
      human->takeDamage(bullets.at(i)->get_damage());
      showBullet = false;
    }

    //Check if collided with other bots
    for(int j = 0; j < numBots; j++){

      //Do not check for collision with current bot
      if(bots[j]->get_id() == id)
        continue;

      //Check bot is not dead
      if(bots[j]->get_health() <= 0){
        continue;
      }

      //Check if collided with bots
      if(bullets.at(i)->checkCollision(bots[j])){

        //If So do not render & take damage
        bots[j]->takeDamage(bullets.at(i)->get_damage());
        showBullet = false;
      }

    }
  
    //Check if bullet within map (otherwise remove from rendering queue to save compute time)
    if (!bullets.at(i)->isInsideMap(width, height)) {
      showBullet = false;
    }

    //Check if collided with map tiles
    if(bullets.at(i)->checkCollision(map_objects, num_objs)){
      //If so don't render
      showBullet = false;
    }

    //Delete bullets from queue not to be rendered
    if(!showBullet){
      delete bullets.at(i);
      bullets.erase(bullets.begin() + i);
      continue;
    }

    // Render moving bullet (if not collided and within map)
    app.draw(bullets.at(i)->shootBullet());
  }
}

//Overrides takeDamage in person class (due to bots being different colour)
void BotBehaviour::takeDamage(int damage){
  //Reduces bot opacity as damage increases
  sprite.setColor(sf::Color(0,0,255,50+health*2));

  //Reduces player health
  health -= damage;
}

//Overrides updateHealth in person class (due to bots being different colour)
void BotBehaviour::updateHealth(int health){
  this->health += health;
  if(this->health > 100) this->health = 100;
  sprite.setColor(sf::Color(0,0,255,50+this->health*2));
}

//Swap active gun if a better option is available or out of ammo
void BotBehaviour::gun_swap(){

  //If bot has a secondary gun, use it because it's better 
  if(hasSecondary){

    //Set selected gun to secondary
    selectedGun = secondary;

    //Check if secondary out of ammo, switch to primary then
    selectedGun = gun_inventory[secondary].get_ammo() == 0 ? primary : secondary;
  }
}

//Moves bot away from player when they are close
void BotBehaviour::move_away(tileFeature** map_objects, int num_objs, float x, float y, int width, int height){
  //Change direcion if collided with a wall object
  if(!isCollided){
   if(x - get_x() > 0) move(movement::left, map_objects, num_objs, width, height); 
   else move(movement::right, map_objects, num_objs, width, height);
  } else {
    if(y - get_y() > 0) move(movement::up, map_objects, num_objs, width, height); 
    else move(movement::down, map_objects, num_objs, width, height);
  }
}