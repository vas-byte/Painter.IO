#include "../Headers/Person.h"
#include "../Headers/Common.h"
#include "../Headers/Bullet.h"
#include "../Headers/Gun.h"

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

Bullet* Person::attack(){ 
    //limit fire rate and check gun has ammo
    if(canAttack()){
          Bullet* bullet = new Bullet(get_x(), get_y(), get_rotation()); //Creates new sprite object for bullet
          gun_inventory[selectedGun].shoot(); //Reduces ammo of gun
          clock.restart(); //Restarts fire rate limiter
          return bullet;
    } else {
        return nullptr;
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

int Person::get_health(){
    return health;
};

//moves the player and returns the sprite to be rendered
void Person::move(movement::Direction direction){
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

void Person::update() {
}

sf::Sprite Person::getSprite() {
    return sprite;  
}


//Get player position
float Person::get_x(){
    return sprite.getPosition().x;
};

float Person::get_y(){
    return sprite.getPosition().y;
};

float Person::get_rotation(){
    return sprite.getRotation();
};

sf::FloatRect Person::get_bounds(){
   return sprite.getGlobalBounds();
}


//Stores whether player is currently colliding with wall
bool Person::get_collision(){
    return isCollided;
}

//Updates player state about collision with wall
void Person::set_collision(bool collision_status){
    isCollided = collision_status;
    
}

//Retrieves player position before colliding
float Person::get_previous_dir(){
    return prev_dir;
}


//Update player position prior to collision event
void Person::set_previous_dir(float dir){
    prev_dir = dir;
}

//Accept collectables
bool Person::accept_collectables(Gun* gun){
    if(hasSecondary)
        return false;
    
    gun_inventory[secondary] = *gun;
    hasSecondary = true;
    return true;
}

bool Person::accept_collectables(Health* health){
    this->health += health->get_health();

    if(this->health > 100)
        this->health = 100;

    return true;
}

bool Person::accept_collectables(Ammo* ammo){
    this->gun_inventory[selectedGun].add_ammo(ammo->get_bullets()); 
    return true;
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

//Renders player
 void Person::render(sf::RenderWindow& app){
    app.draw(sprite);
 }

// damage implementation
void Person::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0; // ensure health doesn't go negative
}

// to check if person is at 0 health (therefore dead)
bool Person::isDead() {
    return health <= 0;
}

void Person::setMovement(movement::Direction direction) {
    currentDirection = direction;
}

Bullet* Person::shootBullet() {
    return attack();  
}






    