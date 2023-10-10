#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"

class Player : public Person{
    private:

        //Text Font
        sf::Font font;

        //Text for HUD
        sf::Text ammoText;
        sf::Text healthText;

        //Textures for HUD
        sf::Texture btexture;
        sf::Texture htexture;

        //Sprites for HUD (from textures)
        sf::Sprite bsprite;
        sf::Sprite hsprite;


    public:
        Player(int width, int height, int id);
        Player();

        //Methods used to display HUD stuff
        void showHealth(sf::RenderWindow& app, int width, int height);
        void showAmmo(sf::RenderWindow& app, int width, int height);
     
};

#endif