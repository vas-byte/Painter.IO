#include "../Headers/Ammo.h"

Ammo::Ammo(int id, bool isCollected, float x, float y) : Collectable(id, isCollected, x, y, "Assets/Individual Icons and Particles/Bullet.png"){
    bullets = 20;
}

int Ammo::get_bullets(){
    return bullets;
}