#ifndef EASYBOT_H
#define EASYBOT_H

#include "BotBehaviour.h"
#include "Person.h"
#include "Common.h"

//Used to control the movemnet/behaviour of an Easy Attack bot
class EasyBot : public BotBehaviour {
    private:
        //Move the bot randomly
         void roam(tileFeature** map_objects, int num_objs, int width, int height);

         //Move the bot strategically to attack player
         void followPlayer(float x, float y, tileFeature** map_objects, int num_objs, int width, int height);
    
    public:
        EasyBot(int id, float x, float y, int width, int height);
     

        //Called by Game class - it decides whether to call roam() or followPlayer()
        void move_bot(tileFeature** map_objects, int num_objs, int width, int height, Person* human, BotBehaviour** bots, int numBots);
        
};

#endif