#ifndef GUN_H
#define GUN_H

#include "Common.h"
#include "Collectable.h"
#include <SFML/Graphics.hpp>

class Gun : public Collectable{
    private:
        float rate;
        int ammo;
        int damage;
    
    public:
        Gun();
        Gun(bool isCollected, int fr);
        int get_ammo();
        int get_damage();
        void shoot();
};

#endif