#include "../Headers/Person.h"
#include "../Headers/Common.h"
#include "../Headers/Bullet.h"
#include "../Headers/Gun.h"

Person::Person(int id){
    texture.loadFromFile("Assets/Individual Animations/Handgun1.png");
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(24.f, 24.f));
    sprite.setPosition(110,110);
    gun_inventory[primary] = Gun(true, pistol, id);
    health = 100;
    selectedGun = primary;
    isCollided = false;
};

//Sets direction of player movement (from polling keyboard)
void Person::setMovement(movement::Direction direction){
    switch(direction){
       
        case movement::up:
            yDelta=-0.2;
            xDelta=0;
            Rot=angle::up;
            break;
        case movement::down:
            yDelta=0.2;
            xDelta=0;
            Rot=angle::down;
            break;
        case movement::left:
            xDelta=-0.2;
            yDelta=0;
            Rot=angle::left; 
            break;
        case movement::right:
            xDelta=0.2;
            yDelta=0;
            Rot=angle::right;
            break;
    }

}

void Person::move(sf::Vector2f direction){
    sprite.move(direction.x, direction.y);
}

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
sf::Sprite Person::move(){
    sprite.setRotation(Rot);
    sprite.move(sf::Vector2f(xDelta,yDelta));
    xDelta = 0;
    yDelta = 0;
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

bool Person::get_collision(){
    return isCollided;
}
void Person::set_collision(bool collision_status){
    isCollided = collision_status;
    
}
float Person::get_previous_dir(){
    return prev_dir;
}

void Person::set_previous_dir(float dir){
    prev_dir = dir;
}







    