#include "../Headers/Object.h"

//Returns unique ID of object
int Object::get_id(){
    return id;
}

//Returns whether object can be penetrated
bool Object::isPassthrough(){
    return passthrough;
};