#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>

class Object{
    protected:
        bool passthrough;
        int id;
    public:
        int get_id();
};

#endif