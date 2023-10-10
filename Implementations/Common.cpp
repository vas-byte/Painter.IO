#include "../Headers/Common.h"

 float direction_to_angle(movement::Direction direction){
    switch (direction)
    {
        case movement::right:
            return angle::right;
        
        case movement::down:
            return angle::down;

        case movement::left:
            return angle::left;

        case movement::up:
            return angle::up;
    }
 }
