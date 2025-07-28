#include <SFML/Graphics.hpp>
#include <iostream>

#include "tile.hpp"

using namespace sf;

void tile::TileInit()
{
    Tile.setPosition({ PosX, PosY });
    Tile.setTexture(TileTexture);
}

void tile::HitboxInit()
{
    Hitbox.setPosition({ PosX, PosY });
    Hitbox.setSize(Vector2f(Width, Height));

    Hitbox.setFillColor(Color::Transparent);
    Hitbox.setOutlineColor(Color::Blue);

    Hitbox.setOutlineThickness(1.0);
}

tile::tile(float posX, float posY, int width, int height, bool collision, std::string texture) :
    PosX(posX),
    PosY(posY),

    Width(width),
    Height(height),

    Collision(collision),

    TileTexture(Vector2u{ static_cast<unsigned int>(Width), static_cast<unsigned int>(Height) }),
    Tile(TileTexture)
{
    //texture load
    if (!TileTexture.loadFromFile(texture)) { std::cerr << "ERROR: can't load the texture" << texture << std::endl; }

    this->TileInit();
    this->HitboxInit();
}

void tile::setPosition(float posX, float posY)
{
    PosX = posX;
    PosY = posY;

    Tile.setPosition({ PosX, PosY });
    Hitbox.setPosition({ PosX, PosY });
}

float tile::getPosX()
{
    return PosX;
}

float tile::getPosY()
{
    return PosY;
}

bool tile::getCollision()
{
    return Collision;
}

RectangleShape &tile::getHitbox()
{
    return Hitbox;
}

void tile::drawTile(RenderWindow *window)
{
    window->draw(Tile);
    if (toggleHitbox) 
        window->draw(Hitbox);
}

grass::grass(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

rock::rock(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

rock2::rock2(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

rock3::rock3(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

water::water(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

water2::water2(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

water3::water3(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

water4::water4(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

water5::water5(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{    
}

water6::water6(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

water7::water7(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

water8::water8(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

water9::water9(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

water10::water10(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

water11::water11(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

water12::water12(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

water13::water13(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

ship::ship(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

colSpawner::colSpawner(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture),
    Full(0),
    Rare(0)
{
    Hitbox.setOutlineColor(Color::Red);
}

bool colSpawner::getFull()
{
    return Full;
}

bool colSpawner::getRareness()
{
    return Rare;
}

void colSpawner::setFull(bool full)
{
    Full = full;
}

rareSpawner::rareSpawner(float posX, float posY, int width, int height, bool collision, std::string texture) :
    colSpawner(posX, posY, width, height, collision, texture)
{
    Rare = 1;

    Hitbox.setOutlineColor(Color::Yellow);
}

path::path(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture) 
{
}

path1::path1(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture) 
{
}

path2::path2(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture) 
{
}

path3::path3(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture) 
{
}

path4::path4(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture) 
{
}

path5::path5(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture) 
{
}

path6::path6(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

path7::path7(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

path8::path8(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

tree::tree(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

heart::heart(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

fullHeart::fullHeart(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}

halfHeart::halfHeart(float posX, float posY, int width, int height, bool collision, std::string texture) :
    tile(posX, posY, width, height, collision, texture)
{
}
