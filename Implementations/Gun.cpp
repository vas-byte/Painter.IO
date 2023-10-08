#include "../Headers/Gun.h"
#include <SFML/Graphics.hpp>
#include "../Headers/Common.h"


Gun::Gun(bool isCollected, int fr, int id) : Collectable(id, isCollected){
    rate = static_cast<float>(fr);

    if(fr == pistol){
        ammo = 40;
        damage = 15;
    } else {
        ammo = 100;
        damage = 10;
    }   
}

Gun::Gun() : Collectable(-1, false){
     rate = static_cast<float>(pistol);
     ammo = 40;
     damage = 15;
}

int Gun::get_damage(){
    return damage;
}

int Gun::get_ammo(){
    return ammo;
}

float Gun::get_rate(){
    return rate;
}

void Gun::shoot(){
    ammo--;
} 