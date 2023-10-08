#include "../Headers/Game.h"
#include "../Headers/Person.h"
#include "../Headers/Common.h"
#include "../Headers/Bullet.h"
#include "../Headers/Gun.h"

Person::Person(Game* thisGame){
    texture.loadFromFile("Assets/Individual Animations/Handgun1.png");
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(24.f, 24.f));
    sprite.setPosition(110,110);
    game = thisGame;
    id = game->generate_id(); //TODO: Make random UUID
    passthrough = false;
    gun_inventory[primary] = Gun(true, pistol, game->generate_id());
    health = 100;
    selectedGun = primary;
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

void Person::attack(){ 
    //limit fire rate and check gun has ammo
    if(clock.getElapsedTime().asMilliseconds() > gun_inventory[selectedGun].get_rate() && gun_inventory[selectedGun].get_ammo() > 0){
          Bullet* bullet = new Bullet(&sprite); //Creates new sprite object for bullet
          game->set_bullet(bullet); //Adds bullet to rendering queue
          gun_inventory[selectedGun].shoot(); //Reduces ammo of gun
          clock.restart(); //Restarts fire rate limiter
          
    }
  
};

int Person::get_health(){
    return health;
};

//moves the player and returns the sprite to be rendered
sf::Sprite Person::move(){
    sf::Vector2f pos = sprite.getPosition();

    //TODO: check for collisions using adj x and y and passing Deltas to check if heading in direction of object
    std::cout << "x: " << pos.x / 16 << "y: " << pos.y / 16 << std::endl;

    sprite.setRotation(Rot);
    sprite.move(sf::Vector2f(xDelta,yDelta));
    xDelta = 0;
    yDelta = 0;
    return sprite;
}






    