#include "../Headers/Game.h"
#include "../Headers/HardBot.h"
#include "../Headers/EasyBot.h"
#include "../Headers/Ammo.h"
#include "../Headers/Health.h"
#include "../Headers/Gun.h"
#include "../Headers/Bullet.h"
#include <thread>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

//Test 1: Tests that window rendering player successfuly launches
bool testPlayerRender(){
    Game game;
    try {

        //Create sf window
        sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");

        //Unit test timeout
        const sf::Time freezeLength{ sf::seconds(5.f) };
        sf::Clock freezeClock;

        //Keeps frame open for 5 seconds (aka set time)
        while (freezeClock.getElapsedTime() < freezeLength)
        {
            sf::Event event;
            window.pollEvent(event);

            //Draws Player + HUD
            game.renderPlayer(window);
            window.display();
        }
        return true;
    } catch (int x ){
        return false;
    }
}

//Test 2: Tests that window rendering bots successfuly launches
bool testBotRender(){
    Game game;
    try {

        //Create sf window
        sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");

        //Unit test timeout
        const sf::Time freezeLength{ sf::seconds(5.f) };
        sf::Clock freezeClock;

        //Keeps frame open for 5 seconds (aka set time)
        while (freezeClock.getElapsedTime() < freezeLength)
        {
            sf::Event event;
            window.pollEvent(event);

            //Draws Player + HUD
            game.render_bots(window);
            window.display();
        }
        return true;
    } catch (int x ){
        return false;
    }
}

//Test 3: Map rendering
bool testMap(){
    Game game;
    
    try{
        //Unit test timeout
        const sf::Time freezeLength{ sf::seconds(5.f) };
        sf::Clock freezeClock;

        //Create sf window
        sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");

        //Let bots move untill player takes damage
        while (freezeClock.getElapsedTime() < freezeLength)
        {
            sf::Event event;
            window.pollEvent(event);
            window.clear();
            window.draw(game.get_map());
            window.display();
        }
        
        return true;

    } catch (int x) {
        return false;
    }
}


//Test 4: Collision with map object
bool testCollision(){
    Game game;

    //Mock object aggregated by player class
    Player* player = new Player(1440, 800, 250.f, 160.f, 1);
    
    //Unit test timeout
    const sf::Time freezeLength{ sf::seconds(120.f) };
    sf::Clock freezeClock;

    //Create sf window
    sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");
    window.setFramerateLimit(120);

    //Create object to collide with (simuilates game class)
    tileFeature** features = new tileFeature*[1]; //Need to free
    features[0] = new tileFeature(1,272.f,160.f);

    //Let bots move untill player takes damage
    while (freezeClock.getElapsedTime() < freezeLength)
    {
        sf::Event event;
        window.pollEvent(event);
        window.clear();  
        window.draw(game.get_map());

        //Move player toward wall
        player->move(movement::right, features, 1, 1440, 800);
        player->render(window, 1440, 800, features,1, player, NULL, 0);
      
        window.display();

        //Check if player has collided with object at 272 160 within tolerance threshold
        if (abs(player->get_x() - 272 + 24) < 5 && abs(player->get_y() - 160) < 14){
          return true;
        }
    }

    return false;
}

//Test 5: Move away from map object (opposite dir)
bool testOppositeMove(){
    Game game;

    //Mock object aggregated by player class
    Player* player = new Player(1440, 800, 1000.f, 288.f, 1);
    
    //Unit test timeout
    const sf::Time freezeLength{ sf::seconds(120.f) };
    sf::Clock freezeClock;

    //Create sf window
    sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");
    window.setFramerateLimit(120);

    //Create object to collide with (simuilates game class)
    tileFeature** features = new tileFeature*[1];
    features[0] = new tileFeature(1,1168.f,288.f);

    //Let bots move untill player takes damage
    while (freezeClock.getElapsedTime() < freezeLength)
    {
        sf::Event event;
        window.pollEvent(event);
        window.clear();  
        window.draw(game.get_map());

        //Move player toward wall
        player->move(movement::right, features, 1, 1440, 800);
        player->render(window, 1440, 800, features,1, player, NULL, 0);
      
        window.display();

        //Check if player has collided with object at 272 160 within tolerance threshold
        if(abs(player->get_x() - features[0]->get_x() + 24) < 5 && abs(player->get_y() - features[0]->get_y()) < 14){

            //Store x-coordinate of collision event
            float x = player->get_x();

            //Move player away
            for(int i = 0; i < 50; i++){
                window.clear();
                window.draw(game.get_map());
                player->move(movement::left, features, 1, 1440, 800);
                player->render(window, 1440, 800, features,1, player, NULL, 0);
                window.display();
            }
            
            //Compare coordinates of player
            if(x != player->get_x()) return true;
        }
            
    }

    return false;
}

//Test 6: Move along collided map object (down)
bool testMovealong(){

    Game game;

    //Mock object aggregated by player class
    Player* player = new Player(1440, 800, 1000.f, 288.f, 1);
    
    //Unit test timeout
    const sf::Time freezeLength{ sf::seconds(120.f) };
    sf::Clock freezeClock;

    //Create sf window
    sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");
    window.setFramerateLimit(120);

    //Create object to collide with (simuilates game class)
    tileFeature** features = new tileFeature*[1];
    features[0] = new tileFeature(1,1168.f,288.f);

    //Let bots move untill player takes damage
    while (freezeClock.getElapsedTime() < freezeLength)
    {
        sf::Event event;
        window.pollEvent(event);
        window.clear();  
        window.draw(game.get_map());

        //Move player toward wall
        player->move(movement::right, features, 1, 1440, 800);
        player->render(window, 1440, 800, features,1, player, NULL, 0);
      
        window.display();

        //Check if player has collided with object at 272 160 within tolerance threshold
        if(abs(player->get_x() - features[0]->get_x() + 24) < 5 && abs(player->get_y() - features[0]->get_y()) < 14){

            //Store x-coordinate of collision event
            float y = player->get_y();

            //Move player away
            for(int i = 0; i < 50; i++){
                window.clear();
                window.draw(game.get_map());
                player->move(movement::down, features, 1, 1440, 800);
                player->render(window, 1440, 800, features,1, player, NULL, 0);
                window.display();
            }
            
            //Compare coordinates of player
            if(y != player->get_y()) return true;
        }
            
    }

    return false;
}

//Test 7 render objects
bool testObjectRender(){

    Game game;
    
    try{
        //Unit test timeout
        const sf::Time freezeLength{ sf::seconds(5.f) };
        sf::Clock freezeClock;

        //Create sf window
        sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");

        //Let bots move untill player takes damage
        while (freezeClock.getElapsedTime() < freezeLength)
        {
            sf::Event event;
            window.pollEvent(event);
            window.clear();
            window.draw(game.get_map());
            game.render_objects(window);
            window.display();
        }
        return true;
    } catch (int x) {
        return false;
    }

}

//Test 8: player can collect objects 
bool testCollectObject(){

    Game game;

    //Mock object aggregated by player class
    Player* player = new Player(1440, 800, 100.f, 750.f, 1);
    
    //Create object to collide with (simuilates game class)
    //Note these objects are within the 30 by 30 threshold defined in the Person Class
    //to be able to pickup an object
    int ammoID = 2;
    Ammo* ammo = new Ammo(ammoID, false, 90.f, 750.f);

    //Collectablea array (collect function parameters)
    Collectable** collectables = new Collectable*[1];
    collectables[0] = ammo;

    //Collectables maps (collect function parameters)
    std::map<int, Ammo*> ammoobj;
    std::map<int, Gun*> gunobj;
    std::map<int, Health*> healthobj;
    ammoobj[ammoID] = ammo;

    //Collect object
    player->collectObject(collectables, 1, ammoobj, healthobj, gunobj);

    if(ammo->get_collected_status())
        return true;
    
    return false;
}

//Test 9: Bullet hits Bot
bool testBulletCollision(){
    
    Game game;

    //Mock object aggregated by game class
    Player* player = new Player(1440, 800, 100.f, 750.f, 1);
   
    //Mock object aggregated by game class
    HardBot* bot = new HardBot(1, 200.f, 750.f, 1440, 800);
    BotBehaviour** bots = new BotBehaviour*[1];
    bots[0] = bot;

    //Timeout for unit test
    const sf::Time freezeLength{ sf::seconds(120.f) };
    sf::Clock freezeClock;

    //Create sf window
    sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");
    window.setFramerateLimit(120);

    //Loop until bullet collides with bot
    while (freezeClock.getElapsedTime() < freezeLength)
    {
        sf::Event event;
        window.pollEvent(event);
        window.clear();  
        window.draw(game.get_map());
        player->attack();
        player->render(window, 1440, 800, NULL, 0, player, bots, 1);
        bot->render(window, 1440, 800, NULL, 0, player, bots, 1);
        window.display();
        
        if(bot->get_health() < 100)
            return true;
    }

    return false;
}

//Test 10: bullet rendering
bool bulletRenders(){

    Game game;

    //Mock object aggregated by game class
    Player* player = new Player(1440, 800, 100.f, 750.f, 1);

    //Timeout for unit test
    const sf::Time freezeLength{ sf::seconds(5.f) };
    sf::Clock freezeClock;

    //Create sf window
    sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");
    window.setFramerateLimit(120);
    
    try{
        while(freezeClock.getElapsedTime() < freezeLength){
            sf::Event event;
            window.pollEvent(event);
            window.clear();
            
            //Shoots bullet
            player->attack();
            
            //Renders bullet
            player->render(window, 1440, 800, NULL, 0, player, NULL, 0);
            
            window.display();  
        }

        return true;
    } catch (int err){
        return false;
    }

}

//Test 11: Bullets stop shooting when ammo is 0
bool ammoTest(){

    Game game;

    //Mock object aggregated by game class
    Player* player = new Player(1440, 800, 100.f, 750.f, 1);
   
    //Create sf window
    sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");
    window.setFramerateLimit(120);

    //Shoot all bullets in pistol
    for (int i = 0; i < 41; i++)
    {
        sf::Event event;
        window.pollEvent(event);
        window.clear();  
        window.draw(game.get_map());

        //Shoot bullet
        player->attack();

        //Render bullet & player
        player->render(window, 1440, 800, NULL, 0, player, NULL, 0);
    
        window.display();

        //Let the gun cooldown for 200ms , ensures pistol bullet is actually shot
        //Due to firerate restrictions
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    //Check if player can still attack after shooting all pistol bullets
    if(!player->canAttack())
        return true;

    return false;

}

//Test 12: Player can swap guns
bool testSwap(){

    //Stores attacking state of pistol
    bool pistolAttack = true;
    
    Game game;

    //Create "Mock" gun collectable
    int gunID = 2;
    Gun* gun = new Gun(gunID, false, rapid, 90.f, 750.f);

    //Collectablea array (collect function parameters)
    Collectable** collectables = new Collectable*[1];
    collectables[0] = gun;

    //Collectables maps (collect function parameters)
    std::map<int, Ammo*> ammoobj;
    std::map<int, Gun*> gunobj;
    std::map<int, Health*> healthobj;
    gunobj[gunID] = gun;

    //Mock object aggregated by game class
    Player* player = new Player(1440, 800, 100.f, 750.f, 1);
    
    //Collect gun
    player->collectObject(collectables, 1, ammoobj, healthobj, gunobj);
   
    //Create sf window
    sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");
    window.setFramerateLimit(120);

    //Shoot all bullets in pistol (we loop to 40 to check if we can attack after expending all bullets)
    for (int i = 0; i < 40; i++)
    {
        sf::Event event;
        window.pollEvent(event);
        window.clear();  
        window.draw(game.get_map());

        //Shoot bullet
        player->attack();

        //Render bullet & player
        player->render(window, 1440, 800, NULL, 0, player, NULL, 0);
    
        window.display();

        //Let the gun cooldown for 200ms (ensures canAttack() doesn't return
        //false due to fire rate limiter) 
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
         
        //Check if player can still attack after shooting all pistol bullets
        if(!player->canAttack())
            pistolAttack = false;
    } 

    //Swap player gun
    player->swapGun();   

    //Check pistol cannot attack and new rapid fire gun can
    //this indicates the player has swapped guns as canAttack()
    //is triggered to return false if the ammo count is 0
    //Which is the role of the for loop above
    if(player->canAttack() && !pistolAttack){
        return true;
    }

    return false;
    
}

//Test 13: Hard Bot movement (randomly)
bool testHardBotRoam(){
    Game game;

    //Mock object aggregated by game class
    Player* player = new Player(1440, 800, 100.f, 750.f, 1);

    float x = 200.f;
    float y = 750.f;
    HardBot* bot = new HardBot(1, x, y, 1440, 800);

    //Unit test timeout
    const sf::Time freezeLength{ sf::seconds(120.f) };
    sf::Clock freezeClock;

    //Create sf window
    sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");
    window.setFramerateLimit(120);

    //Loop until bot moves from pre-determined spot
    while (freezeClock.getElapsedTime() < freezeLength)
    {
        sf::Event event;
        window.pollEvent(event);
        window.clear();  

        //Move bot
        bot->move_bot(NULL, 0, 1440, 800, player, NULL, 0);

        //Render bot
        bot->render(window, 1440, 800, NULL, 0, player, NULL, 0);

        window.display();

        //Check if bot position has changed
        if(bot->get_x() != x || bot->get_y() != y)
            return true;
    }

    return false;
}

//Test 14: Easy Bot movement (randomly)
bool testEasyBotRoam(){
    Game game;

    //Mock object aggregated by game class
    Player* player = new Player(1440, 800, 100.f, 750.f, 1);

    float x = 200.f;
    float y = 750.f;
    EasyBot* bot = new EasyBot(1, x, y, 1440, 800);

    //Unit test timeout
    const sf::Time freezeLength{ sf::seconds(120.f) };
    sf::Clock freezeClock;

    //Create sf window
    sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");
    window.setFramerateLimit(120);

    //Loop until bot moves from pre-determined spot
    while (freezeClock.getElapsedTime() < freezeLength)
    {
        sf::Event event;
        window.pollEvent(event);
        window.clear();  

        //Move bot
        bot->move_bot(NULL, 0, 1440, 800, player, NULL, 0);

        //Render bot
        bot->render(window, 1440, 800, NULL, 0, player, NULL, 0);

        window.display();

        //Check if bot position has changed
        if(bot->get_x() != x || bot->get_y() != y)
            return true;
    }

    return false;
}

//Test 15: Easy Bots shoot at player (when y coordinates match)
bool testShootY(){
    Game game;

    //Mock object aggregated by game class, it has macthing x coordinates with HardBot
    Player* player = new Player(1440, 800, 200.f, 750.f, 1);

    //Mock object aggregated by game class, matching x coordinate with Player class object
    EasyBot* bot = new EasyBot(1, 100.f, 750.f, 1440, 800);
    BotBehaviour** bots = new BotBehaviour*[1];
    bots[0] = bot;

    //Unit test timeout
    const sf::Time freezeLength{ sf::seconds(120.f) };
    sf::Clock freezeClock;

    //Create sf window
    sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");
    window.setFramerateLimit(120);

    //Loop until bot takes damage
    while (freezeClock.getElapsedTime() < freezeLength)
    {
        sf::Event event;
        window.pollEvent(event);
        window.clear();  

        player->render(window, 1440, 800, NULL, 0, player, bots, 1);

        //Move bot (this should trigger an attack)
        bot->move_bot(NULL, 0, 1440, 800, player, NULL, 0);

        //Render bot
        bot->render(window, 1440, 800, NULL, 0, player, NULL, 0);

        window.display();

        //Check if player has taken damage as a result
        if(player->get_health() < 100)
            return true;
    }

    return false;

}

//Test 16: Check bot swaps to rapid fire gun if available
bool botSwapsBestGun(){
     //Stores attacking state of pistol
    bool pistolAttack = true;
    
    Game game;

    //Create "Mock" gun collectable
    int gunID = 2;
    Gun* gun = new Gun(gunID, false, rapid, 90.f, 750.f);

    //Collectablea array (collect function parameters)
    Collectable** collectables = new Collectable*[1];
    collectables[0] = gun;

    //Collectables maps (collect function parameters)
    std::map<int, Ammo*> ammoobj;
    std::map<int, Gun*> gunobj;
    std::map<int, Health*> healthobj;
    gunobj[gunID] = gun;

    //Mock object aggregated by game class
    HardBot* bot = new HardBot(1, 100.f, 750.f, 1440, 800);
    
    //Collect gun
    bot->collectObject(collectables, 1, ammoobj, healthobj, gunobj);
  
    //Create sf window
    sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");
    window.setFramerateLimit(120);

    //Mock object aggregated by game class, it has macthing x coordinates with HardBot
    Player* player = new Player(1440, 800, 200.f, 750.f, 1);

    //Should cause bot to change guns (since move_bot drives all decision making)
    bot->move_bot(NULL,0,1440,800,player,NULL,0);

    //Checks bot has actually swapped to secondary gun by checking the bot can shoot 100 bullets
    for (int i = 0; i < 100; i++)
    {
        sf::Event event;
        window.pollEvent(event);
        window.clear();  

        //Shoot bullet
        bot->attack();

        //Render bullet & player
        bot->render(window, 1440, 800, NULL, 0, player, NULL, 0);
    
        window.display();

        //Let the gun cooldown for a second (ensures canAttack() doesn't return
        //false due to fire rate limiter) 
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
       
        //Check if player can still attack (after 40 iterations on pistol this should be false)
        //But for for rapid gun which can last 100 iterations
        if(!bot->canAttack())
            return false;
    } 

    return true;
}

//Test 17: check if bullet hits wall
bool testBulletHitsWall(){
    Game game;

    //Mock object aggregated by player class
    Bullet* bullet = new Bullet(250.f, 160.f, angle::right, 10);
    
    //Unit test timeout
    const sf::Time freezeLength{ sf::seconds(5.f) };
    sf::Clock freezeClock;

    //Create sf window
    sf::RenderWindow window(sf::VideoMode(game.get_width(), game.get_height()), "Painter.IO");
    window.setFramerateLimit(30);

    //Create object to collide with (simuilates game class)
    tileFeature** features = new tileFeature*[1];
    features[0] = new tileFeature(1,272.f,160.f);

    //Let bullet move untill it collides with wall
    while (freezeClock.getElapsedTime() < freezeLength)
    {
        sf::Event event;
        window.pollEvent(event);
        window.clear();  
        window.draw(game.get_map());

        //Move Bullet toward wall and render
        window.draw(bullet->shootBullet());
      
        window.display();

        //Check if bullet has collided with wall
        if(bullet->checkCollision(features, 1)) return true;
        
    }

    return false;
}

int main(){
    if(testPlayerRender()) std::cout << "Test 1 Pass" << std::endl;
    if(testBotRender()) std::cout << "Test 2 Pass" << std::endl;
    if(testMap()) std::cout << "Test 3 Pass" << std::endl;
    if(testCollision()) std::cout << "Test 4 Pass" << std::endl;
    if(testOppositeMove()) std::cout << "Test 5 Pass" << std::endl;
    if(testMovealong()) std::cout << "Test 6 Pass" << std::endl;
    if(testObjectRender()) std::cout << "Test 7 Pass" << std::endl;
    if(testCollectObject()) std::cout << "Test 8 Pass" << std::endl;
    if(testBulletCollision()) std::cout << "Test 9 Pass" << std::endl;
    if(bulletRenders()) std::cout << "Test 10 Pass" << std::endl;
    if(ammoTest()) std::cout << "Test 11 Pass" << std::endl;
    if(testSwap()) std::cout << "Test 12 Pass" << std::endl;
    if(testHardBotRoam()) std::cout << "Test 13 Pass" << std::endl;
    if(testEasyBotRoam()) std::cout << "Test 14 Pass" << std::endl;
    if(testShootY()) std::cout << "Test 15 Pass" << std::endl;
    if(botSwapsBestGun()) std::cout << "Test 16 Pass" << std::endl;
    if(testBulletHitsWall()) std::cout << "Test 17 Pass" << std::endl;
}