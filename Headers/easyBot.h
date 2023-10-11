#ifndef EASYBOT_H
#define EASYBOT_H

#include "Person.h"

class EasyBot : public Person {
public:
    EasyBot();  // constructor
    void update() override;  // overriding the update method
    sf::Sprite move() override;
    void attack() override;  // overriding the attack method for shooting frequency and accuracy
};

#endif
