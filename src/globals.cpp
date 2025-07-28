#include "globals.hpp"
#include <math.h>

bool checkCollision(RectangleShape &rect1, RectangleShape &rect2)
{
    if(rect1.getPosition().x  + rect1.getSize().x > rect2.getPosition().x  && 
        rect1.getPosition().x < rect2.getPosition().x + rect2.getSize().x  &&
        rect1.getPosition().y  + rect1.getSize().y > rect2.getPosition().y  && 
        rect1.getPosition().y < rect2.getPosition().y + rect2.getSize().y) 
    {
        return true;
    }
    else 
        return false;
}

int pointsDistance(int xOne, int yOne, int xTwo, int yTwo)
{
    return sqrt( pow( xOne-xTwo, 2 ) + pow( yOne-yTwo, 2 ) );
}

//other
bool toggleHitbox = false;
