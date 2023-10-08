#include "../Headers/tileFeature.h"

tileFeature::tileFeature(Game* game, float x, float y){
    id=game->generate_id();
    passthrough = false;
    this->x = x;
    this->y = y;
}