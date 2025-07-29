#pragma once

#include <SFML/Graphics.hpp>

#include "globals.hpp"

using namespace sf;

class tile
{
public:
    tile(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, 
         bool collision = 0, bool solid = 0, std::string texture = " ");
    
    //setters
    void setPosition(float posX, float posY);

    //getters
    float getPosX();
    float getPosY();
    bool getCollision();
    bool getSolid();
    RectangleShape &getHitbox();

    void drawTile(RenderWindow *window);

protected:
    virtual void TileInit();
    virtual void HitboxInit();

protected:
    float PosX;
    float PosY;
    int Width;
    int Height;
    bool Collision;
    bool Solid;

    Texture TileTexture;
    Sprite Tile;
    RectangleShape Hitbox;
};

class grass : public tile
{
public:
    grass(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/grass.png");
};

class rock : public tile
{
public:
    rock(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 1, std::string texture = "../res/rock.png");
};

class rock2 : public tile
{
public:
    rock2(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 1, std::string texture = "../res/rock2.png");
};

class rock3 : public tile
{
public:
    rock3(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 1, std::string texture = "../res/rock3.png");
};

class water : public tile
{
public:
    water(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 0, std::string texture = "../res/water.png");
};

class water2 : public tile
{
public:
    water2(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 0, std::string texture = "../res/water2.png");
};

class water3 : public tile
{
public:
    water3(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 0, std::string texture = "../res/water3.png");
};

class water4 : public tile
{
public:
    water4(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 0, std::string texture = "../res/water4.png");
};

class water5 : public tile
{
public:
    water5(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 0, std::string texture = "../res/water5.png");
};

class water6 : public tile
{
public:
    water6(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 0, std::string texture = "../res/water6.png");
};

class water7 : public tile
{
public:
    water7(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 0, std::string texture = "../res/water7.png");
};

class water8 : public tile
{
public:
    water8(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 0, std::string texture = "../res/water8.png");
};

class water9 : public tile
{
public:
    water9(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 0, std::string texture = "../res/water9.png");
};

class water10 : public tile
{
public:
    water10(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 0, std::string texture = "../res/water10.png");
};

class water11 : public tile
{
public:
    water11(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 0, std::string texture = "../res/water11.png");
};

class water12 : public tile
{
public:
    water12(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 0, std::string texture = "../res/water12.png");
};

class water13 : public tile
{
public:
    water13(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 0, std::string texture = "../res/water13.png");
};

class ship : public tile
{
public:
    ship(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 0, std::string texture = "../res/ship.png");
};

class colSpawner : public tile
{
protected:
    bool Full;
    bool Rare;
    
public:
    colSpawner(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/grass.png");

    //getters
    bool getFull();
    bool getRareness();

    //setters
    void setFull(bool full);
};

class rareSpawner : public colSpawner
{
public:
    rareSpawner(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/grass.png");
};

class path : public tile 
{
public:
    path(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/path.png");
};

class path1 : public tile 
{
public:
    path1(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/path1.png");
};

class path2 : public tile 
{
public:
    path2(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/path2.png");
};

class path3 : public tile 
{
public:
    path3(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/path3.png");
};

class path4 : public tile 
{
public:
    path4(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/path4.png");
};

class path5 : public tile 
{
public:
    path5(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/path5.png");
};

class path6 : public tile 
{
public:
    path6(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/path6.png");
};

class path7 : public tile 
{
public:
    path7(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/path7.png");
};

class path8 : public tile 
{
public:
    path8(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/path8.png");
};

class tree : public tile 
{
public:
    tree(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 1, bool solid = 1, std::string texture = "../res/tree.png");
};

class heart : public tile 
{
public:
    heart(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/emptyHeart.png");
};

class fullHeart : public tile 
{
public:
    fullHeart(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/fullHeart.png");
};

class halfHeart : public tile 
{
public:
    halfHeart(float posX = 0, float posY = 0, int width = BLOCK_SIZE, int height = BLOCK_SIZE, bool collision = 0, bool solid = 0, std::string texture = "../res/halfHeart.png");
};