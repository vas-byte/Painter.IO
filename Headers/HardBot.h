#ifndef HARDBOT_H
#define HARDBOT_H

#include "BotBehaviour.h"
#include "Person.h"
#include "Common.h"

class HardBot : public BotBehaviour{
    private:
        //Move the bot randomly
        void roam(tileFeature** map_objects, int num_objs, int width, int height);

        //Move the bot strategically to attack player
        void followPlayer(float x, float y, tileFeature** map_objects, int num_objs, int width, int height);
        void followPlayerX(float x, float y, tileFeature** map_objects, int num_objs, int width, int height);
        void followPlayerY(float x, float y, tileFeature** map_objects, int num_objs, int width, int height);

        //Determins which direction to follow player
        bool followX;
        bool isAlreadyFollowing;
    
    public:
        HardBot(int id, float x, float y, int width, int height);   

        //Called by Game class - it decides whether to call roam() or followPlayer()
        void move_bot(tileFeature** map_objects, int num_objs, int width, int height, Person* human, BotBehaviour** bots, int numBots);
};

#endif