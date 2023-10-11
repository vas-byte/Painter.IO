#ifndef MEDIUMBOT_H
#define MEDIUMBOT_H

#include "Person.h"

class MediumBot : public Person {
public:
    MediumBot();  
    void update() override;  // overriding the update method
    sf::Sprite move() override;
    void attack() override;  // overriding the attack method for more frequent and accurate shooting
};

#endif
