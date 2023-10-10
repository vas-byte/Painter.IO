#ifndef AMMO_H
#define AMMO_H

#include "Collectable.h"

//For ammo droplet boosts
class Ammo : public Collectable{
    private:
        int bullets;
       

    public:
        Ammo(int id, bool isCollected, float x, float y);
        int get_bullets();
};

#endif