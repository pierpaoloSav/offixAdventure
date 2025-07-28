#pragma once
#include <SFML/Graphics.hpp>

#include "character.hpp"
#include "animation.hpp"

using namespace sf;

class bullet : public character
{
public: 
    bullet(Direction lastDirection, float posX, float posY, float strenght, 
           int width = 15, int height = 5, float offsetX = 0, float offsetY = 0, 
           float life = 1, float speed = 0.4, 
           std::string name = "", std::string pgTexture = "../res/bullet.png");
    ~bullet();

    void movement(float deltatime);
private:
};