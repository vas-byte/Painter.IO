#ifndef HEALTH_H
#define HEALTH_H

#include "Collectable.h"

//For Health point boosts
class Health : public Collectable{
    private:
        int hp;
    
    public:
        Health(int id, bool isCollected, float x, float y);
        int get_health();
};

#endif