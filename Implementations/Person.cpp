#include "../Headers/Person.h"
#include "../Headers/Common.h"

Person::Person(){
    texture.loadFromFile("Assets/Individual Animations/Handgun1.png");
    sprite.setTexture(texture);
    sprite.setPosition(100,100);
    sprite.setOrigin(sf::Vector2f(24.f, 24.f));
    id = "test"; //TODO: Make random UUID
    shoot = false;
    bTexture.loadFromFile("Assets/Individual Icons and Particles/BulletProjectile.png");
    bullet.setTexture(bTexture);
    
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
    shoot = true;

    //Down
    if(sprite.getRotation() == 90.f){
        bullet.setPosition(sprite.getPosition().x-7.5f, sprite.getPosition().y+13);
        bulletDirection = sf::Vector2f(0.f,2.f);
    
    //Up
    } else if(sprite.getRotation() == 270.f){
        bullet.setPosition(sprite.getPosition().x-7.5f, sprite.getPosition().y-30);
        bulletDirection = sf::Vector2f(0.f,-2.f);

    //Left
    }  else if(sprite.getRotation() == 180.f){
        bullet.setPosition(sprite.getPosition().x-30, sprite.getPosition().y-7.5f);
        bulletDirection = sf::Vector2f(-2.f,0.f);

    //Right
    } else if(sprite.getRotation() == 0.f){
        bulletDirection = sf::Vector2f(2.f,0.f);
        bullet.setPosition(sprite.getPosition().x+13, sprite.getPosition().y-7.5f);
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

sf::Sprite Person::shootBullet(){
    if(shoot){
        bullet.move(bulletDirection);
        shoot = false;
        return bullet;
    }
    
}

//TODO: Fix Bullet Shooting
bool Person::showBullet(){
    return shoot;
}
    