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
        //Constructor called by Person class
        Gun(bool isCollected, int fr, int id);

        //Constructor called by Game class (collectable)
        Gun(int id, bool isCollected, int fr, float x, float y);
        
        //Default (never used)
        Gun();

        //Get gun properties
        int get_ammo();
        int get_damage();
        float get_rate();
        void add_ammo(int ammo);

        //Reduce ammo count by 1
        void shoot();
};

#endif