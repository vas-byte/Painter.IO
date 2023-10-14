#ifndef BOTBEHAVIOUR_H
#define BOTBEHAVIOUR_H

#include "tileFeature.h"
#include "Ammo.h"
#include "Health.h"
#include "Gun.h"
#include "Common.h"
#include "Person.h"
#include "Object.h"

//Defines common behaviour of easy and hard bots

class BotBehaviour : public Person{
    protected:
        //Moves bot in random direction for 1 second
        virtual void roam(tileFeature** map_objects, int width, int height) = 0;

        //Stratgically follows player for an attack
        virtual void followPlayer(float x, float y, tileFeature** map_objects, int width, int height) = 0;

        //Determins random direction (used by roam)
        void reset_direction();

        //Determins initial roam direction when class is initialized
        void set_initial_direction(float x, float y, int width, int height);
        
        //Stores how long a bot moved in a direction
        sf::Clock time_direction;

        //Stores current bot direction
        movement::Direction direction;

        //Update Health & opacity
        void updateHealth(int health) override;

        //Swap active gun if a better option is available or out of ammo
        void gun_swap();

    public:

        //Determins whether to roam or follow the player
        virtual void move_bot(tileFeature** map_objects, int width, int height, Person* human, BotBehaviour** bots) = 0;

        //Constructor
        BotBehaviour(int id, float x, float y);

        //Renders bot
        void render(sf::RenderWindow& app, int width, int height, tileFeature** map_objects, Person* human, BotBehaviour** bots) override;

        //Allows bot to take damage
        void takeDamage(int damage) override;
};

#endif