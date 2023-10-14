#include "../Headers/Person.h"
#include "../Headers/Common.h"
#include "../Headers/Bullet.h"
#include "../Headers/Gun.h"
#include "../Headers/Object.h"

Person::Person(int id, float x, float y){
    texture.loadFromFile("Assets/Individual Animations/Handgun1.png");
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(24.f, 24.f));
    sprite.setPosition(x,y);
    gun_inventory[primary] = Gun(true, pistol, id);
    health = 100;
    selectedGun = primary;
    isCollided = false;
    hasSecondary = false;
};

Person::~Person(){
  //Clear dynamic memory for bullets
  for(Bullet* bullet : bullets){
    delete bullet;
  }
}

//Shoots a bullet
void Person::attack(){ 
    //limit fire rate and check gun has ammo
    if(canAttack()){
          Bullet* bullet = new Bullet(get_x(), get_y(), get_rotation(), gun_inventory[selectedGun].get_damage()); //Creates new sprite object for bullet
          gun_inventory[selectedGun].shoot(); //Reduces ammo of gun
          clock.restart(); //Restarts fire rate limiter
          bullets.push_back(bullet);
    } 
};

//Determins if player has enough ammo and limits fire rate
bool Person::canAttack(){
     if(clock.getElapsedTime().asMilliseconds() > gun_inventory[selectedGun].get_rate() && gun_inventory[selectedGun].get_ammo() > 0){
        return true;
    } else {
        return false;
    }
}

//Returns player health
int Person::get_health(){
    return health;
};

//moves the player
void Person::move(movement::Direction direction, tileFeature** map_objects, int num_objs, int width, int height){

    //if not inside map or collided with an object and resolving the collision don't move
    if(!isInsideMap(direction, width, height) || checkFutureCollision(direction, map_objects, num_objs)) return;

    switch(direction){
        case movement::up:
            sprite.setRotation(angle::up);
            sprite.move(sf::Vector2f(0,-0.2));
            break;
        case movement::down:
            sprite.setRotation(angle::down);
            sprite.move(sf::Vector2f(0,0.2));
            break;
        case movement::left:
            sprite.setRotation(angle::left);
            sprite.move(sf::Vector2f(-0.2,0));
            break;
        case movement::right:    
            sprite.setRotation(angle::right);
            sprite.move(sf::Vector2f(0.2,0));
            break;
    }
}

//Get player position
float Person::get_x(){
    return sprite.getPosition().x;
};

float Person::get_y(){
    return sprite.getPosition().y;
};

//Get player rotation
float Person::get_rotation(){
    return sprite.getRotation();
};

//Collect droplets (ammo, health, guns) if nearby
void Person::collectObject(Collectable** collectables, int num_collectables, std::map<int, Ammo*> ammo, std::map<int, Health*> health, std::map<int, Gun*> guns){
  int id = 0;

  for(int i = 0; i < num_collectables; i++){

    //Checks if object already collected
    if(collectables[i]->get_collected_status())
      continue;

    //Checks if object is close to player
    if(abs(get_x() - collectables[i]->get_x()) < 30 && abs(get_y() - collectables[i]->get_y()) < 30){
      id = collectables[i]->get_id();
    }

  }

//Get the base object from a dictionary
Health* health_obj = health[id];
Ammo* ammo_obj = ammo[id];
Gun* gun_obj = guns[id];


//Determine what the collectable item was and apply it (if possible)
if(health_obj != nullptr){
  updateHealth(health_obj->get_health());
  health_obj->collect();
  return;
}

if(ammo_obj != nullptr){
  this->gun_inventory[selectedGun].add_ammo(ammo_obj->get_bullets());
  ammo_obj->collect();
  return;
  
}

if(gun_obj != nullptr){
 if(hasSecondary)
    return;

 gun_inventory[secondary] = *gun_obj;
 hasSecondary = true;
 gun_obj->collect();
   
 }  
}

//Swaps gun held by player
void Person::swapGun(){
    if(!hasSecondary)
        return;

    if(selectedGun == primary){
        selectedGun = secondary;
    } else {
        selectedGun = primary;
    }
 }

//Detect if player is currently collided against an object
bool Person::detectPlayerCollision(Object* obj) {

  // Note: a distance threshold is applied different depending on the direction
  // the sprite faces since it is rectangular

  //Checks distance between wall object and player (when moving right)
  if (get_rotation() == 0.f || get_rotation() == 360.f) {
    if (abs(get_x() - obj->get_x() + 24) < 5 && abs(get_y() - obj->get_y()) < 14){
          return true;
        }
      
  //Checks distance between wall object and player (when moving down)
  } else if (get_rotation() == 90.f) {
    if (abs(get_x() - obj->get_x()) < 14 && abs(get_y() - obj->get_y() + 24) < 5){
           return true;
        }
     
  //Checks distance between wall object and player (when moving left)
  } else if (get_rotation() == 180.f) {
    if (abs(get_x() - obj->get_x() - 24) < 15 && abs(get_y() - obj->get_y()) < 17){
          return true;
        }
      
  //Checks distance between wall object and player (when moving up)
  } else if (get_rotation() == 270.f) {
    if (abs(get_x() - obj->get_x()) < 17 && abs(get_y() - obj->get_y() - 24) < 15){
          return true;
        }
      
  }

  return false; 
}

// Checks if player will collide with object based on next move
bool Person::checkFutureCollision(movement::Direction direction, tileFeature** map_objects, int num_objs) {
  int next_rot = direction_to_angle(direction);

  //Check if player has already collided
  if (isCollided) {
      
      for (int i = 0; i < num_objs; i++) {

        //Check player is out of range of collided barrier
        if (detectPlayerCollision(map_objects[i])) {
          isCollided = true;
          break;
        } else {
          isCollided = false;
        }
      }

      //Check player is moving away from object
      if (prev_dir != next_rot) {
        return false;
      } else {
        return true;
      }

    //Otherwise check if player will collide with a non "passthrough" object
  }  

  for (int i = 0; i < num_objs; i++) {

    if (detectPlayerCollision(map_objects[i])) {
      prev_dir = get_rotation();
      isCollided = true;
      return true;
    }

  }

  isCollided = false;
  return false;
}

//Check if player inside map
bool Person::isInsideMap(movement::Direction direction, int width, int height){
 bool insideMap = true;

 //Checks if player is outside map bounds
  if(get_x() < 20){
    //Checks if player is heading within bounds (aka not left and further outside)
    if(direction != movement::left){ 
      insideMap = true; 
    } else {
      insideMap = false; 
    }

  }  

  if(get_y() < 20){
    //Checks if player is heading within bounds (aka not left and further outside)
    if(direction != movement::up){ 
      insideMap = true;
    } else {
      insideMap = false;
    }
  
  } 
  
  if(get_x() > width-20){
    //Checks if player is heading within bounds (aka not left and further outside)
    if(direction != movement::right){ 
      insideMap = true;
    } else {
      insideMap = false;
    }
   }
    
  if(get_y() > height - 20){
    //Checks if player is heading within bounds (aka not left and further outside)
    if(direction != movement::down) {
      insideMap = true;
    } else {
      insideMap = false;
    }
  }

  //Special cases for corners of map
  //Top right corner
  if(get_x() < 20 && get_y() < 20){
    if(direction != movement::left && direction != movement::up) {
      insideMap = true;
    } else {
      insideMap = false;
    }
  }

  //Bottom right
  if(get_x() < 20 && get_y() > height - 20){
    //Checks if player is heading within bounds (aka not left and further outside)
    if(direction != movement::left && direction != movement::down) {
      insideMap = true;
    } else {
      insideMap = false;
    }
  }

  //Bottom left
  if(get_x() > width - 20 && get_y() > height - 20){
    //Checks if player is heading within bounds (aka not left and further outside)
    if(direction != movement::right && direction != movement::down) {
      insideMap = true;
    } else {
      insideMap = false;
    }
  }

  //Top left
  if(get_x() > width - 20 && get_y() < 20){
    //Checks if player is heading within bounds (aka not left and further outside)
    if(direction != movement::right && direction != movement::up) {
      insideMap = true;
    } else {
      insideMap = false;
    }
  }
  return insideMap;
}

//Gives the player damage that reduces health
void Person::takeDamage(int damage){
  //Reduces health and sprite opacity
  sprite.setColor(sf::Color(255,255,255,50+health*2));
  health -= damage;
}

//Checks if player still alive
bool Person::isDead(){
  if(health <= 0){
    std::cout << "Dead" << std::endl;
    return true;
  }
  else
    return false;
}

void Person::updateHealth(int health){
  this->health += health;
  if(this->health > 100) this->health = 100;
  sprite.setColor(sf::Color(255,255,255,50+this->health*2));
}







    