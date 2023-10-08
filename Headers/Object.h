#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

class Object{
    protected:
        bool takesDamage;
        int id;
    public:
        int get_id();
};

#endif