#include "../Headers/Game.h"
#include "../Headers/Person.h"
#include "../Headers/Common.h"
#include "../Headers/Bullet.h"


Person::Person(Game* thisGame){
    texture.loadFromFile("Assets/Individual Animations/Handgun1.png");
    sprite.setTexture(texture);
    sprite.setPosition(100,100);
    sprite.setOrigin(sf::Vector2f(24.f, 24.f));
    id = "test"; //TODO: Make random UUID
    game = thisGame;
    gun_inventory[primary] = Gun();
    health = 100;
    selectedGun = primary;
};

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
    if(clock.getElapsedTime().asMilliseconds() > 400.f && gun_inventory[selectedGun].get_ammo() > 0){
          Bullet* bullet = new Bullet(&sprite); //TODO: Fix shooting
          game->set_bullet(bullet);
          clock.restart();
          gun_inventory[selectedGun].shoot();
    }
  
};

int Person::get_health(){
    return health;
};

sf::Sprite Person::move(){
    sprite.setRotation(Rot);
    sprite.move(sf::Vector2f(xDelta,yDelta));
    xDelta = 0;
    yDelta = 0;
    return sprite;
}






    