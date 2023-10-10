#include "../Headers/Player.h"
#include <iostream>
#include <string>


Player::Player(int width, int height, float x, float y, int id) : Person(id, x, y) {
  //Load font for HUD text
  font.loadFromFile("Assets/Fonts/arial.ttf");

  //Load images to be used in HUD
  btexture.loadFromFile("Assets/Individual Icons and Particles/Bullet.png");
  htexture.loadFromFile("Assets/Individual Icons and Particles/Health1.png");
  pistolTexture.loadFromFile("Assets/Individual Icons and Particles/Handgun.png");
  rapidTexture.loadFromFile("Assets/Individual Icons and Particles/Machinegun.png");
  bsprite.setTexture(btexture);
  hsprite.setTexture(htexture);
  pistolsprite.setTexture(pistolTexture);
  rapidsprite.setTexture(rapidTexture);

  //Set position and size of HUD images
  bsprite.setOrigin(sf::Vector2f(8.f, 8.f));
  hsprite.setOrigin(sf::Vector2f(8.f, 8.f));
  pistolsprite.setOrigin(sf::Vector2f(8.f, 8.f));
  pistolsprite.setOrigin(sf::Vector2f(16.f, 8.f));
  bsprite.scale(1.5,1.5);
  hsprite.scale(1.5,1.5);
  pistolsprite.scale(1.5,1.5);
  rapidsprite.scale(1.5,1.5);
  bsprite.setPosition(width - 170, 0 + 33);
  hsprite.setPosition(width - 100, 0 + 33);
  pistolsprite.setPosition(width - 200, 0 + 35);
  rapidsprite.setPosition(width - 240, 0 + 23);
}

// Default constructor for player (never used)
Player::Player() : Person(-1,110,110) {
 
}

//Used to update health in the HUD
void Player::showHealth(sf::RenderWindow& app, int width, int height) {
  healthText = sf::Text(std::to_string(health), font, 20);
  healthText.setPosition(width - 85, 0 + 20);
  app.draw(healthText);
  app.draw(hsprite);
}

//Used to update ammo count in HUD
void Player::showAmmo(sf::RenderWindow& app, int width, int height) {
  ammoText = sf::Text(std::to_string(gun_inventory[selectedGun].get_ammo()), font, 20);
  ammoText.setPosition(width - 155, 0 + 20);
  app.draw(ammoText);
  app.draw(bsprite);
}

//Displays currently selected gun in HUD
void Player::showGun(sf::RenderWindow& app, int width, int height){
  
  //positions selected gun closer to bullet sprite
  if(selectedGun == primary){
    pistolsprite.setPosition(width - 200, 0 + 35);
    rapidsprite.setPosition(width - 300, 0 + 23);
  } else {
    pistolsprite.setPosition(width - 265, 0 + 35);
    rapidsprite.setPosition(width - 240, 0 + 23);
  }

  //Renders pistol sprite
  app.draw(pistolsprite);

  //Only renders machine gun sprite if player has the machine gun
  if(hasSecondary)
    app.draw(rapidsprite);
}
