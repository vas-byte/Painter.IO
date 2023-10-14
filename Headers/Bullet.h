#ifndef BULLET_H
#define BULLET_H

    #include <SFML/Graphics.hpp>
    #include <iostream>
    #include "tileFeature.h"
    #include "Object.h"

    //Used to store information about fired bullet
    class Bullet{
        private:
            //Stores bullet texture
            sf::Texture bTexture;

            //Bullet Sprite
            sf::Sprite bullet;

            //Stores bullet direction
            sf::Vector2f bulletDirection;

            //Sets bullet position (relative to player) - called by constrcutor
            void setPosition(float x, float y, float rot);

            //Stores what damage the fired bullet does (ie what gun shot it)
            int damage;
            

        public:
            Bullet(float x, float y, float rot, int damage);
            
            //Checks bullet is inside map
            bool isInsideMap(int width, int height);

            //Renders bullet
            sf::Sprite shootBullet();

            //Check if bullet has collided with map objects
            bool checkCollision(tileFeature** map_objects);

            //Check collision with any entity derrived from Object class
            bool checkCollision(Object* object);

            //Retrieves damage of fired bullet (changes with gun)
            int get_damage();
    };

#endif