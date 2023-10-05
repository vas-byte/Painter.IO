#include "../Headers/Gun.h"
#include <SFML/Graphics.hpp>
#include "../Headers/Common.h"

Gun::Gun() : Collectable(false){
    rate = static_cast<float>(pistol);
    ammo = 40;
    damage = 15;
}

Gun::Gun(bool isCollected, int fr) : Collectable(isCollected){
    rate = static_cast<float>(fr);

    if(fr == 400.f){
        ammo = 40;
        damage = 15;
    } else {
        ammo = 100;
        damage = 10;
    }
   
}

int Gun::get_damage(){
    return damage;
}

int Gun::get_ammo(){
    return ammo;
}

void Gun::shoot(){
    ammo--;
} 