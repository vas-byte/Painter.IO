#include "../Headers/Ammo.h"

//Sets number of collectable bullets to 20
Ammo::Ammo(int id, bool isCollected, float x, float y) : Collectable(id, isCollected, x, y, "Assets/Individual Icons and Particles/Bullet.png"){
    bullets = 20;
}

//Returns number of bullets collected
int Ammo::get_bullets(){
    return bullets;
}