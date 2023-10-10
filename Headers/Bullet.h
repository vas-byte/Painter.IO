#ifndef BULLET_H
#define BULLET_H

    #include <SFML/Graphics.hpp>
    #include <iostream>

    class Bullet{
        private:
            sf::Texture bTexture;
            sf::Sprite bullet;
            sf::Vector2f bulletDirection;
            void setPosition(float x, float y, float rot);
            bool isExploded;
            

        public:
            Bullet(float x, float y, float rot);
            
            //Checks bullet is inside map
            bool isInsideMap(int width, int height);

            //Renders bullet
            sf::Sprite shootBullet();

            //Get's positional information about bullet
            sf::FloatRect get_bounds();

            //Update bullet sprite to exploded
            void set_exploded();
            
            //Return if bullet has exploded
            bool get_exploded();
    };

#endif