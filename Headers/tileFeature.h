#ifndef TILEFEATURE_H
#define TILEFEATURE_H

#include "Object.h"
#include "Game.h"

class tileFeature : public Object{
    public:
        float x;
        float y;
        tileFeature(Game* game, float x, float y);
};

#endif