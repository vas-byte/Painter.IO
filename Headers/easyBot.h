#ifndef EASYBOT_H
#define EASYBOT_H

#include "Person.h"

class EasyBot : public Person {
public:
    EasyBot();
    void update() override;
    void move(movement::Direction direction = static_cast<movement::Direction>(rand() % 4)) override;
    Bullet* attack() override;
};

#endif
