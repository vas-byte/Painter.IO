#include "../Headers/Bullet.h"
#include "../Headers/tileFeature.h"

Bullet::Bullet(float x, float y, float rot, int damage){
    bTexture.loadFromFile("Assets/Individual Icons and Particles/BulletProjectile.png");
    bullet.setTexture(bTexture);
    this->damage = damage;

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

//Moves bullet in direction shot
sf::Sprite Bullet::shootBullet(){
    bullet.move(bulletDirection);
    return bullet;
}

//Checks if SFML still needs to render bullet (is it still visible in the map)
bool Bullet::isInsideMap(int width, int height){
    sf::Vector2f position = bullet.getPosition();
    
    if(position.x > width || position.y > height || position.x < 0 || position.y < 0 )
        return false;
    
    return true;
}

//Check collision with tile
 bool Bullet::checkCollision(tileFeature** map_objects, int num_objs){
  for(int i = 0; i < num_objs; i++){
    
    //Check if bullet is close to any tiles
    if(abs(bullet.getPosition().x - map_objects[i]->get_x()) < 10 && abs(bullet.getPosition().y - map_objects[i]->get_y()) < 10){
      return true;
    }
  }

  return false;
}

//Check collision with generic object (used for player)
 bool Bullet::checkCollision(Object* obj){

  if(abs(bullet.getPosition().x - obj->get_x()) < 16 && abs(bullet.getPosition().y - obj->get_y()) < 16){
    return true;
  } else {
    return false;
  } 

 }

//Get damage of gun that shot bullet
int Bullet::get_damage(){
  return damage;
}