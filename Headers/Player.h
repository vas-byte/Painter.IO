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
        sf::Texture pistolTexture;
        sf::Texture rapidTexture;

        //Sprites for HUD (from textures)
        sf::Sprite bsprite;
        sf::Sprite hsprite;
        sf::Sprite pistolsprite;
        sf::Sprite rapidsprite;
        
        // 
        sf::Vector2f position;

    public:
        Player(int width, int height, float x, float y, int id);
        Player();

        //Methods used to display HUD stuff
        void showHealth(sf::RenderWindow& app, int width, int height);
        void showAmmo(sf::RenderWindow& app, int width, int height);
        void showGun(sf::RenderWindow& app, int width, int height);

        void setPosition(const sf::Vector2f& position); // Assuming you're using sf::Vector2f for positions
        void setHealth(int health);
        
     
};

#endif