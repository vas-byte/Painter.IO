#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"

class Player : public Person{
    private:
        sf::Font font;
        sf::Text ammoText;
        sf::Text healthText;
        sf::Texture btexture;
        sf::Texture htexture;
        sf::Sprite bsprite;
        sf::Sprite hsprite;


    public:
        Player(int width, int height, int id);
        Player();
        void showHealth(sf::RenderWindow& app, int width, int height);
        void showAmmo(sf::RenderWindow& app, int width, int height);
     
};

#endif