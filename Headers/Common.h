#ifndef COMMON_H
#define COMMON_H
    
    //Defines fire rate of gun based off time restriction for calling attack()
    enum fireRate{
        pistol = 400,
        rapid = 100,
    };

    enum selectedGun{
        primary = 0,
        secondary = 1
    };
    
    namespace movement{

        //Defines direction player can move
        enum Direction{
            up = 0,
            down = 1,
            left = 2,
            right = 3,
        };

    }
    
    namespace angle{

        //Defines Sprite rotation angle based on direction player moves
        enum FacingAngle{
            up = 270,
            down = 90,
            left = 180,
            right = 0
        };

    }

#endif