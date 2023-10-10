#include "../Headers/Bullet.h"


Bullet::Bullet(float x, float y, float rot){
    bTexture.loadFromFile("Assets/Individual Icons and Particles/BulletProjectile.png");
    bullet.setTexture(bTexture);
    isExploded = false;

    setPosition(x,y,rot);
}

//Sets position of bullet (from shooting position) for rendering
void Bullet::setPosition(float x, float y, float rot){
    
    //Down
    if(rot == 90.f){
        bullet.setPosition(x-7.8f, y+13);
        bulletDirection = sf::Vector2f(0.f,2.f);
    
    //Up
    } else if(rot == 270.f){
        bullet.setPosition(x-7.8f, y-30);
        bulletDirection = sf::Vector2f(0.f,-2.f);

    //Left
    }  else if(rot == 180.f){
        bullet.setPosition(x-30, y-7.5f);
        bulletDirection = sf::Vector2f(-2.f,0.f);

    //Right - note game engine does not represent sprite angle as 0 when it first loads hence <1
    } else if(rot == 0.f || rot == 360.f){
        bulletDirection = sf::Vector2f(2.f,0.f);
        bullet.setPosition(x+13, y-7.5f);
    }
}

sf::Sprite Bullet::shootBullet(){
    if(!isExploded)
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

 sf::FloatRect Bullet::get_bounds(){
    return bullet.getGlobalBounds();
 }

//Sets Explosion to true
 void Bullet::set_exploded(){
    isExploded = true;
 }

//returns status of explosion
 bool Bullet::get_exploded(){
    return isExploded;
 }