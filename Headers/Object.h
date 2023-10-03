#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

class Object{
    protected:
        bool takesDamage;
        std::string id;
    public:
        std::string get_id();
};

#endif