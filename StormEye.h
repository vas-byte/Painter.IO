#ifndef STORMEYE_H
#define STORMEYE_H

#include <SFML/Graphics.hpp>

class StormEye {
public:
    StormEye(float initial_radius, float max_radius);
    void shrink(float amount);
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);
    float getRadius();
    bool isInside(sf::Vector2f& position);

private:
    sf::CircleShape memberCircle;
    float memberMaxRadius;
};

#endif
