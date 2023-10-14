#include "../Headers/HardBot.h"
#include "../Headers/BotBehaviour.h"
#include "../Headers/Common.h"
#include "../Headers/Player.h"
#include <unistd.h>

HardBot::HardBot(int id, float x, float y, int width, int height) : BotBehaviour(id,x,y)
    {
        set_initial_direction(x,y,width,height);
        isAlreadyFollowing = false;
        followX = false;
    }

//Determins whether to roam() the bot or followPlayer()
void HardBot::move_bot(tileFeature** map_objects, int width, int height, Person* human, BotBehaviour** bots){

    //Swap active gun if a better option is available or out of ammo
    swapGun();

    int xDist = abs(human->get_x() - get_x());
    int yDist = abs(human->get_y() - get_y());

    if(xDist < 500 && xDist > 10 && yDist < 150 && yDist > 10){
        followPlayer(human->get_x(), human->get_y(), map_objects, width, height);
        return;
    }

    //If close to player move bot away
    if(xDist < 10 && yDist < 10){
        move_away(map_objects, human->get_x(),human->get_y(),width,height);
    }
    
    roam(map_objects, width, height);
}

//Moves bot randomly
void HardBot::roam(tileFeature** map_objects, int width, int height) {
  
  if(isCollided){
    reset_direction();
    time_direction.restart();
  }

  if (time_direction.getElapsedTime().asSeconds() >= 1) {
    reset_direction();
    time_direction.restart();
  }

  switch (direction) {
    case movement::up:
      Person::move(movement::up, map_objects, width, height);
      break;
    case movement::down:
      Person::move(movement::down, map_objects, width, height);
      break;
    case movement::left:
      Person::move(movement::left, map_objects, width, height);
      break;
    case movement::right:
      Person::move(movement::right, map_objects, width, height);
      break;
  }
}

//Follows player strategically (only in Y direction however)
void HardBot::followPlayer(float x, float y, tileFeature** map_objects, int width, int height) {
    
    if(followX && isAlreadyFollowing){
       followPlayerX(x,y,map_objects,width,height);
    } else if(!followX && isAlreadyFollowing) {
       followPlayerY(x,y,map_objects,width,height);
    }

    //Calculate distance
    int yDelta = (y - get_y());
    int xDelta = (x - get_x());

    //Align with player along a axis (prevents bot from spamming directions)
    if(xDelta < yDelta){
        followX = true;
        isAlreadyFollowing = true;
        followPlayerX(x,y,map_objects,width,height);
    } else {
        followX = false;
        isAlreadyFollowing = true;
        followPlayerY(x,y,map_objects,width,height);
    }
  
}

void HardBot::followPlayerX(float x, float y, tileFeature** map_objects, int width, int height){
    //Determine what speed to move based on distance
    float spd = 0;
    int xDelta = (x - get_x());

    if(xDelta > 150){
        isAlreadyFollowing = false;
    } else if(xDelta  > 75){
        spd = 0.2;
    } else if (xDelta > 50){
        spd = 0.1;
    } else if (xDelta > 25){
        spd = 0.05;
    } else {
        spd = 0.02;
    }

    //Determine which direction to move
    int xDir = (x - get_x()) > 0 ? spd : -1 * spd;

    //Determine which direction to face when moving
    float rot = x - get_y() > 0 ? 90 : 270;

    //move the bot
    sprite.move(xDir,0);
    sprite.setRotation(rot);

    //Attack if y coordinates simmilar
    if(abs(x - get_x()) < 30)
        attack();
}

void HardBot::followPlayerY(float x, float y, tileFeature** map_objects, int width, int height){
    
    //Determine what speed to move based on distance
    float spd = 0;
    int yDelta = (y - get_y());

    if(yDelta > 100){
        isAlreadyFollowing = false;
    } else if(yDelta  > 75){
        spd = 0.2;
    } else if (yDelta > 50){
        spd = 0.1;
    } else if (yDelta > 25){
        spd = 0.05;
    } else {
        spd = 0.02;
    }

    //Determine which direction to move
    int yDir = (y - get_y()) > 0 ? spd : -1 * spd;

    //Determine which direction to face when moving
    float rot = x - get_x() > 0 ? 0 : 180;

    //move the bot
    sprite.move(0,yDir);
    sprite.setRotation(rot);

    //Attack if y coordinates simmilar
    if(abs(y - get_y()) < 20)
        attack();
}