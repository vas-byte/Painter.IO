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
        Player(Game* game);
        void showHealth(sf::RenderWindow& app);
        void showAmmo(sf::RenderWindow& app);
     
};

#endif