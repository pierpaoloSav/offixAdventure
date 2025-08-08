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

tile::tile(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    PosX(posX),
    PosY(posY),

    Width(width),
    Height(height),
    Scale(1.0f),

    Collision(collision),
    Solid(solid),

    TileTexture(Vector2u{ static_cast<unsigned int>(Width), static_cast<unsigned int>(Height) }),
    Tile(TileTexture)
{
    //texture load
    if (!TileTexture.loadFromFile(texture)) { std::cerr << "ERROR: can't load the texture" << texture << std::endl; }

    this->TileInit();
    this->HitboxInit();
    this->setScale(SCALE);
}

void tile::setPosition(float posX, float posY)
{
    PosX = posX;
    PosY = posY;

    Tile.setPosition({ PosX, PosY });
    Hitbox.setPosition({ PosX, PosY });
}

void tile::setScale(float scale)
{
    Width /= Scale;
    Height /= Scale;
    PosX /= Scale;
    PosY /= Scale;

    //set the Scale
    Scale = scale;
    Tile.setScale(Vector2f{Scale, Scale});

    //reset the position
    this->setPosition(PosX*Scale, PosY*Scale);

    //reset the dimensions
    Width *= Scale;
    Height *= Scale;
    Hitbox.setSize(Vector2f(Width, Height));
}

float tile::getPosX()
{
    return PosX/Scale;
}

float tile::getPosY()
{
    return PosY/Scale;
}

bool tile::getCollision()
{
    return Collision;
}

bool tile::getSolid()
{
    return Solid;
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

grass::grass(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

rock::rock(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

rock2::rock2(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

rock3::rock3(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

water::water(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

water1::water1(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

water2::water2(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

water3::water3(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

water4::water4(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

water5::water5(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{    
}

water6::water6(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

water7::water7(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

water8::water8(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

water9::water9(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

water10::water10(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

water11::water11(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

water12::water12(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

water13::water13(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

hut::hut(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

colSpawner::colSpawner(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture),
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

rareSpawner::rareSpawner(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    colSpawner(posX, posY, width, height, collision, solid, texture)
{
    Rare = 1;

    Hitbox.setOutlineColor(Color::Yellow);
}

path::path(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture) 
{
}

path1::path1(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture) 
{
}

path2::path2(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture) 
{
}

path3::path3(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture) 
{
}

path4::path4(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture) 
{
}

path5::path5(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture) 
{
}

path6::path6(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

path7::path7(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

path8::path8(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

path9::path9(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

path10::path10(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

path11::path11(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

path12::path12(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

tree::tree(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

heart::heart(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

fullHeart::fullHeart(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}

halfHeart::halfHeart(float posX, float posY, int width, int height, bool collision, bool solid, std::string texture) :
    tile(posX, posY, width, height, collision, solid, texture)
{
}
