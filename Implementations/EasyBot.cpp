#include "../Headers/EasyBot.h"
#include "../Headers/BotBehaviour.h"
#include "../Headers/Common.h"
#include "../Headers/Player.h"
#include <unistd.h>

EasyBot::EasyBot(int id, float x, float y, int width, int height) : BotBehaviour(id,x,y)
    {
        //Sets the roam direction to the longest direction to the edge of the map
        set_initial_direction(x,y,width,height);
    }



//Determins whether to roam() the bot or followPlayer()
void EasyBot::move_bot(tileFeature** map_objects, int num_objs, int width, int height, Person* human, BotBehaviour** bots, int numBots){

    //Swap active gun if a better option is available or out of ammo
    swapGun();

    int xDist = abs(human->get_x() - get_x());
    int yDist = abs(human->get_y() - get_y());

    if(xDist < 500 && xDist > 30 && yDist < 100 && yDist > 10){
        followPlayer(human->get_x(), human->get_y(), map_objects, num_objs, width, height);
        return;
    }

    //If close to player move bot away
    if(xDist < 10 && yDist < 10){
        move_away(map_objects, num_objs, human->get_x(),human->get_y(),width,height);
    }
    
    roam(map_objects, num_objs, width, height);
}

//Moves bot randomly
void EasyBot::roam(tileFeature** map_objects, int num_objs, int width, int height) {

  //Applies time restriction on when bot changes direction (prevent sporradic movement)
  if (time_direction.getElapsedTime().asSeconds() >= 1) {
    //Changes bot movement direction
    reset_direction();

    //Reset timer whicb restricts direction of bot movement
    time_direction.restart();
  }

  //Moves bot in direction using move() method from parent class person
  switch (direction) {
    case movement::up:
      Person::move(movement::up, map_objects, num_objs, width, height);
      break;
    case movement::down:
      Person::move(movement::down, map_objects, num_objs, width, height);
      break;
    case movement::left:
      Person::move(movement::left, map_objects, num_objs, width, height);
      break;
    case movement::right:
      Person::move(movement::right, map_objects, num_objs, width, height);
      break;
  }
}

//Follows player strategically (only in Y direction however)
void EasyBot::followPlayer(float x, float y, tileFeature** map_objects, int num_objs, int width, int height) {
    
    //Calculate distance
    int yDelta = (y - get_y());
    
    //Determine what speed to move based on distance
    float spd = 0;
    if(yDelta  > 75){
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