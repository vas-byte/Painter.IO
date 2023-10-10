#include "../Headers/Common.h"

float calculateAngleBetweenVectors(float playerX, float playerY, float objX, float objY){
        // Calculate the dot product of the two vectors.
        float dotProduct = playerX * objX + playerY * objY;

        // Calculate the magnitude of the two vectors.
        float magnitude1 = sqrt(playerX * playerX + playerY * playerY);
        float magnitude2 = sqrt(objX * objX + objY * objY);

        // Calculate the angle between the two vectors.
        float angle = acos(dotProduct / (magnitude1 * magnitude2));

        // Convert the angle from radians to degrees.
        angle *= 180 / M_PI;

        return angle;
    }