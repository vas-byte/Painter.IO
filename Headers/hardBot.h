#ifndef HARDBOT_H
#define HARDBOT_H

#include "Person.h"

class HardBot : public Person {
public:
    HardBot();  // constructor
    void update() override;  // overriding the update method
    sf::Sprite move() override;
    void attack() override;  // overriding the attack method for the most frequent and accurate shooting
};

#endif
