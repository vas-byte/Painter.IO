#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include <SFML/Graphics.hpp>
#include "Object.h"

//Parent class to collectable items such as Ammo, Health and Guns
class Collectable : public Object{
    protected:
        float x;
        float y;
        bool isCollected;
        sf::Sprite rectangle;
        sf::Texture recttexture;
        
    public:
        Collectable(int id, bool isCollected);
        Collectable(int id, bool isCollected, float x, float y, std::string texture);
        float get_x();
        float get_y();
        void render(sf::RenderWindow& app);
        bool get_collected_status();
        void collect();
};

#endif