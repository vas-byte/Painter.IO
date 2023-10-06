#ifndef COMMON_H
#define COMMON_H

    
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

#endif;



