#include "StormEye.h"

StormEye::StormEye(float initial_radius, float max_radius) : memberMaxRadius(max_radius) {
    memberCircle.setRadius(initial_radius);
    memberCircle.setFillColor(sf::Color::Transparent);
    memberCircle.setOutlineColor(sf::Color::Blue);
    memberCircle.setOutlineThickness(5);
}

void StormEye::shrink(float amount) {
    float new_radius = getRadius() - amount;
    memberCircle.setRadius(std::max(new_radius, 0.0f));
}

void StormEye::setPosition(float x, float y) {
    memberCircle.setPosition(x, y);
}

void StormEye::draw(sf::RenderWindow& window) {
    window.draw(memberCircle);
}

float StormEye::getRadius() {
    return memberCircle.getRadius();
}

bool StormEye::isInside(const sf::Vector2f& position) {
    sf::Vector2f diff = position - memberCircle.getPosition();
    return (diff.x * diff.x + diff.y * diff.y) <= (memberCircle.getRadius() * memberCircle.getRadius());
}