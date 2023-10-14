#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"
#include "BotBehaviour.h"
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

    public:
        Player(int width, int height, float x, float y, int id);
        Player();

        //Methods used to display HUD stuff
        void showHealth(sf::RenderWindow& app, int width, int height);
        void showAmmo(sf::RenderWindow& app, int width, int height);
        void showGun(sf::RenderWindow& app, int width, int height);
        void render(sf::RenderWindow& app, int width, int height, tileFeature** map_objects, int num_objs, Person* human, BotBehaviour** bots, int numBots);
        
     
};

#endif