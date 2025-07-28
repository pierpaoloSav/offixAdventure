#pragma once

#include <SFML/Graphics.hpp>
#include "globals.hpp"
#include "player.hpp"

using namespace sf;


class collectible
{
public:

    collectible(float posX, float posY, int width, int height, std::string texture);

    //setters
    void setPosition(float posX, float posY);
    void setSpawnerIndex(int index);

    //getters
    float getPosX();
    float getPosY();
    int getSpawnerIndex();

    virtual bool checkTaked(player *pg);    

    void drawCollectible(RenderWindow *window);                                                      

protected:
    void ColInit();
    void HitboxInit();

protected:
    int Width;
    int Height;
    float PosX;
    float PosY;

    int SpawnerIndex;

    Texture ColTexture;
    Sprite Col;
    RectangleShape Hitbox;
};

class hamburger : public collectible
{    
public:
    hamburger(float posX, float posY, int width = 33, int height = 36, std::string texture = "../res/hamburger.png");

    bool checkTaked(player *pg);    //derived
};

class chili : public collectible
{
public:
    chili(float posX, float posY, int width = 30, int height = 40, std::string texture = "../res/chili.png");

    bool checkTaked(player *pg);    //derived
};

class pizza : public collectible
{
public:
    pizza(float posX, float posY, int width = 40, int height = 40, std::string texture = "../res/pizza.png");

    bool checkTaked(player *pg);    //derived
};

class shield : public collectible
{
public:
    shield(float posX, float posY, int width = 40, int height = 40, std::string texture = "../res/shield.png");

    bool checkTaked(player *pg);    //derived
};

//OTHER IDEAS
//-BOX GLOVES
//-SACCU POWER