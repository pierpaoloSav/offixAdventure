#include <iostream>

#include "collectible.hpp"

void collectible::ColInit()
{
    Col.setPosition({ PosX, PosY });
    Col.setTexture(ColTexture);
}

void collectible::HitboxInit()
{
    Hitbox.setPosition({ PosX, PosY });
    Hitbox.setSize(Vector2f(Width, Height));

    Hitbox.setFillColor(Color::Transparent);
    Hitbox.setOutlineColor(Color::Red);

    Hitbox.setOutlineThickness(1.0);
}

collectible::collectible(float posX, float posY, int width, int height, std::string texture) :
    PosX(posX),
    PosY(posY),
    
    Width(width),
    Height(height),
    Scale(1.0f),

    SpawnerIndex(),

    ColTexture(Vector2u{ static_cast<unsigned int>(Width), static_cast<unsigned int>(Height) }),
    Col(ColTexture)
{
    //texture load 
    if (!ColTexture.loadFromFile(texture)) { std::cerr << "ERROR: can't load the texture"; }

    this->ColInit();
    this->HitboxInit();
    this->setScale(SCALE);
}

bool collectible::checkTaked(player *pg)
{
    if (checkCollision(Hitbox, pg->getHitbox())) { return true; }
    else { return false; }
}

void collectible::setPosition(float posX, float posY)
{
    PosX = posX;
    PosY = posY;
    Col.setPosition({ PosX, PosY });
    Hitbox.setPosition({ PosX, PosY });
}

void collectible::setSpawnerIndex(int index)
{
    SpawnerIndex = index;
}

void collectible::setScale(float scale)
{
    Width /= Scale;
    Height /= Scale;
    PosX /= Scale;
    PosY /= Scale;

    //set the Scale
    Scale = scale;
    Col.setScale(Vector2f{Scale, Scale});

    //reset the position
    this->setPosition(PosX*Scale, PosY*Scale);

    //reset the dimensions
    Width *= Scale;
    Height *= Scale;
    Hitbox.setSize(Vector2f(Width, Height));
}

float collectible::getPosX()
{
    return PosX;
}

float collectible::getPosY()
{
    return PosY;
}

int collectible::getSpawnerIndex()
{
    return SpawnerIndex;
}

void collectible::drawCollectible(RenderWindow *window)
{
    window->draw(Col);
    if (toggleHitbox) { window->draw(Hitbox); }
}


hamburger::hamburger(float posX, float posY, int width, int height, std::string texture) :
    collectible(posX, posY, width, height, texture)
{
}

bool hamburger::checkTaked(player *pg)
{
    if (collectible::checkTaked(pg))
    {
        pg->incScore();
        std::cout << "Score: " << pg->getScore() << std::endl;
        
        return true; 
    }
    else  
        return false;        
}

chili::chili(float posX, float posY, int width, int height, std::string texture) :
    collectible(posX, posY, width, height, texture)
{
}

bool chili::checkTaked(player *pg)
{
    if (collectible::checkTaked(pg))
    {
        pg->buffSpeed(0.2f, 3.0f);
        std::cout << "SUPERFAST" << std::endl;
        
        return true; 
    }
    else  
        return false;
}

pizza::pizza(float posX, float posY, int width, int height, std::string texture) :
    collectible(posX, posY, width, height, texture)
{
}

bool pizza::checkTaked(player *pg)
{
    if (collectible::checkTaked(pg))
    {
        pg->heal(1.0f);
        std::cout << "HEALED" << std::endl;
        
        return true; 
    }
    else  
        return false;
}

shield::shield(float posX, float posY, int width, int height, std::string texture) :
    collectible(posX, posY, width, height, texture)
{
}

bool shield::checkTaked(player *pg)
{
    if (collectible::checkTaked(pg))
    {
        pg->shield(5.0f);
        std::cout << "SHIELD" << std::endl;
        
        return true; 
    }
    else  
        return false;
}
