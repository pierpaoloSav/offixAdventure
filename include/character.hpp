#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "tile.hpp"
#include "animation.hpp"

using namespace sf;

enum Direction 
{
    NONE = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

/*
    A model for derivated classes who rappresent
    a character
*/

class character
{
public:
    character(int width, int height, float posX, float posY, float offsetX, float offsetY, 
              float life, float speed, float strenght, 
              std::string name, std::string pgTexture);
    virtual ~character() {}
    
    //movement: they set the x and y speeds in a frame
    virtual void moveForward();
    virtual void moveLeft();
    virtual void moveRight();
    virtual void moveBack();
    void rotate(float angle);

    //combat
    virtual float attack(character* attacked);
    virtual void getDamage(float damage);
    bool checkAlive();

    
    void update(float deltatime, std::vector<tile*> *collisions);

    void drawCharacter(sf::RenderWindow *window);
    
    //setters
    void setPosition(float posX, float posY);
    void setTexture(std::string texture);

    //getters
    float getPosX();
    float getPosY();
    RectangleShape &getHitbox();
    float getLife();
    float getStrenght();
    bool isColliding();

protected:
    void PgInit();
    void HitboxInit();
    
protected:

    float PosX;
    float PosY;
    float OffsetX;
    float OffsetY;

    int Width;
    int Height;

    float Life;
    float Strenght;

    float stdSpeed; 
    float SpeedX;
    float SpeedY;

    bool IsColliding;
    
    std::string Name;

    RectangleShape Hitbox;
    IntRect CurrentFrame;
    Texture PgTexture;
    Sprite Pg;

    Direction LastDirection;
};