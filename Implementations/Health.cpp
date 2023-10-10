#include "../Headers/Health.h"

Health::Health(int id, bool isCollected, float x, float y) : Collectable(id, isCollected, x, y, "Assets/Individual Icons and Particles/Health1.png"){
    hp = 20;
}

int Health::get_health(){
    return hp;
}