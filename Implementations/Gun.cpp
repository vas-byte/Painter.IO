#include "../Headers/Gun.h"
#include <SFML/Graphics.hpp>
#include "../Headers/Common.h"

//Constructor used for default gun in player inventory (starting pistol)
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

//Constructor for collectable gun
Gun::Gun(int id, bool isCollected, int fr, float x, float y) : Collectable(id, isCollected, x, y, "Assets/Individual Icons and Particles/Machinegun.png"){
    rate = static_cast<float>(fr);

    if(fr == pistol){
        ammo = 40;
        damage = 15;
    } else {
        ammo = 100;
        damage = 10;
    }  

}

//Default constructor (never used)
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