#include "../Headers/Player.h"
#include <iostream>
#include <string>


Player::Player(Game* game) : Person(game) {
  font.loadFromFile("Assets/Fonts/arial.ttf");

  btexture.loadFromFile("Assets/Individual Icons and Particles/Bullet.png");
  htexture.loadFromFile("Assets/Individual Icons and Particles/Health1.png");

  bsprite.setTexture(btexture);
  hsprite.setTexture(htexture);
  
  bsprite.setOrigin(sf::Vector2f(8.f, 8.f));
  hsprite.setOrigin(sf::Vector2f(8.f, 8.f));

  bsprite.scale(1.5,1.5);
  hsprite.scale(1.5,1.5);

  bsprite.setPosition(game->get_width() - 170, 0 + 33);
  hsprite.setPosition(game->get_width() - 100, 0 + 33);
}

void Player::showHealth(sf::RenderWindow& app) {
  healthText = sf::Text(std::to_string(health), font, 20);
  healthText.setPosition(game->get_width() - 80, 0 + 20);
  app.draw(healthText);
  app.draw(hsprite);
}

void Player::showAmmo(sf::RenderWindow& app) {
  ammoText = sf::Text(std::to_string(gun_inventory[0].get_ammo()), font, 20);
  ammoText.setPosition(game->get_width() - 150, 0 + 20);
  app.draw(ammoText);
  app.draw(bsprite);
}
