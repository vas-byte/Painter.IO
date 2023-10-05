#ifndef BULLET_H
#define BULLET_H

    #include <SFML/Graphics.hpp>
    #include <iostream>

    class Bullet{
        private:
            sf::Texture bTexture;
            sf::Sprite bullet;
            sf::Vector2f bulletDirection;
            void setPosition(sf::Sprite* sprite);

        public:
            Bullet(sf::Sprite* sprite);
            sf::Sprite shootBullet();
            bool isInsideMap(int width, int height);
    };

#endif