#pragma once

#include "player.hpp"
#include "tile.hpp"
#include "globals.hpp"

class enemy : public character
{
public:
    enemy(int width, int height, float posX, float posY, float offsetX, float offsetY, 
          float life, float speed, float strenght, 
          std::string name, std::string pgTexture = "../res/enemySheet.png");

    float attack(character *attacked, float deltatime); 

    void movement(float deltatime, player* pg); 
private:
    //animations
    bool MovingSide;
    animation RunningUp;
    animation RunningDown;
    animation RunningLeft;
    animation RunningRight;
    Direction LastDirection;
    animation AttackLeft;
    animation AttackRight;
    Clock Cooldown;
};