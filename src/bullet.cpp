#include "bullet.hpp"

bullet::bullet(Direction lastDirection, float posX, float posY, float strenght, int width, int height, float offsetX, float offsetY, float life, float speed, std::string name, std::string pgTexture) :
    character(width, height, posX, posY, offsetX, offsetY, life, speed, strenght, name, pgTexture)
{
    LastDirection = lastDirection;

    //adjusting based on direction
    if (LastDirection == DOWN || LastDirection == UP) { this->rotate(90); }
    if (LastDirection == UP) { PosY-=Width*3; PosX+=Height/2; }
    if (LastDirection == DOWN) { PosX+=Height/2; }
}

bullet::~bullet()
{
}

void bullet::movement(float deltatime)
{
    switch (LastDirection)
    {
    case UP:
        moveForward();

        break;
    case DOWN:
        moveBack();

        break;
    case LEFT:
        moveLeft();
        
        break;
    case RIGHT:
        moveRight();

        break;
    default:
        break;
    }
}