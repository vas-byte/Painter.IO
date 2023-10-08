#include "../Headers/Bullet.h"

Bullet::Bullet(sf::Sprite* sprite){
    bTexture.loadFromFile("Assets/Individual Icons and Particles/BulletProjectile.png");
    bullet.setTexture(bTexture);
    

    setPosition(sprite);
}

//Sets position of bullet (from shooting position) for rendering
void Bullet::setPosition(sf::Sprite* sprite){
    
    std::cout << sprite->getRotation() << std::endl;

    //Down
    if(sprite->getRotation() == 90.f){
        bullet.setPosition(sprite->getPosition().x-7.8f, sprite->getPosition().y+13);
        bulletDirection = sf::Vector2f(0.f,2.f);
    
    //Up
    } else if(sprite->getRotation() == 270.f){
        bullet.setPosition(sprite->getPosition().x-7.8f, sprite->getPosition().y-30);
        bulletDirection = sf::Vector2f(0.f,-2.f);

    //Left
    }  else if(sprite->getRotation() == 180.f){
        bullet.setPosition(sprite->getPosition().x-30, sprite->getPosition().y-7.5f);
        bulletDirection = sf::Vector2f(-2.f,0.f);

    //Right - note game engine does not represent sprite angle as 0 when it first loads hence <1
    } else if(sprite->getRotation() == 0.f || sprite->getRotation() < 1.f){
        bulletDirection = sf::Vector2f(2.f,0.f);
        bullet.setPosition(sprite->getPosition().x+13, sprite->getPosition().y-7.5f);
    }
}

sf::Sprite Bullet::shootBullet(){
   
    bullet.move(bulletDirection);
    // std::cout << "Pos" << bullet.getPosition().x << " " << bullet.getPosition().y << std::endl;
    // std::cout << "Direction" << bulletDirection.x << " " << bulletDirection.y << std::endl;
    return bullet;
    
}

//Checks if SFML still needs to render bullet (is it still visible in the map)
bool Bullet::isInsideMap(int width, int height){
    sf::Vector2f position = bullet.getPosition();
    
    if(position.x > width || position.y > height || position.x < 0 || position.y < 0 )
        return false;
    
    return true;
}
